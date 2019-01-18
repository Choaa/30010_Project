#ifndef _LCD_H_
#define _LCD_H_

#include "stm32f30x_conf.h"
#include "charset.h"
#include <stdio.h>
#include <string.h>

void lcd_write_string(char str[], uint8_t* buffer, int slice, int line);
void lcd_draw_hearts(int amount, uint8_t* buffer, int pos, int row);
void lcd_draw_missiles(int amount, uint8_t* buffer, int pos, int row);
void lcd_draw_bullets(int amount, uint8_t* buffer, int pos, int row);

#endif /*! _LCD_H_ */
