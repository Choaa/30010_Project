#include "stm32f30x_conf.h"
#include "struct.h"
#include "objects.h"
#include "ship.h"

#ifndef _STAGE_H_
#define _STAGE_H_

void stage_init(int stage, struct spaceship *s, int angle, struct planet *p);
void stage_waves(int stage, struct alien *a, int time, int randwavetime);

#endif /*! _STAGE_H_ */
