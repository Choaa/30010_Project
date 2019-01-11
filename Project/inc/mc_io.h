#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _MC_IO_H_
#define _MC_IO_H_

#define UART_BUFFER_LENGTH 256

int16_t readIO();
void setLeeXd(int color);
void timer_init();
void time_init(int h, int m, int s, int hs);
int get_hs();
int get_s();
int get_m();
int get_h();
void time_update();

#endif /* _MC_IO_H_ */
