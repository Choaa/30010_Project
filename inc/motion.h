#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _MOTION_H_
#define _MOTION_H_

struct TVector {
    int x, y;
};

struct spaceship {
    int x,y,vx,vy;
};

struct projectile {
    int x,y;
};

void initVector(struct TVector *v);
void rotVector(struct TVector *v, int angle);

void shipinit(struct spaceship *s);
void shippos(struct spaceship  *s, struct TVector *v, int on);
void shipdraw(struct spaceship *s, int angle);
void shipclear(struct spaceship *s, int angle);

void bulletinit(struct spaceship *s, struct projectile *p);
void bulletpos(struct projectile *p, struct TVector *v);
void bulletdraw(struct projectile *p);
void bulletclear(struct projectile *p);

void bombdraw(struct projectile *p);



#endif /* _MOTION_H_ */
