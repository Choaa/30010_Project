#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _MENU_H
#define _MENU_H

void menu_main_draw(uint8_t *buffer);
void menu_start_draw(uint8_t *buffer);
void menu_help_draw(uint8_t *buffer);
void menu_help2_draw(uint8_t *buffer);
void menu_help3_draw(uint8_t *buffer);
void menu_pause_draw(uint8_t *buffer, char *score);
void menu_stage_draw(uint8_t *buffer, char *name);
void menu_warning_draw(uint8_t *buffer);
void menu_dead_draw(uint8_t *buffer, char *score);
void menu_victory_draw(uint8_t *buffer, char *score, char *stage);
void menu_gamevictory_draw(uint8_t *buffer, char *score);
void menu_score_draw(uint8_t *buffer, char *hs1, char *hs2, char *hs3);
int menu(uint8_t *buffer, char input[], const uint8_t me[][58], char *hs1, char *hs2, char *hs3);

#endif /*! _MENU_H_ */


