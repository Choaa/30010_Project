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

void bomb_init(struct bomb *b);
void bomb_spawn(struct bomb *b, struct spaceship *s, struct angle *v);
void bomb_pos(struct bomb *b);
void bomb_draw(struct bomb *b);
void bomb_explode(struct bomb *b, struct alienprojectile *ap, struct alien *a);
void bomb_clear(struct bomb *b);
void bomb_despawn(struct bomb *b);
void bomb_create(struct bomb *b);


#endif /*! _PROJECTILE_H_ */
