#include <stdio.h>
#ifndef _MENU_H
#define _MENU_H

#include "struct.h"
#include "stm32f30x_conf.h"
#include <stdio.h>

void menu_main_draw(uint8_t *buffer);
void menu_start_draw(uint8_t *buffer);
void menu_help_draw(uint8_t *buffer);
void menu_help2_draw(uint8_t *buffer);
void menu_help3_draw(uint8_t *buffer);
void menu_pause_draw(uint8_t *buffer);
void menu_stage_draw(uint8_t *buffer, char *name);
void menu_warning_draw(uint8_t *buffer);
void menu_dead_draw(uint8_t *buffer);
int menu(uint8_t *buffer, char input[], const uint8_t me[][58]);


#endif /*! _MENU_H_ */


