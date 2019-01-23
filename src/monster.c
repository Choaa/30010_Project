#include "monster.h"
#include "struct.h"
#include "equations.h"
#include "draw.h"

#define SHIFT_AMOUNT 2

#define ESC 0x1B

/*
const uint8_t monstersprite[11][58] = {
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
};

const uint8_t monsterclear[11][58] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
*/
/*
const uint8_t monstersprite[5][58] = {
    {0,0,0,0,1,1,1,1},
    {0,0,1,1,1,1,0,0},
    {1,1,1,1,1,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,0,1,1,1,1},
};

const uint8_t monsterclear[5][58] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
};
*/

void monster_init(struct monster *m) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        (m+i)->x = 380;
        (m+i)->y = 200;
        (m+i)->alive = 0;
        (m+i)->animation = 0;
    }
}

void monster_spawn(struct monster *m, int x, int y, int n) {
    (m+n)->x = x;
    (m+n)->y = y;
    (m+n)->alive = 1;
}

void monster_pos(struct monster *m, struct projectile *p) {
    int i = 0;
    for (i = 0; i < 10; i++)
        if ((m+i)->alive == 1)
            (m+i)->x = (m+i)->x - 1;
}

void monster_despawn(struct monster *m, int n) {
    monster_clear(m);
    (m+n)->animation = 1;
    (m+n)->alive = 0;
}

void monster_animation(struct monster *m, int n) {
    if ((m+n)->animation == 1) {
        printf("%c[%d;%dH",ESC,(m+n)->y-2,(m+n)->x+1);
        printf("%c%c%c",219,219,219);
        printf("%c[%d;%dH",ESC,(m+n)->y-1,(m+n)->x-1);
        printf("%c%c %c",219,219,219);
        printf("%c[%d;%dH",ESC,(m+n)->y,(m+n)->x-3);
        printf("%c%c  %c",219,219,219);
        printf("%c[%d;%dH",ESC,(m+n)->y+1,(m+n)->x-1);
        printf("%c%c %c",219,219,219);
        printf("%c[%d;%dH",ESC,(m+n)->y+2,(m+n)->x+1);
        printf("%c%c%c",219,219,219);
    }
    if ((m+n)->animation > 0 && (m+n)->animation < 11) {
        (m+n)->animation++;
    }
    if ((m+n)->animation > 10) {
        (m+n)->animation = 0;
        printf("%c[%d;%dH",ESC,(m+n)->y-2,(m+n)->x+1);
        printf("%c%c%c",32,32,32);
        printf("%c[%d;%dH",ESC,(m+n)->y-1,(m+n)->x-1);
        printf("%c%c %c",32,32,32);
        printf("%c[%d;%dH",ESC,(m+n)->y,(m+n)->x-3);
        printf("%c%c  %c",32,32,32);
        printf("%c[%d;%dH",ESC,(m+n)->y+1,(m+n)->x-1);
        printf("%c%c %c",32,32,32);
        printf("%c[%d;%dH",ESC,(m+n)->y+2,(m+n)->x+1);
        printf("%c%c%c",32,32,32);
        (m+n)->x = 380;
        (m+n)->y = 200;
    }
}

void monster_clear(struct monster *m) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        if ((m+i)->alive == 1) {
            printf("%c[%d;%dH",ESC,(m+i)->y-2,(m+i)->x+1);
            printf("%c%c%c%c",32,32,32,32);
            printf("%c[%d;%dH",ESC,(m+i)->y-1,(m+i)->x-1);
            printf("%c%c%c%c",32,32,32,32);
            printf("%c[%d;%dH",ESC,(m+i)->y,(m+i)->x-3);
            printf("%c%c%c%c%c",32,32,32,32,32);
            printf("%c[%d;%dH",ESC,(m+i)->y+1,(m+i)->x-1);
            printf("%c%c%c%c",32,32,32,32);
            printf("%c[%d;%dH",ESC,(m+i)->y+2,(m+i)->x+1);
            printf("%c%c%c%c",32,32,32,32);
        }
    }
}

void monster_draw(struct monster *m) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        if ((m+i)->alive == 1) {
            printf("%c[%d;%dH",ESC,(m+i)->y-2,(m+i)->x+1);
            printf("%c%c%c%c",219,219,219,219);
            printf("%c[%d;%dH",ESC,(m+i)->y-1,(m+i)->x-1);
            printf("%c%c%c%c",219,219,219,219);
            printf("%c[%d;%dH",ESC,(m+i)->y,(m+i)->x-3);
            printf("%c%c%c%c%c",219,219,219,219,219);
            printf("%c[%d;%dH",ESC,(m+i)->y+1,(m+i)->x-1);
            printf("%c%c%c%c",219,219,219,219);
            printf("%c[%d;%dH",ESC,(m+i)->y+2,(m+i)->x+1);
            printf("%c%c%c%c",219,219,219,219);
        }
    }
}
