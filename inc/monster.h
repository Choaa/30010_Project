#include <stdio.h>
#ifndef _MONSTER_H
#define _MONSTER_H

#include "struct.h"
#include "stm32f30x_conf.h"
#include <stdio.h>

void monster_init(struct monster *m);
void monster_spawn(struct monster *m, int x, int y, int n);
void monster_pos(struct monster *m, struct projectile *p);
void monster_despawn(struct monster *m, int n);
void monster_clear(struct monster *m);
void monster_draw(struct monster *m);
void monster_animation(struct monster *m, int n);


#endif /*! _MONSTER_H_ */
