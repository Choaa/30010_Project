#include "stage.h"
#include "struct.h"
#include "ship.h"


#define ESC 0x1B

void stage_init(int stage, struct spaceship *s, int angle, struct planet *p) {

    if (stage == 1) {
    planet_init(p, 225, 30, 0);
    planet_init(p, 225, 70, 1);
    }

    else if (stage == 2) {
    planet_init(p, 225, 21, 0);
    planet_init(p, 125, 69, 1);
    planet_init(p, 300, 33, 2);
    }

    else if (stage == 3) {
    planet_init(p, 387, 30, 0);
    planet_init(p, 355, 70, 1);
    planet_init(p, 76, 30, 0);
    planet_init(p, 200, 70, 1);
    }

    else if (stage == 4) {
    planet_init(p, 335, 30, 0);
    planet_init(p, 153, 70, 1);
    planet_init(p, 273, 30, 0);
    planet_init(p, 129, 70, 1);
    planet_init(p, 299, 30, 0);
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
    planet_init(p, 10, 150, 0);
    planet_init(p, 40, 111, 1);
    planet_init(p, 70, 66, 2);
    planet_init(p, 100, 187, 3);
    planet_init(p, 130, 30, 4);
    planet_init(p, 160, 46, 5);
    planet_init(p, 190, 130, 6);
    planet_init(p, 220, 152, 7);
    planet_init(p, 250, 54, 8);
    planet_init(p, 280, 89, 9);
    }

    ship_draw(s,angle);
    planet_draw(p);
}

