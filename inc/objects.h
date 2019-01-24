#include "struct.h"
#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _OBJECTS_H_
#define _OBJECTS_H_

void planet_init(struct planet *p, int x, int y, int n);
void planet_draw(struct planet *p);

#endif /*! _EQUATIONS_H_ */
