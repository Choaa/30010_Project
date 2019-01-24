#include "struct.h"

#define ESC 0x1B

// Initialize the asteroids
void planet_init(struct planet *p, int x, int y, int n) {
    (p+n)->x = x;
    (p+n)->y = y;
    (p+n)->active = 1;
}

void planet_draw(struct planet *p) {
    int i = 0;
    for (i = 0; i < 10; i++) {
            if ((p+i)->active == 1) {
                printf("%c[%d;%dH",ESC,(p+i)->y+4,(p+i)->x-2);
                printf("%c%c%c%c%c",219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y+3,(p+i)->x-3);
                printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y+2,(p+i)->x-4);
                printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y+1,(p+i)->x-4);
                printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y,(p+i)->x-4);
                printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y-1,(p+i)->x-4);
                printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y-2,(p+i)->x-4);
                printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y-3,(p+i)->x-3);
                printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);
                printf("%c[%d;%dH",ESC,(p+i)->y-4,(p+i)->x-2);
                printf("%c%c%c%c%c",219,219,219,219,219);
        }
    }
}
