#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "mc_io.h"
#include "motion.h"
#include "LUT.h"
#include <stdlib.h>
#include <stdio.h>

#define ESC 0x1B

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

// Rotate vector

void initVector(struct TVector *v) {
    v->x = v->x << 14;
    v->y = v->y << 14;
}

void rotVector(struct TVector *v, int angle) {
     int x = FIX14_MULT(1 << 14,calccos(angle)) - FIX14_MULT(0 << 14,calcsin(angle));
     int y = FIX14_MULT(1 << 14,calcsin(angle)) + FIX14_MULT(0 << 14,calccos(angle));
     v->x = x;
     v->y = y;
}

// Ship functions

void shipinit(struct spaceship *s) {
    s->x = 20;
    s->y = 20;
    s->vx = 0;
    s->vy = 0;
}

void shippos(struct spaceship *s, struct TVector *v, int on) {
    if (on == 0) {
        s->x = s->x + (v->x*20 >> 14)*2;
        s->y = s->y + (v->y*20 >> 14);
    }
    else if (on == 1) {
        s->x = s->x - (v->x*20 >> 14)*2;
        s->y = s->y - (v->y*20 >> 14);

    }
}

void shipdraw(struct spaceship *s, int angle) {
    int num = angle / 15;
    if (num == 24) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219);
    }
    else if (num == 1) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+4);
    printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    }
    else if (num == 2) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+2);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+6);
    printf("%c%c",219,219);
    }
    else if (num == 3) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+4);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x+6);
    printf("%c%c",219,219);
    }
    else if (num == 4) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x+4);
    printf("%c%c",219,219);
    }
    else if (num == 5) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+4,s->x+2);
    printf("%c%c",219,219);
    }
    else if (num == 6) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+4,s->x);
    printf("%c%c",219,219);
    }
    else if (num == 7) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+4,s->x-2);
    printf("%c%c",219,219);
    }
    else if (num == 8) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x-4);
    printf("%c%c",219,219);
    }
    else if (num == 9) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-4);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+3,s->x-6);
    printf("%c%c",219,219);
    }
    else if (num == 10) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-4);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-6);
    printf("%c%c",219,219);
    }
    else if (num == 11) {
    printf("%c[%d;%dH",ESC,s->y,s->x-2);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-8);
    printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    }
    else if (num == 12) {
    printf("%c[%d;%dH",ESC,s->y,s->x-8);
    printf("%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219);
    }
    else if (num == 13) {
    printf("%c[%d;%dH",ESC,s->y,s->x-2);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-8);
    printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    }
    else if (num == 14) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-4);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-6);
    printf("%c%c",219,219);
    }
    else if (num == 15) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-4);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x-6);
    printf("%c%c",219,219);
    }
    else if (num == 16) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x-4);
    }
    else if (num == 17) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x-2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-4,s->x-2);
    printf("%c%c",219,219);
    }
    else if (num == 18) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-4,s->x);
    printf("%c%c",219,219);
    }
    else if (num == 19) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-4,s->x+2);
    printf("%c%c",219,219);
    }
    else if (num == 20) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x+4);
    printf("%c%c",219,219);
    }
    else if (num == 21) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+2);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+4);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-3,s->x+6);
    printf("%c%c",219,219);
    }
    else if (num == 22) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+2);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+6);
    printf("%c%c",219,219);
    }
    else if (num == 23) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c%c%c",219,219,219,219);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+4);
    printf("%c%c%c%c%c%c",219,219,219,219,219,219);
    }
}

void shipclear(struct spaceship *s, int angle) {
    int num = angle / 15;
    if (num == 24) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c%c%c%c%c%c%c%c%c",32,32,32,32,32,32,32,32,32,32);
    }
    else if (num == 1) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+4);
    printf("%c%c%c%c%c%c",32,32,32,32,32,32);
    }
    else if (num == 2) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+2);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+6);
    printf("%c%c",32,32);
    }
    else if (num == 3) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+4);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x+6);
    printf("%c%c",32,32);
    }
    else if (num == 4) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x+4);
    printf("%c%c",32,32);
    }
    else if (num == 5) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+4,s->x+2);
    printf("%c%c",32,32);
    }
    else if (num == 6) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+4,s->x);
    printf("%c%c",32,32);
    }
    else if (num == 7) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+4,s->x-2);
    printf("%c%c",32,32);
    }
    else if (num == 8) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x-4);
    printf("%c%c",32,32);
    }
    else if (num == 9) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-4);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+3,s->x-6);
    printf("%c%c",32,32);
    }
    else if (num == 10) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-4);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y+2,s->x-6);
    printf("%c%c",32,32);
    }
    else if (num == 11) {
    printf("%c[%d;%dH",ESC,s->y,s->x-2);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y+1,s->x-8);
    printf("%c%c%c%c%c%c",32,32,32,32,32,32);
    }
    else if (num == 12) {
    printf("%c[%d;%dH",ESC,s->y,s->x-8);
    printf("%c%c%c%c%c%c%c%c%c%c",32,32,32,32,32,32,32,32,32,32);
    }
    else if (num == 13) {
    printf("%c[%d;%dH",ESC,s->y,s->x-2);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-8);
    printf("%c%c%c%c%c%c",32,32,32,32,32,32);
    }
    else if (num == 14) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-4);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-6);
    printf("%c%c",32,32);
    }
    else if (num == 15) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-4);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x-6);
    printf("%c%c",32,32);
    }
    else if (num == 16) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x-4);
    }
    else if (num == 17) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x-2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-4,s->x-2);
    printf("%c%c",32,32);
    }
    else if (num == 18) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-4,s->x);
    printf("%c%c",32,32);
    }
    else if (num == 19) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-4,s->x+2);
    printf("%c%c",32,32);
    }
    else if (num == 20) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x+4);
    printf("%c%c",32,32);
    }
    else if (num == 21) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+2);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+4);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-3,s->x+6);
    printf("%c%c",32,32);
    }
    else if (num == 22) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c",32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+2);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y-2,s->x+6);
    printf("%c%c",32,32);
    }
    else if (num == 23) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c%c%c%c",32,32,32,32);
    printf("%c[%d;%dH",ESC,s->y-1,s->x+4);
    printf("%c%c%c%c%c%c",32,32,32,32,32,32);
    }
}

// Bullet functions
void bulletinit(struct spaceship *s, struct projectile *p) {
    p->x = s->x;
    p->y = s->y;
}

void bulletpos(struct projectile *p, struct TVector *v) {
    p->x = (p->x + v->x) >> 14;
    p->y = (p->y + v->y) >> 14;
}

void bulletdraw(struct projectile *p) {
    printf("%c[%d;%dH",ESC,p->y,p->x);
    printf("%c",169);
    printf("%c[H",ESC);
}

void bulletclear(struct projectile *p) {
    printf("%c[%d;%dH",ESC,p->y,p->x);
    printf("%c",32);
    printf("%c[H",ESC);
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

