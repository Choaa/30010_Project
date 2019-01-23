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
    int offset;
    for (i = 0; i < amount; i++) {
        offset = pos+i*8+(row-1)*128;

        memset(buffer+offset,0b00001100,1);
        memset(buffer+offset+1,0b00011110,1);
        memset(buffer+offset+2,0b00111110,1);
        memset(buffer+offset+3,0b01111100,1);
        memset(buffer+offset+4,0b00111110,1);
        memset(buffer+offset+5,0b00011110,1);
        memset(buffer+offset+6,0b00001100,1);
    }

    i = 3;
    for (i = 3; i > amount; i--) {
        offset = pos+(i-1)*8+(row-1)*128;

        memset(buffer+offset,0b00001100,1);
        memset(buffer+offset+1,0b00010010,1);
        memset(buffer+offset+2,0b00100010,1);
        memset(buffer+offset+3,0b01000100,1);
        memset(buffer+offset+4,0b00100010,1);
        memset(buffer+offset+5,0b00010010,1);
        memset(buffer+offset+6,0b00001100,1);
    }
}

void lcd_draw_nuke(uint8_t* buffer, int pos, int row) {
    int offset;
    offset = pos+(row-1)*128;

    memset(buffer+offset,0b00001000,1);
    memset(buffer+offset+1,0b10001100,1);
    memset(buffer+offset+2,0b11001110,1);
    memset(buffer+offset+3,0b11100000,1);
    memset(buffer+offset+4,0b11001110,1);
    memset(buffer+offset+5,0b10001100,1);
    memset(buffer+offset+6,0b00001000,1);

    lcd_write_string("NUKE READY",buffer,pos+10,row);

    memset(buffer+offset+71,0b00001000,1);
    memset(buffer+offset+72,0b10001100,1);
    memset(buffer+offset+73,0b11001110,1);
    memset(buffer+offset+74,0b11100000,1);
    memset(buffer+offset+75,0b11001110,1);
    memset(buffer+offset+76,0b10001100,1);
    memset(buffer+offset+77,0b00001000,1);
}

void lcd_draw_bullets(int amount, uint8_t* buffer, int pos, int row) {
    int offset;
    int i = 0;
    for (i = 0; i < amount; i++) {
        offset = pos+i*4+(row-1)*128;

        memset(buffer+offset,0b01111100,1);
        memset(buffer+offset+1,0b01111110,1);
        memset(buffer+offset+2,0b01111100,1);
    }
    i = 20;
    for (i = 20; i > amount; i--) {
        offset = pos+(i-1)*4+(row-1)*128;

        memset(buffer+offset,0b01111100,1);
        memset(buffer+offset+1,0b01000010,1);
        memset(buffer+offset+2,0b01111100,1);
    }
}
