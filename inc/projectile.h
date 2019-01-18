#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

void projectile_init(struct projectile *p);
void projectile_spawn(struct spaceship *s, struct projectile *p, struct angle *v, int n, int dir);
void projectile_pos(struct projectile *p, struct planet *c, struct angle *v, int n);
void projectile_draw(struct projectile *p, int n);
void projectile_clear(struct projectile *p, int n);
void projectile_despawn(struct projectile *p, int n);



#endif /* _SHIP_H_ */
