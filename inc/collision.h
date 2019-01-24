#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _COLLISION_H_
#define _COLLISION_H_

int bullet_alien_collision(struct projectile *p, struct alien *a);
void bullet_player_collision(struct alienprojectile *ap, struct spaceship *s);
void player_alien_collision(struct alien *a, struct spaceship *s);
void player_stage_collision(struct spaceship *s, int angle, int leftx, int topy, int rightx, int bottomy);
void asteroid_collision(struct spaceship *s, struct projectile *p, struct alienprojectile *ap, struct alien *a,struct planet *pla, struct bomb *b);
int player_pickup_collision(struct spaceship *s, struct bomb *b);

#endif /*! _COLLISION_H_ */

