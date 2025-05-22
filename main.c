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

void get_input(CellState_t map[BOARD_W * BOARD_H]);
void game_loop(CellState_t p1[BOARD_W * BOARD_H], (CellState_t p2[BOARD_W * BOARD_H);

int main() {
    clrscr();
    printf("Gebruik de pijltjes om\nte bewegen, + om te draaien, en - om te plaatsen\nDruk om door te gaan\n");
    while (!getk());

    CellState_t p1_map[BOARD_W * BOARD_H] = { 0 };
    get_input(p1_map);

    clrscr();
    printf("Geef de rekenmachine aan de volgende speler\n");
    while (!getk());

    CellState_t p2_map[BOARD_W * BOARD_H] = { 0 };
    get_input(p2_map);

    clrscr();
    printf("Geef de rekenmachine terug aan speler 1\n");
    while (!getk());

    main_loop(p1_map, p2_map);

    return 0;
}

void print_ship(int x, int y, int dir, int len) {
    for (int i = 0; i < len; i++) {
        gotoxy((x+i*(dir==0))*2, y+i*(dir==1));
        printf("O");
    }
}

void clear_ship(int x, int y, int dir, int len, CellState_t map[BOARD_W * BOARD_H]) {
    for (int i = 0; i < len; i++) {
        int ax = x+i*(dir==0);
        int ay = y+i*(dir==1);
        gotoxy(ax*2, ay);
        switch (map[ay*BOARD_W+ax]) {
            case CS_Water: printf("."); break;
            case CS_Ship: printf("O"); break;
            default: printf("?"); break;
        }
    }
}

void get_input(CellState_t map[BOARD_W * BOARD_H]) {
    int ship_len[NUM_SHIPS] = { 5, 4, 3, 2, 2 };

    clrscr();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            gotoxy(x*2, y);
            printf(".");
        }
    }

    int x = 0;
    int y = 0;

    int dir = 0;
    int len_i = 0;
    int len = ship_len[len_i];

    print_ship(x, y, dir, len);

    while (len_i < NUM_SHIPS) {
        int k = getk();
        bool moved = (k == K_UP || k == K_DOWN || k == K_LEFT || k == K_RIGHT || k == K_TURN);
        if (moved) clear_ship(x, y, dir, len, map);
        switch (k) {
            case K_EXIT:
                clrscr();
                printf("Bye!\n");
                exit(0);
            case K_UP:    if (y > 0) y -= 1; break;
            case K_DOWN:  if (y+(len-1)*(dir==1)+1 < BOARD_H) y += 1; break;
            case K_LEFT:  if (x > 0) x -= 1; break;
            case K_RIGHT: if (x+(len-1)*(dir==0)+1 < BOARD_W) x += 1; break;
            case K_TURN: {
                dir = !dir;
                if (dir == 0 && x+len > BOARD_W) x = BOARD_W - len;
                if (dir == 1 && y+len > BOARD_H) y = BOARD_H - len;
                break;
            }
            case K_PLACE: {
                for (int i = 0; i < len; i++) {
                    int ax = x+i*(dir==0);
                    int ay = y+i*(dir==1);
                    map[ay*BOARD_W+ax] = CS_Ship;
                }
                len_i += 1;
                len = ship_len[len_i];
                break;
            }
        }
        if (moved) print_ship(x, y, dir, len);
    }
}

void game_loop(CellState_t p1[BOARD_W * BOARD_H], (CellState_t p2[BOARD_W * BOARD_H) {
}
