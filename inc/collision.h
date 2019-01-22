#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _COLLISION_H_
#define _COLLISION_H_

void bullet_monster_collision(struct projectile *p, struct monster *m);
void bullet_player_collision(struct monsterprojectile *p, struct spaceship *s);
void player_monster_collision(struct monster *m, struct spaceship *s);
void player_stage_collision(struct spaceship *s, int angle, int leftx, int topy, int rightx, int bottomy);

#endif /*! _COLLISION_H_ */

