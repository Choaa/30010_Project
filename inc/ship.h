#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _SHIP_H_
#define _SHIP_H_

void ship_init(struct spaceship *s);
void ship_pos(struct spaceship  *s, struct angle *v);
void ship_drift(struct spaceship *s, int angx, int angy, int drift);
void ship_draw(struct spaceship *s, int angle);
void ship_clear(struct spaceship *s, int angle);
void ship_health(struct spaceship *s);

#endif /*! _SHIP_H_ */
