#include <stdio.h>
#include <conio.h>

#pragma string name ZEESLAG

#define K_EXIT  64

void get_input(int player);

int main() {
    while (1) {
        int k = getk();
        clrscr();
        gotoxy(0, 0);
        switch (k) {
            case K_EXIT: printf("%d; Bye!", k); exit(0);
            default: printf("%d", k); break;
        }
    }
    return 0;
}
