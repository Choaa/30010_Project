#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _MOTION_H_
#define _MOTION_H_

void vector_init(struct angle *v);
void vector_rot(struct angle *v, int angle);


void bombdraw(struct projectile *p);

#endif /* _MOTION_H_ */
