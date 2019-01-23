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

    ship_draw(s,angle);
    planet_draw(p);
}
