#include "stage.h"
#include "struct.h"
#include "ship.h"


#define ESC 0x1B

void stage_init(int stage, struct spaceship *s, int angle, struct planet *p) {
    ship_init(s);
    ship_draw(s,angle);

    if (stage == 1) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_draw(p);
    }

    else if (stage == 2) {
    planet_init(p, 225, 21, 0);
    planet_init(p, 125, 69, 1);
    planet_init(p, 300, 33, 2);
    planet_draw(p);
    }

    else if (stage == 3) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    }

    else if (stage == 4) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    }

    else if (stage == 5) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    }

    else if (stage == 6) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    }

    else if (stage == 7) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    }

    else if (stage == 8) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    }

    else if (stage == 9) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    }
}

