#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#pragma string name ZEESLAG

#define K_EXIT  64 // quit
#define K_UP    11 // up arrow
#define K_DOWN  10 // down arrow
#define K_LEFT  8  // left arrow
#define K_RIGHT 9  // right arrow
#define K_TURN  43 // plus
#define K_PLACE 45 // minus

#define BOARD_W 10
#define BOARD_H 8

#define NUM_SHIPS 5

typedef enum {
    CS_Water, CS_Ship, CS_WaterHit, CS_ShipHit
} CellState_t;

void get_input(int player, CellState_t board[BOARD_W * BOARD_H], int ship_len[NUM_SHIPS]);
void game_loop(CellState_t p1[BOARD_W * BOARD_H], CellState_t p2[BOARD_W * BOARD_H], int totalhits);

int main() {
    int ship_len[NUM_SHIPS] = { 5, 4, 3, 2, 2 };
    int totalhits = 16; // sum of ship_len

    clrscr();
    printf("Gebruik de pijltjes om\nte bewegen, + om te draaien, en - om te plaatsen. - toont een mis aan en X een raak shot aan\nDruk om door te gaan\n");
    while (!getk());

    CellState_t p1_board[BOARD_W * BOARD_H] = { 0 };
    get_input(1, p1_board, ship_len);

    clrscr();
    printf("Geef de rekenmachine aan speler 2\n");
    while (!getk());

    CellState_t p2_board[BOARD_W * BOARD_H] = { 0 };
    get_input(2, p2_board, ship_len);

    clrscr();
    printf("Geef de rekenmachine terug aan speler 1\n");
    while (!getk());

    game_loop(p1_board, p2_board, totalhits);

    return 0;
}

void print_ship(int x, int y, int dir, int len) {
    for (int i = 0; i < len; i++) {
        gotoxy((x+i*(dir==0))*2, y+i*(dir==1));
        printf("O");
    }
}

void clear_ship(int x, int y, int dir, int len, CellState_t board[BOARD_W * BOARD_H]) {
    for (int i = 0; i < len; i++) {
        int ax = x+i*(dir==0);
        int ay = y+i*(dir==1);
        gotoxy(ax*2, ay);
        switch (board[ay*BOARD_W+ax]) {
            case CS_Water: printf("."); break;
            case CS_Ship: printf("O"); break;
            default: printf("?"); break;
        }
    }
}

void get_input(int player, CellState_t board[BOARD_W * BOARD_H], int ship_len[NUM_SHIPS]) {
    clrscr();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            gotoxy(x*2, y);
            printf(".");
        }
    }
    gotoxy(20, 0);
    printf("P%d", player);

    int x = 0;
    int y = 0;

    int dir = 0;
    int len_i = 0;
    int len = ship_len[len_i];

    print_ship(x, y, dir, len);

    while (len_i < NUM_SHIPS) {
        int k = getk();
        bool moved = (k == K_UP || k == K_DOWN || k == K_LEFT || k == K_RIGHT || k == K_TURN);
        if (moved) clear_ship(x, y, dir, len, board);
        switch (k) {
            case K_EXIT:
                clrscr();
                printf("Bye!\n");
                exit(0);
            case K_UP:    if (y > 0) y--; break;
            case K_DOWN:  if (y+(len-1)*(dir==1)+1 < BOARD_H) y++; break;
            case K_LEFT:  if (x > 0) x--; break;
            case K_RIGHT: if (x+(len-1)*(dir==0)+1 < BOARD_W) x++; break;
            case K_TURN: {
                dir = !dir;
                if (dir == 0 && x+len > BOARD_W) x = BOARD_W - len;
                if (dir == 1 && y+len > BOARD_H) y = BOARD_H - len;
                break;
            }
            case K_PLACE: {
                bool blocked = false;
                for (int i = 0; i < len; i++) {
                    int ax = x+i*(dir==0);
                    int ay = y+i*(dir==1);
                    if (board[ay*BOARD_W+ax] == CS_Ship) {
                        blocked = true;
                        break;
                    }
                }
                if (blocked) break;
                for (int i = 0; i < len; i++) {
                    int ax = x+i*(dir==0);
                    int ay = y+i*(dir==1);
                    board[ay*BOARD_W+ax] = CS_Ship;
                }
                len_i++;
                len = ship_len[len_i];
                break;
            }
        }
        if (moved) print_ship(x, y, dir, len);
    }
}


void draw_board(int player, CellState_t board[BOARD_W * BOARD_H]) {
    clrscr();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            gotoxy(x*2, y);
            switch (board[y*BOARD_W+x]) {
                case CS_Water: case CS_Ship: printf("."); break;
                case CS_WaterHit: printf("-"); break;
                case CS_ShipHit: printf("X"); break;
                default: printf("?"); break;
            }
        }
    }
    gotoxy(20, 0);
    printf("P%d", player);
}

int player_turn(int player, CellState_t board[BOARD_W * BOARD_H]) {
    int x = 0;
    int y = 0; 
    int k = 0;

    draw_board(player, board);
    gotoxy(0, 0);
    printf("O"); 

    while (k != K_PLACE) {
        k = getk();
        bool moved = (k == K_UP || k == K_DOWN || k == K_LEFT || k == K_RIGHT);
        if (moved) {
            gotoxy(x*2, y);
            switch (board[y*BOARD_W+x]) {
                case CS_Water: case CS_Ship: printf("."); break;
                case CS_WaterHit: printf("-"); break;
                case CS_ShipHit: printf("X"); break;
                default: printf("?"); break;
            }
        }
        switch (k) {
            case K_EXIT:
                clrscr();
                printf("Bye!\n");
                exit(0);
            case K_UP:    if (y > 0) y--; break;
            case K_DOWN:  if (y+1 < BOARD_H) y++; break;
            case K_LEFT:  if (x > 0) x--; break;
            case K_RIGHT: if (x+1 < BOARD_W) x++; break;
        }
        if (moved) { gotoxy(x*2, y); printf("O"); }
    }

    gotoxy(x*2, y);
    int h = 0;
    if (board[y*BOARD_W+x] == CS_Ship) {
        board[y*BOARD_W+x] = CS_ShipHit;
        printf("X");
        h = 1;
    } else {
        board[y*BOARD_W+x] = CS_WaterHit;
        printf("-");
    }
    while (!getk());
    return 0;
}

void game_loop(CellState_t p1[BOARD_W * BOARD_H], CellState_t p2[BOARD_W * BOARD_H], int totalhits) {
    int player, p1_hits, p2_hits;
    int winner = -1;

    while (winner == -1) {
        player = !player;
        switch (player) {
            case 0: 
                p1_hits += player_turn(1, p2);
                if (p1_hits == totalhits) winner = 1;
                break;
            case 1: 
                p2_hits += player_turn(2, p1);
                if (p2_hits == totalhits) winner = 2;
                break;
            default: clrscr(); printf("ERROR\n"); exit(1);
        }
    }

    clrscr();
    printf("Speler 2 heeft gewonnen!\n");
}
