#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include <string.h>

#define ESC 0x1B

void fgcolor(int foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(int background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(int foreground, int background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  int type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {
// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr() {
  bgcolor(0);
  printf("%c[2J", ESC);
  printf("%c[H", ESC);
}

void clreol() {
  printf("%c[H", ESC);
  printf("%c[K", ESC);
}

void gotoxy(int x, int y) {
  printf("%c[%d;%dH", ESC, x, y);
}

void underline(int on) {
    if (on == 1)
        printf("%c[4m", ESC);
    else
        printf("%c[24m", ESC);
}

void blink(int on) {
    if (on == 1)
        printf("%c[5m", ESC);
    else
        printf("%c[25m", ESC);
}

void inverse(int on) {
    if (on == 1)
        printf("%c[7m", ESC);
    else
        printf("%c[27m", ESC);
}

void window(int x1, int y1, int x2, int y2, char title[], int on) {
    gotoxy(y1,x1);
    underline(0);
    blink(0);
    inverse(0);
    if (on == 0) {
        printf("%c%c",218,180);
        int a = (x2-x1-4)-strlen(title);
        inverse(1);
        int i = 1;
        printf("  %s",title);
        for (i = 1; i < a; i++) {
            printf(" ");
            }
        inverse(0);
        printf("%c%c",195,191);
        i = 1;
        for (i = 1; i < y2-y1 ; i++) {
            gotoxy(y1+i,x1);
            printf("%c",179);
            gotoxy(y1+i,x2);
            printf("%c",179);
        }
        gotoxy(y2,x1);
        printf("%c",192);
        i = 1;
        for (i = 1; i < x2-x1; i++)
            printf("%c",196);
        printf("%c",217);
    }
    else {
        printf("%c%c",201,185);
        int a = (x2-x1-4)-strlen(title);
        inverse(1);
        int i = 1;
        printf("  %s",title);
        for (i = 1; i < a; i++) {
            printf(" ");
            }
        inverse(0);
        printf("%c%c",204,187);
        i = 1;
        for (i = 1; i < y2-y1 ; i++) {
            gotoxy(y1+i,x1);
            printf("%c",186);
            gotoxy(y1+i,x2);
            printf("%c",186);
        }
        gotoxy(y2,x1);
        printf("%c",200);
        i = 1;
        for (i = 1; i < x2-x1; i++)
            printf("%c",205);
        printf("%c",188);
    }
}

void windowbasic(int x1, int y1, int x2, int y2, int on) {
    gotoxy(y1,x1);
    underline(0);
    blink(0);
    inverse(0);
    if (on == 0) {
        printf("%c",218);
        int i = 1;
        for (i = 1; i < x2-x1; i++)
            printf("%c",196);
        printf("%c",191);
        i = 1;
        for (i = 1; i < y2-y1 ; i++) {
            gotoxy(y1+i,x1);
            printf("%c",179);
            gotoxy(y1+i,x2);
            printf("%c",179);
        }
        gotoxy(y2,x1);
        printf("%c",192);
        i = 1;
        for (i = 1; i < x2-x1; i++)
            printf("%c",196);
        printf("%c",217);
    }
    else {
        printf("%c",201);
        int i = 1;
        for (i = 1; i < x2-x1 ; i++)
            printf("%c",205);
        printf("%c",187);
        i = 1;
        for (i = 1; i < y2-y1 ; i++) {
            gotoxy(y1+i,x1);
            printf("%c",186);
            gotoxy(y1+i,x2);
            printf("%c",186);
        }
        gotoxy(y2,x1);
        printf("%c",200);
        i = 1;
        for (i = 1; i < x2-x1; i++)
            printf("%c",205);
        printf("%c",188);
    }
}
