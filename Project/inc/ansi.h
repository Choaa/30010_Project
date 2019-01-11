#include "stm32f30x_conf.h"
#include <stdio.h>

#ifndef _ANSI_H_
#define _ANSI_H_

#define UART_BUFFER_LENGTH 256

void fgcolor(int foreground);
void bgcolor(int background);
void color(int foreground, int background);

void clrscr();
void clreol();

void gotoxy(int x, int y);

void underline(int on);
void blink(int on);
void inverse(int on);

void window(int x1, int y1, int x2, int y2, char title[], int on);
void windowbasic(int x1, int y1, int x2, int y2, int on);

#endif /* _ANSI_H_ */
