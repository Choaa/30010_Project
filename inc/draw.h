#ifndef _DRAW_H_
#define _DRAW_H_

#include "struct.h"
#include "stm32f30x_conf.h"
#include <stdio.h>

void draw_matrix(int cornerx, int cornery, int height, int length, const uint8_t sprite[][58], int drawempty);

#endif /*! _DRAW_H_ */
