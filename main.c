#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#pragma string name ZEESLAG

#define K_EXIT  64
#define K_UP    11
#define K_DOWN  10
#define K_LEFT  8
#define K_RIGHT 9
#define K_TURN  43
#define K_PLACE 45

#define BOARD_W 10
#define BOARD_H 10

#define NUM_SHIPS 5

typedef enum {
    CS_Water, CS_Ship, CS_WaterHit, CS_ShipHit
} CellState_t;

void get_input(int player, CellState_t map[BOARD_W * BOARD_H]);

int main() {
    // while (1) {
    //     int k = getk();
    //     clrscr();
    //     gotoxy(0, 0);
    //     switch (k) {
    //         case K_EXIT:
    //             gotoxy(6, 0);
    //             printf("%d; Bye!", k);
    //             exit(0);
    //         case K_UP:    printf("^"); break;
    //         case K_DOWN:  printf("v"); break;
    //         case K_LEFT:  printf("<"); break;
    //         case K_RIGHT: printf(">"); break;
    //         default: printf("%d", k); break;
    //     }
    // }
    CellState_t p0_map[BOARD_W * BOARD_H] = {0};
    get_input(0, p0_map);
    return 0;
}

void print_ship(int x, int y, int dir, int len) {
    for (int i = 0; i < len; i++) {
        gotoxy((x+i*(dir==0))*2+1, y+i*(dir==1));
        printf("O");
    }
}

void clear_ship(int x, int y, int dir, int len, CellState_t map[BOARD_W * BOARD_H]) {
    for (int i = 0; i < len; i++) {
        gotoxy((x+i*(dir==0))*2+1, y+i*(dir==1));
        switch (map[y*BOARD_W+x]) {
            case CS_Water: printf("."); break;
            case CS_Ship: printf("O"); break;
            default: printf("?"); break;
        }
    }
}

void get_input(int player, CellState_t map[BOARD_W * BOARD_H]) {

    int ship_len[NUM_SHIPS] = { 5, 4, 3, 2, 2 };

    clrscr();
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            gotoxy(x*2+1, y);
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
                printf("Bye!");
                exit(0);
            case K_UP:    if (y+len*(dir==1) < BOARD_H) y -= 1; break;
            case K_DOWN:  if (y > 1)                    y += 1; break;
            case K_LEFT:  if (x > 1)                    x -= 1; break;
            case K_RIGHT: if (x+len*(dir==0) < BOARD_W) x += 1; break;
        }
        if (moved) print_ship(x, y, dir, len);
        gotoxy(21, 0);
        printf("%d", x);
        gotoxy(21, 1);
        printf("%d", y);
    }
}
/*
While S-2<L₆(1)

getKey→K
If K=26andX+L*(D=1)≠10:X+1→X
If K=24andX≠1:X-1→X
If K=34andY+L*(D=­1)≠10:Y+1→Y
If K=25andY≠1:Y-1→Y

" ALPHA
If K=31
Then
D*­1→D
If D=1andX+L>10:10-L→X
If D=­1andY+L>10:10-L→Y
End

" 2ND
If K=21
Then
For(I,0,L)
If P=­1:((X+I*(D=1))*2-1)+(Y+I*(D=­1))/100→L₄(M)
If P=1:((X+I*(D=1))*2-1)+(Y+I*(D=­1))/100→L₅(M)
M+1→M
" Output(1,20,M)
End
S+1→S
If S-2<L₆(1):L₆(S)-1→L
End

For(I,0,L)
Output(Y+I*(D=­1),(X+I*(D=1))*2-1,"O")
End
End
End
End

" ### MAIN GAME LOOP ###

0→W
Repeat W
For(X,1,10)
For(Y,1,10)
Output(Y,X*2-1,".")
End
End
getKey→K
If 24≤KandK≤26orK=34orK=21
Then
1→W
End
End

" ### CLEANUP ###
ClrListL₅,L₄

ClrHome
Stop
 */
