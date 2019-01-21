#include "monsterprojectile.h"
#include "ansi.h"
#include "equations.h"
#include <stdio.h>
#include <stdlib.h>

#define SHIFT_AMOUNT 8
#define FIX_MULT(a, b) ( (a)*(b) >> SHIFT_AMOUNT )
#define FIX_DIV(a, b) ( ((a) << SHIFT_AMOUNT) / b )

#define MAX_A 1
#define MAX_V 16

#define ESC 0x1B

// projectile_ functions
void monsterprojectile_init(struct monsterprojectile *p) {
    int i = 0;
    for (i = 0; i < 20; i++) {
        (p+i)->x = 2;
        (p+i)->y = 2;
        (p+i)->alive = 0;
    }
}

void monsterprojectile_spawn(struct monster *m, struct spaceship *s, struct monsterprojectile *p, int n) {
    (p+n)->x = (m->x - 10) << SHIFT_AMOUNT;
    (p+n)->y = (m->y) << SHIFT_AMOUNT;
    int dist = newton_sqrt((s->x-((p+n)->x >> SHIFT_AMOUNT))*(s->x-((p+n)->x >> SHIFT_AMOUNT))*2+(s->y-((p+n)->y >> SHIFT_AMOUNT))*(s->y-((p+n)->y >> SHIFT_AMOUNT)),500);
    (p+n)->x = (p+n)->x >> SHIFT_AMOUNT;
    (p+n)->y = (p+n)->y >> SHIFT_AMOUNT;
    dist = dist/10;
    (p+n)->rx = (((s->x)-(p+n)->x))/dist;
    (p+n)->ry = (((s->y)-(p+n)->y))/dist;
    (p+n)->alive = 1;
}

void monsterprojectile_pos(struct monsterprojectile *p, int n) {
    if ((p+n)->alive == 1) {
        (p+n)->x = (p+n)->x + (p+n)->rx;
        (p+n)->y = (p+n)->y + (p+n)->ry;
    }
}

void monsterprojectile_draw(struct monsterprojectile *p, int n) {
    if  ((p+n)->alive == 1) {
        printf("%c[%d;%dH",ESC,(p+n)->y-1,(p+n)->x);
        fgcolor(1);
        printf("%c",223);
        fgcolor(15);
        printf("%c[%d;%dH",ESC,(p+n)->y,(p+n)->x-1);
        fgcolor(1);
        printf("%c%c%c",223,223,223);
        fgcolor(15);
        printf("%c[%d;%dH",ESC,(p+n)->y+1,(p+n)->x);
        fgcolor(1);
        printf("%c",223);
        fgcolor(15);
        printf("%c[H",ESC);
    }
}

void monsterprojectile_clear(struct monsterprojectile *p, int n) {
        printf("%c[%d;%dH",ESC,(p+n)->y-1,(p+n)->x);
        printf("%c",32);
        printf("%c[%d;%dH",ESC,(p+n)->y,(p+n)->x-1);
        printf("%c%c%c",32,32,32);
        printf("%c[%d;%dH",ESC,(p+n)->y+1,(p+n)->x);
        printf("%c",32);
        printf("%c[H",ESC);
}

void monsterprojectile_despawn(struct monsterprojectile *p, int n) {
    monsterprojectile_clear(p,n);
    (p+n)->alive = 0;
    (p+n)->x = 2;
    (p+n)->y = 2;
}

