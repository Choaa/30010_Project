#include "lcd.h"
#include <string.h>

void lcd_write_string(char str[], uint8_t* buffer, int slice, int line) {

    int counter = strlen(str);
    int a = 0;

    for (a = 0; a < counter; a++) {

        int i = 0;
        for (i = 0; i < 5; i++){
            memset(buffer+a*6+i+slice+(line-1)*128,character_data[str[a]-32][i],1);
        }
        memset(buffer+a*6,0x00,1);
    }
}

void lcd_draw_hearts(int amount, uint8_t* buffer, int pos, int row) {

    int i = 0;
    for (i = 0; i < amount; i++) {

        int offset = pos+i*8+(row-1)*128;

        memset(buffer+offset,0b00001100,1);
        memset(buffer+offset+1,0b00011110,1);
        memset(buffer+offset+2,0b00111110,1);
        memset(buffer+offset+3,0b01111100,1);
        memset(buffer+offset+4,0b00111110,1);
        memset(buffer+offset+5,0b00011110,1);
        memset(buffer+offset+6,0b00001100,1);
    }
}
