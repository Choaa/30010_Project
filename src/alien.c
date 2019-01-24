#include "alien.h"

#define ESC 0x1B

void alien_init(struct alien *a) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        (a+i)->x = 380;
        (a+i)->y = 200;
        (a+i)->alive = 0;
        (a+i)->animation = 0;
    }
}

void alien_spawn(struct alien *a, int x, int y, int n) {
    (a+n)->x = x;
    (a+n)->y = y;
    (a+n)->alive = 1;
}

void alien_pos(struct alien *a, struct projectile *p) {
    int i = 0;
    for (i = 0; i < 10; i++)
        if ((a+i)->alive == 1)
            (a+i)->x = (a+i)->x - 1;
}

void alien_despawn(struct alien *a, int n) {
    alien_clear(a);
    (a+n)->animation = 1;
    (a+n)->alive = 0;
}

void alien_animation(struct alien *a, int n) {
    if ((a+n)->animation == 1) {
        printf("%c[%d;%dH",ESC,(a+n)->y-2,(a+n)->x+1);
        printf("%c%c%c",219,219,219);
        printf("%c[%d;%dH",ESC,(a+n)->y-1,(a+n)->x-1);
        printf("%c%c %c",219,219,219);
        printf("%c[%d;%dH",ESC,(a+n)->y,(a+n)->x-3);
        printf("%c%c  %c",219,219,219);
        printf("%c[%d;%dH",ESC,(a+n)->y+1,(a+n)->x-1);
        printf("%c%c %c",219,219,219);
        printf("%c[%d;%dH",ESC,(a+n)->y+2,(a+n)->x+1);
        printf("%c%c%c",219,219,219);
    }
    if ((a+n)->animation > 0 && (a+n)->animation < 11) {
        (a+n)->animation++;
    }
    if ((a+n)->animation > 10) {
        (a+n)->animation = 0;
        printf("%c[%d;%dH",ESC,(a+n)->y-2,(a+n)->x+1);
        printf("%c%c%c",32,32,32);
        printf("%c[%d;%dH",ESC,(a+n)->y-1,(a+n)->x-1);
        printf("%c%c %c",32,32,32);
        printf("%c[%d;%dH",ESC,(a+n)->y,(a+n)->x-3);
        printf("%c%c  %c",32,32,32);
        printf("%c[%d;%dH",ESC,(a+n)->y+1,(a+n)->x-1);
        printf("%c%c %c",32,32,32);
        printf("%c[%d;%dH",ESC,(a+n)->y+2,(a+n)->x+1);
        printf("%c%c%c",32,32,32);
        (a+n)->x = 380;
        (a+n)->y = 200;
    }
}

void alien_clear(struct alien *a) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        if ((a+i)->alive == 1) {
            printf("%c[%d;%dH",ESC,(a+i)->y-2,(a+i)->x+1);
            printf("%c%c%c%c",32,32,32,32);
            printf("%c[%d;%dH",ESC,(a+i)->y-1,(a+i)->x-1);
            printf("%c%c%c%c",32,32,32,32);
            printf("%c[%d;%dH",ESC,(a+i)->y,(a+i)->x-3);
            printf("%c%c%c%c%c",32,32,32,32,32);
            printf("%c[%d;%dH",ESC,(a+i)->y+1,(a+i)->x-1);
            printf("%c%c%c%c",32,32,32,32);
            printf("%c[%d;%dH",ESC,(a+i)->y+2,(a+i)->x+1);
            printf("%c%c%c%c",32,32,32,32);
        }
    }
}

void alien_draw(struct alien *a) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        if ((a+i)->alive == 1) {
            printf("%c[%d;%dH",ESC,(a+i)->y-2,(a+i)->x+1);
            printf("%c%c%c%c",219,219,219,219);
            printf("%c[%d;%dH",ESC,(a+i)->y-1,(a+i)->x-1);
            printf("%c%c%c%c",219,219,219,219);
            printf("%c[%d;%dH",ESC,(a+i)->y,(a+i)->x-3);
            printf("%c%c%c%c%c",219,219,219,219,219);
            printf("%c[%d;%dH",ESC,(a+i)->y+1,(a+i)->x-1);
            printf("%c%c%c%c",219,219,219,219);
            printf("%c[%d;%dH",ESC,(a+i)->y+2,(a+i)->x+1);
            printf("%c%c%c%c",219,219,219,219);
        }
    }
}
