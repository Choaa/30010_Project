#ifndef _INPUT_H_
#define _INPUT_H_

#include "stm32f30x_conf.h"
#include "charset.h"
#include <stdio.h>
#include <string.h>

int check_w(char *in);
int check_a(char *in);
int check_s(char *in);
int check_d(char *in);
int check_r(char *in);
int check_v(char *in);
int check_p(char *in);
int check_l(char *in);
int check_space(char *in);

#endif /*! _INPUT_H_ */
