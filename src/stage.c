#include "stage.h"
#include "struct.h"
#include "objects.h"
#include "alien.h"
#include "ship.h"

#include <stdio.h>

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
    planet_init(p, 76, 30, 2);
    planet_init(p, 200, 70, 3);
    }

    ship_draw(s,angle);
    planet_draw(p);
}

void stage_waves(int stage, struct alien *a, int time, int randwavetime) {

    // Wave patterns for stage 1
    if (stage == 1) {
        if (time == (0 + randwavetime)) {
            alien_spawn(a,380,100,0);
        }
        if (time == (300 + randwavetime)) {
            alien_spawn(a,380,50,1);
            alien_spawn(a,380,150,2);
        }
        if (time == (3000 + randwavetime)) {
            alien_spawn(a,380,30,3);
            alien_spawn(a,380,170,4);
        }
        if (time == (3400 + randwavetime)) {
            alien_spawn(a,380,100,5);
        }
    }

    // Wave patterns for stage 2
    if (stage == 2) {

    }
    // Wave patterns for stage 3
    if (stage == 3) {

    }
}
