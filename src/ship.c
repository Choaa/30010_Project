#include "ship.h"

#define ESC 0x1B

// Start position and speed for the ship
void ship_init(struct spaceship *s) {
    s->x = 20;
    s->y = 20;
    s->vx = 0;
    s->vy = 0;
}

// Calculate the position of the ship
void ship_pos(struct spaceship *s, struct angle *v, int on) {
    if (on == 0) {
        s->x = s->x + (v->x*8 >> 14)*2;
        s->y = s->y + (v->y*8 >> 14);
    }
    else if (on == 1) {
        s->x = s->x - (v->x*8 >> 14)*2;
        s->y = s->y - (v->y*8 >> 14);

    }
}

// Draw the ship
void ship_draw(struct spaceship *s, int angle) {
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
    printf("%c%c",219,219);
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

// Clear the ship
void ship_clear(struct spaceship *s, int angle) {
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
    printf("%c%c",32,32);
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

