#include "stage.h"
#include "struct.h"
#include "objects.h"
#include "alien.h"
#include "ship.h"

#include <stdio.h>

#define ESC 0x1B

// Initialize the stage with planets and the player depending on the selected stage
void stage_init(int stage, struct spaceship *s, int angle, struct planet *p) {

    if (stage == 1) {
    planet_init(p, 170, 74, 0);
    planet_init(p, 280, 125, 1);
    }

    else if (stage == 2) {
    planet_init(p, 105, 140, 0);
    planet_init(p, 240, 130, 1);
    planet_init(p, 300, 70, 2);
    }

    else if (stage == 3) {
    planet_init(p, 120, 185, 0);
    planet_init(p, 165, 35, 1);
    planet_init(p, 241, 90, 2);
    planet_init(p, 280, 120, 3);
    }

    ship_draw(s,angle);
    planet_draw(p);
}

// Spawn each stages aliens at a certain time
void stage_waves(int stage, struct alien *a, int time) {

    // Wave patterns for stage 1
    if (stage == 1) {
        if (time == (100)) {
            alien_spawn(a,380,100,0);
        }
        if (time == (400)) {
            alien_spawn(a,380,50,1);
            alien_spawn(a,380,150,2);
        }
        if (time == (3000)) {
            alien_spawn(a,380,30,3);
            alien_spawn(a,380,170,4);
        }
        if (time == (3300)) {
            alien_spawn(a,380,100,5);
        }
    }

    // Wave patterns for stage 2
    if (stage == 2) {
        if (time == (100)) {
            alien_spawn(a,380,30,0);
        }
        if (time == (400)) {
            alien_spawn(a,380,60,1);
        }
        if (time == (700)) {
            alien_spawn(a,380,90,2);
        }
        if (time == (3000)) {
            alien_spawn(a,380,100,3);
        }
        if (time == (3300)) {
            alien_spawn(a,380,40,4);
            alien_spawn(a,380,160,5);
        }
        if (time == (3600)) {
            alien_spawn(a,380,100,6);
        }
        if (time == (5500)) {
            alien_spawn(a,380,50,0);
            alien_spawn(a,380,100,1);
            alien_spawn(a,380,150,2);
        }
        if (time == (6500)) {
            alien_spawn(a,380,80,3);
            alien_spawn(a,380,120,4);
        }
        if (time == (7000)) {
            alien_spawn(a,380,30,5);
            alien_spawn(a,380,170,6);
        }
    }
    // Wave patterns for stage 3
    if (stage == 3) {
        if (time == (100)) {
            alien_spawn(a,380,100,0);
        }
        if (time == (400)) {
            alien_spawn(a,380,70,1);
            alien_spawn(a,380,130,2);
        }
        if (time == (700)) {
            alien_spawn(a,380,100,3);
        }
        if (time == (1000)) {
            alien_spawn(a,380,40,4);
            alien_spawn(a,380,160,5);
        }
        if (time == (3900)) {
            alien_spawn(a,380,50,0);
            alien_spawn(a,380,150,1);
        }
        if (time == (4200)) {
            alien_spawn(a,380,100,2);
        }
        if (time == (4500)) {
            alien_spawn(a,380,50,3);
            alien_spawn(a,380,150,4);
        }
        if (time == (6500)) {
            alien_spawn(a,380,20,0);
            alien_spawn(a,380,180,1);
        }
        if (time == (7200)) {
            alien_spawn(a,380,30,2);
            alien_spawn(a,380,170,3);
        }
        if (time == (7500)) {
            alien_spawn(a,380,65,4);
            alien_spawn(a,380,135,5);
        }
        if (time == (7800)) {
            alien_spawn(a,380,100,6);
        }

    }
}
