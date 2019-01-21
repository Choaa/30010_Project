#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _STRUCT_H_
#define _STRUCT_H_

struct angle {
    int x, y;
};

struct spaceship {
    int x,y,vx,vy,hp;
};

struct monster {
    int x,y,alive;
};

struct projectile {
    int x,y,dir,alive;
    int32_t vx,vy,ax,ay;
};

struct monsterprojectile {
    int x,y,rx,ry,alive;
};

struct planet {
    int x,y,m,active;
};

#endif /*! _STRUCT_H_ */
