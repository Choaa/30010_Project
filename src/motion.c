#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "mc_io.h"
#include "motion.h"
#include "LUT.h"
#include "ansi.h"
#include <stdlib.h>
#include <stdio.h>

#define ESC 0x1B

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

// Rotate vector

void initVector(struct angle *v) {
    v->x = v->x << 14;
    v->y = v->y << 14;
}

void rotVector(struct angle *v, int angle) {
     int x = FIX14_MULT(1 << 14,calccos(angle)) - FIX14_MULT(0 << 14,calcsin(angle));
     int y = FIX14_MULT(1 << 14,calcsin(angle)) + FIX14_MULT(0 << 14,calccos(angle));
     v->x = x;
     v->y = y;
}


// Bomb functions
void bombdraw(struct projectile *p) {
    printf("%c[%d;%dH",ESC,p->y,p->x);
    printf("%c",62);
    printf("%c[H",ESC);
}

/*
void shipspeed(struct spaceship *s, int dir) {
    if (dir == 1) {
        int vx = s->vx + 1;
        if (vx < 3)
            s->vx = vx;
    }
    else if (dir == 2) {
        int vx = s->vx - 1;
        if (vx > -3)
            s->vx = vx;
    }
    else if (dir == 3) {
        int vy = s->vy + 1;
        s->vy = vy;
        if (vy < 3)
            s->vy = vy;
    }
    else if (dir == 4) {
        int vy = s->vy - 1;
        if (vy > -3)
            s->vy = vy;
    }
}

void shippos(struct spaceship *s) {
        int x = s->x + s->vx * 1;
        int y = s->y + s->vy * 1;
        if (x < 300)
            s->x = x;
        else if (x > 300)
            s->x = 2;
        if (y < 100)
            s->y = y;
        else if (y > 100)
            s->y = 2;
}
*/

