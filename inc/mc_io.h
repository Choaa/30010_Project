#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _MC_IO_H_
#define _MC_IO_H_

#define UART_BUFFER_LENGTH 256

int16_t readIO();
void RGB_init();
void RGB_set(int color);

int get_hs();

void time_init();
void time_set(int hs);
void time_update();

int get_flag();
void flag_update();
void flag_reset();

#endif /* _MC_IO_H_ */
