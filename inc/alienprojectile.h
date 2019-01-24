#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _ALIENPROJECTILE_H_
#define _ALIENPROJECTILE_H_

void alienprojectile_init(struct alienprojectile *ap);
void alienprojectile_spawn(struct alien *a, struct spaceship *s, struct alienprojectile *ap, int n);
void alienprojectile_pos(struct alienprojectile *ap, int n);
void alienprojectile_draw(struct alienprojectile *ap, int n);
void alienprojectile_clear(struct alienprojectile *ap, int n);
void alienprojectile_despawn(struct alienprojectile *ap, int n);

#endif /*! _ALIENPROJECTILE_H_ */

