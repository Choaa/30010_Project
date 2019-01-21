
#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _MONSTERPROJECTILE_H_
#define _MONSTERPROJECTILE_H_

void monsterprojectile_init(struct monsterprojectile *p);
void monsterprojectile_spawn(struct monster *m, struct spaceship *s, struct monsterprojectile *p, int n);
void monsterprojectile_pos(struct monsterprojectile *p, int n);
void monsterprojectile_draw(struct monsterprojectile *p, int n);
void monsterprojectile_clear(struct monsterprojectile *p, int n);
void monsterprojectile_despawn(struct monsterprojectile *p, int n);

#endif /*! _MONSTERPROJECTILE_H_ */
