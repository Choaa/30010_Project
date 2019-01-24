#include "stm32f30x_conf.h"
#include "struct.h"
#include <stdio.h>

#ifndef _MATHS_H_
#define _MATHS_H_

int32_t newton_sqrt(int32_t x, int guess);

void vector_init(struct angle *v);
void vector_rot(struct angle *v, int angle);

#endif /*! _MATHS_H_ */
