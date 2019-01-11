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
#include <string.h>

#define ESC 0x1B

int main(void)
{
    uart_init(115200);
    uart_clear();

    int life = 3;
    char lives[100];

    while(1){

    // Check if the current pressed key is a
    char input[2];
    input[0] = uart_get_char();
    input[1] = 0x00;
    char a[2] = "a";
    int cmp = strncmp(input,a,1);
    if (cmp == 0)
        life--;

    // Fill the LCD with 0 (Clearing it)
    memset(buffer,0x00,512);

    // Draw current amount of lives
    lcd_draw_hearts(life,buffer,140,2);

    // Draw to the LCD
    lcd_push_buffer(buffer);

    }
}
