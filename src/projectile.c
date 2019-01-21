#include "projectile.h"
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
void projectile_init(struct projectile *p) {
    int i = 0;
    for (i = 0; i < 20; i++) {
        (p+i)->x = 2;
        (p+i)->y = 2;
        (p+i)->dir = 0;
        (p+i)->alive = 0;
    }
}

void projectile_spawn(struct spaceship *s, struct projectile *p, struct angle *v, int n, int dir) {
    if (n >= 20)
        return;

    if (dir == 0) {
        (p+n)->x = s->x+10;
        (p+n)->y = s->y;
        (p+n)->vx = (v->x*8 >> 14)*2;
        (p+n)->vy = (v->y*8 >> 14);
    }
    else if (dir == 1) {
        (p+n)->x = s->x+10;
        (p+n)->y = s->y;
        (p+n)->vx = 16;
        (p+n)->vy = 0;
    }
    else if (dir == 2) {
        (p+n)->x = s->x;
        (p+n)->y = s->y+10;
        (p+n)->vx = 0;
        (p+n)->vy = 8;
    }
    else if (dir == 3) {
        (p+n)->x = s->x-10;
        (p+n)->y = s->y;
        (p+n)->vx = -16;
        (p+n)->vy = 0;
    }
    else if (dir == 4) {
        (p+n)->x = s->x;
        (p+n)->y = s->y-10;
        (p+n)->vx = 0;
        (p+n)->vy = -8;
    }
    (p+n)->ax = 0;
    (p+n)->ay = 0;
    (p+n)->alive = 1;
    (p+n)->dir = dir;
}

void projectile_pos(struct projectile *p, struct planet *c, struct angle *v, int n) {
    if ((p+n)->alive == 1) {
    int32_t gm = 100;
    int i = 0;

    (p+n)->x = (p+n)->x << SHIFT_AMOUNT;
    (p+n)->y = (p+n)->y << SHIFT_AMOUNT;
    (p+n)->vx = (p+n)->vx << SHIFT_AMOUNT;
    (p+n)->vy = (p+n)->vy << SHIFT_AMOUNT;
    (p+n)->ax = (p+n)->ax << SHIFT_AMOUNT;
    (p+n)->ay = (p+n)->ay << SHIFT_AMOUNT;

    for(i = 0; i < 10; i++) {
        if ((c+i)->active == 1) {
            int32_t dist = newton_sqrt(((c+i)->x-((p+n)->x >> SHIFT_AMOUNT))*((c+i)->x-((p+n)->x >> SHIFT_AMOUNT))+((c+i)->y-((p+n)->y >> SHIFT_AMOUNT))*((c+i)->y-((p+n)->y >> SHIFT_AMOUNT)),500);
            int32_t ax = 0;
            int32_t ay = 0;
            if (dist <= 100) {
                ax = (p+n)->ax + ((((c+i)->x << SHIFT_AMOUNT)-(p+n)->x)*gm)/(dist*dist*dist);
                ay = (p+n)->ay + ((((c+i)->y << SHIFT_AMOUNT)-(p+n)->y)*gm)/(dist*dist*dist);
            }
            else if (dist > 100) {
                ax = 0;
                ay = 0;
            }
            if (abs(ax >> SHIFT_AMOUNT) > MAX_A) {
                ax = MAX_A * ax/abs(ax);
                ax = ax << SHIFT_AMOUNT;
            }
            if (abs(ay >> SHIFT_AMOUNT) > MAX_A) {
                ay = MAX_A * ay/abs(ay);
                ay = ay << SHIFT_AMOUNT;
            }
            (p+n)->ax = ax;
            (p+n)->ay = ay;
        }
    }
    int32_t vx = (p+n)->vx+(p+n)->ax;
    int32_t vy = (p+n)->vy+(p+n)->ay;
    int x = (p+n)->x + (p+n)->vx + (p+n)->ax/2;
    int y = (p+n)->y + (p+n)->vy + (p+n)->ay/2;

    if (abs(vx >> SHIFT_AMOUNT) > MAX_V) {
        vx = MAX_V * vx/abs(vx);
        vx = vx << SHIFT_AMOUNT;
    }
    if (abs(vy >> SHIFT_AMOUNT) > MAX_V) {
        vy = MAX_V * vy/abs(vy);
        vy = vy << SHIFT_AMOUNT;
    }
    (p+n)->vx = vx >> SHIFT_AMOUNT;
    (p+n)->vy = vy >> SHIFT_AMOUNT;
    (p+n)->x = x >> SHIFT_AMOUNT;
    (p+n)->y = y >> SHIFT_AMOUNT;
    }
}

void projectile_draw(struct projectile *p, int n) {
    if  ((p+n)->alive == 1) {
        printf("%c[%d;%dH",ESC,(p+n)->y-1,(p+n)->x);
        fgcolor(2);
        printf("%c",223);
        fgcolor(15);
        printf("%c[%d;%dH",ESC,(p+n)->y,(p+n)->x-1);
        fgcolor(2);
        printf("%c%c%c",223,223,223);
        fgcolor(15);
        printf("%c[%d;%dH",ESC,(p+n)->y+1,(p+n)->x);
        fgcolor(2);
        printf("%c",223);
        fgcolor(15);
        printf("%c[H",ESC);
    }
}

void projectile_clear(struct projectile *p, int n) {
    if ((p+n)->alive == 1) {
        printf("%c[%d;%dH",ESC,(p+n)->y-1,(p+n)->x);
        printf("%c",32);
        printf("%c[%d;%dH",ESC,(p+n)->y,(p+n)->x-1);
        printf("%c%c%c",32,32,32);
        printf("%c[%d;%dH",ESC,(p+n)->y+1,(p+n)->x);
        printf("%c",32);
        printf("%c[H",ESC);
    }
}

void projectile_despawn(struct projectile *p, int n) {
    projectile_clear(p,n);
    (p+n)->alive = 0;
    (p+n)->x = 2;
    (p+n)->y = 2;
    (p+n)->vx = 0;
    (p+n)->vy = 0;
}
