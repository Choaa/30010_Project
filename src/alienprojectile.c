#include "alienprojectile.h"
#include "ansi.h"
#include "maths.h"
#include <stdio.h>
#include <stdlib.h>

#define SHIFT_AMOUNT 8

#define ESC 0x1B

// projectile_ functions
void alienprojectile_init(struct alienprojectile *ap) {
    int i = 0;
    for (i = 0; i < 20; i++) {
        (ap+i)->x = 2;
        (ap+i)->y = 2;
        (ap+i)->alive = 0;
    }
}

void alienprojectile_spawn(struct alien *a, struct spaceship *s, struct alienprojectile *ap, int n) {
    (ap+n)->x = (a->x - 10) << SHIFT_AMOUNT;
    (ap+n)->y = (a->y) << SHIFT_AMOUNT;
    int dist = newton_sqrt((s->x-((ap+n)->x >> SHIFT_AMOUNT))*(s->x-((ap+n)->x >> SHIFT_AMOUNT))*2+(s->y-((ap+n)->y >> SHIFT_AMOUNT))*(s->y-((ap+n)->y >> SHIFT_AMOUNT)),500);
    (ap+n)->x = (ap+n)->x >> SHIFT_AMOUNT;
    (ap+n)->y = (ap+n)->y >> SHIFT_AMOUNT;
    dist = dist/10;
    (ap+n)->rx = (((s->x)-(ap+n)->x))/dist;
    (ap+n)->ry = (((s->y)-(ap+n)->y))/dist;
    (ap+n)->alive = 1;
}

void alienprojectile_pos(struct alienprojectile *ap, int n) {
    if ((ap+n)->alive == 1) {
        (ap+n)->x = (ap+n)->x + (ap+n)->rx;
        (ap+n)->y = (ap+n)->y + (ap+n)->ry;
    }
}

void alienprojectile_draw(struct alienprojectile *ap, int n) {
    if  ((ap+n)->alive == 1) {
        printf("%c[%d;%dH",ESC,(ap+n)->y-1,(ap+n)->x);
        fgcolor(11);
        printf("%c",223);
        fgcolor(15);
        printf("%c[%d;%dH",ESC,(ap+n)->y,(ap+n)->x-1);
        fgcolor(11);
        printf("%c%c%c",223,223,223);
        fgcolor(15);
        printf("%c[%d;%dH",ESC,(ap+n)->y+1,(ap+n)->x);
        fgcolor(11);
        printf("%c",223);
        fgcolor(15);
        printf("%c[H",ESC);
    }
}

void alienprojectile_clear(struct alienprojectile *ap, int n) {
    printf("%c[%d;%dH",ESC,(ap+n)->y-1,(ap+n)->x);
    printf("%c",32);
    printf("%c[%d;%dH",ESC,(ap+n)->y,(ap+n)->x-1);
    printf("%c%c%c",32,32,32);
    printf("%c[%d;%dH",ESC,(ap+n)->y+1,(ap+n)->x);
    printf("%c",32);
    printf("%c[H",ESC);
}

void alienprojectile_despawn(struct alienprojectile *ap, int n) {
    alienprojectile_clear(ap,n);
    (ap+n)->alive = 0;
    (ap+n)->x = 2;
    (ap+n)->y = 2;
}


