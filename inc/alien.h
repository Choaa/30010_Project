#include <stdio.h>
#ifndef _ALIEN_H
#define _ALIEN_H

#include "struct.h"
#include "stm32f30x_conf.h"
#include <stdio.h>

void alien_init(struct alien *a);
void alien_spawn(struct alien *a, int x, int y, int n);
void alien_pos(struct alien *a, struct projectile *p);
void alien_despawn(struct alien *a, int n);
void alien_clear(struct alien *a);
void alien_draw(struct alien *a);
void alien_animation(struct alien *a, int n);

#endif /*! _ALIEN_H_ */

