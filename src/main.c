/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "mc_io.h"
#include "charset.h"
#include "lcd.h"
#include "input.h"
#include <string.h>

#define ESC 0x1B

struct spaceship {
    int x,y,vx,vy;
};

void initship(struct spaceship *s) {
    s->x = 20;
    s->y = 20;
    s->vx = 0;
    s->vy = 0;
}

void shipspeed(struct spaceship *s, int dir) {
    if (dir == 1) {
        int vx = s->vx + 1;
        if (vx < 3)
            s->vx = vx;
    }
    else if (dir == 2) {
        int vx = s->vx - 1;
        if (vx > -3)
            s->vx = vx;
    }
    else if (dir == 3) {
        int vy = s->vy + 1;
        s->vy = vy;
        if (vy < 3)
            s->vy = vy;
    }
    else if (dir == 4) {
        int vy = s->vy - 1;
        if (vy > -3)
            s->vy = vy;
    }
}

void shippos(struct spaceship *s) {
        int x = s->x + s->vx * 1;
        int y = s->y + s->vy * 1;
        if (x < 300)
            s->x = x;
        else if (x > 300)
            s->x = 2;
        if (y < 100)
            s->y = y;
        else if (y > 100)
            s->y = 2;
}

void drawship(struct spaceship *s) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c",169);
    printf("%c[H",ESC);
}

void clearship(struct spaceship *s) {
    printf("%c[%d;%dH",ESC,s->y,s->x);
    printf("%c",32);
    printf("%c[H",ESC);
}

int main(void)
{
    uart_init(115200);
    uart_clear();

    lcd_init();
    timer_init();

    uint8_t buffer[512];
    memset(buffer,0x00,512);

    int life1 = 3;
    int life2 = 3;
    int missiles1 = 3;
    int missiles2 = 3;

    windowbasic(1,1,301,101,1);

    struct spaceship myspaceship;

    initship(&myspaceship);

    while(1){

    // Create array that reads last pressed key
    char input[2];
    input[0] = uart_get_char();
    input[1] = 0x00;

    // Check if the current pressed key is w / a / s / d
    int cmpw = check_w(input);
    if (cmpw == 0) {
        shipspeed(&myspaceship,4);
    }

    int cmpa = check_a(input);
    if (cmpa == 0) {
        shipspeed(&myspaceship,2);
    }

    int cmps = check_s(input);
    if (cmps == 0) {
        shipspeed(&myspaceship,3);
    }

    int cmpd = check_d(input);
    if (cmpd == 0) {

        shipspeed(&myspaceship,1);
    }

    int cmpr = check_r(input);
    if (cmpr == 0) {
        life1 = 3;
        life2 = 3;
        missiles1 = 3;
        missiles2 = 3;
    }

    // Fill the LCD with 0 (Clearing it)
    memset(buffer,0x00,512);

    // Draw player 1 info
    lcd_write_string("Player 1",buffer,1,1);
    lcd_draw_hearts(life1,buffer,1,2,1);
    lcd_draw_missiles(missiles1,buffer,1,3,1);

    // Draw player 2 info
    lcd_write_string("Player 2",buffer,80,1);
    lcd_draw_hearts(life2,buffer,120,2,2);
    lcd_draw_missiles(missiles2,buffer,120,3,2);


    // Test timer
    char hundsec[50];
    int hs = get_hs();
    sprintf(hundsec,"%02d", hs);
    char second[50];
    int sec = get_s();
    sprintf(second, "%02d", sec);
    char minute[50];
    int minu = get_m();
    sprintf(minute, "%02d", minu);

    int a = 36;
    lcd_write_string(minute,buffer,1+a,4);
    lcd_write_string(":",buffer,12+a,4);
    lcd_write_string(second,buffer,16+a,4);
    lcd_write_string(".",buffer,27+a,4);
    lcd_write_string(hundsec,buffer,31+a,4);

    if (hs % 1 == 0) {
    clearship(&myspaceship);
    shippos(&myspaceship);
    drawship(&myspaceship);
    }

    // Draw to the LCD
    lcd_push_buffer(buffer);

    }
}
