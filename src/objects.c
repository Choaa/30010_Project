#include "equations.h"
#include "struct.h"

#define ESC 0x1B


void planet_init(struct planet *p) {
    p->x = 200;
    p->y = 50;
    p->active = 1;
    (p+1)->x = 300;
    (p+1)->y = 70;
    (p+1)->active = 1;
}


void planet_draw(int x, int y) {
    printf("%c[%d;%dH",ESC,y+4,x-2);
    printf("%c%c%c%c%c",219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y+3,x-3);
    printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y+2,x-4);
    printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y+1,x-4);
    printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y,x-4);
    printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y-1,x-4);
    printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y-2,x-4);
    printf("%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y-3,x-3);
    printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);
    printf("%c[%d;%dH",ESC,y-4,x-2);
    printf("%c%c%c%c%c",219,219,219,219,219);
}
