#include "stm32f30x_conf.h"
#include <stdio.h>
#include "struct.h"
#include "ansi.h"
#include "draw.h"
#include "menu.h"
#include "lcd.h"
#include "30010_io.h"


#define ESC 0x1B

void menu_main_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    printf("%c[2J",ESC);
    printf("%c[1;1H",ESC);
    printf("  Main menu\n");
    printf("1 Stage select\n");
    printf("2 Help");
    lcd_write_string("MAIN MENU",buffer,1,1);
    lcd_write_string("1. Stage select",buffer,1,2);
    lcd_write_string("2. Help",buffer,1,3);
    lcd_push_buffer(buffer);
}

void menu_start_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    printf("%c[2J",ESC);
    printf("%c[1;1H",ESC);
    printf("  Option 1\n");
    printf("1 Level 1\n");
    printf("2 Level 2\n");
    printf("3 Level 3\n");
    printf("4 Level 4\n");
    printf("5 Level 5\n");
    printf("6 Back");
    lcd_write_string("STAGE SELECT",buffer,1,1);
    lcd_write_string("1 2 3",buffer,98,2);
    lcd_write_string("4 5 6",buffer,98,3);
    lcd_write_string("7 8 9",buffer,98,4);
    lcd_write_string("0. Back",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_help_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    printf("%c[2J",ESC);
    printf("%c[1;1H",ESC);
    printf("  Option 2\n");
    printf("show help stuff\n");
    printf("1. Back");
    lcd_write_string("HELP",buffer,1,1);
    lcd_write_string("I am much help",buffer,1,2);
    lcd_write_string("1. Back",buffer,1,3);
    lcd_push_buffer(buffer);
}

int menu(uint8_t *buffer, char input[]) {
    int loadgame = 0;
    while(1) {
        input[0] = uart_get_char();
        if (check_char(input,"1") == 0) {
            menu_start_draw(buffer);
            while(1) {
                input[0] = uart_get_char();
                if (check_char(input,"1") == 0) {
                    loadgame = 1;
                    break;
                }

                if (check_char(input,"2") == 0) {
                    loadgame = 1;
                    break;
                }

                if (check_char(input,"3") == 0) {
                    loadgame = 1;
                    break;
                }

                if (check_char(input,"4") == 0) {
                    loadgame = 1;
                    break;
                }

                if (check_char(input,"5") == 0) {
                    loadgame = 1;
                    break;
                }

                if (check_char(input,"6") == 0) {
                    menu_main_draw(buffer);
                    break;
                }
            }
        }
        else if (check_char(input,"2") == 0) {
            menu_help_draw(buffer);
            while(1) {
                input[0] = uart_get_char();
                if (check_char(input,"1") == 0) {
                    menu_main_draw(buffer);
                    break;
                }
            }
        }
        if (loadgame == 1) {
            printf("%c[2J",ESC);
            break;
        }
    }
}
