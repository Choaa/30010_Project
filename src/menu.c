#include "stm32f30x_conf.h"
#include "ansi.h"
#include "draw.h"
#include "menu.h"
#include "lcd.h"
#include "input.h"
#include "30010_io.h"
#include <stdio.h>

#define ESC 0x1B

void menu_main_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    lcd_write_string("MAIN MENU             ",buffer,1,1);
    lcd_write_string("1. STAGE SELECT       ",buffer,1,2);
    lcd_write_string("2. HIGH SCORES        ",buffer,1,3);
    lcd_write_string("3. HELP               ",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_start_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    lcd_write_string("STAGE SELECT         ",buffer,1,1);
    lcd_write_string("           1. STAGE 1",buffer,1,2);
    lcd_write_string("           2. STAGE 2",buffer,1,3);
    lcd_write_string("0. BACK    3. STAGE 3",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_help1_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    lcd_write_string("HELP           PAGE 1",buffer,1,1);
    lcd_write_string("FORWARD: W, TURN: A/D",buffer,1,2);
    lcd_write_string("BOSSKEY: B, PAUSE:  P",buffer,1,3);
    lcd_write_string("0. BACK       1. NEXT",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_help2_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    lcd_write_string("HELP           PAGE 2",buffer,1,1);
    lcd_write_string("FIXED FIRE: JOYCENTER",buffer,1,2);
    lcd_write_string("DIR FIRE:      JOYDIR",buffer,1,3);
    lcd_write_string("0. BACK       1. NEXT",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_help3_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    lcd_write_string("HELP           PAGE 3",buffer,1,1);
    lcd_write_string("RELOAD:             R",buffer,1,2);
    lcd_write_string("NUKE:           SPACE",buffer,1,3);
    lcd_write_string("0. BACK              ",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_stage_draw(uint8_t *buffer, char *name) {
    memset(buffer,0x00,512);
    lcd_write_string(name,buffer,1,1);
    lcd_write_string("PLAY THIS STAGE?     ",buffer,1,2);
    lcd_write_string("1. YES!              ",buffer,1,3);
    lcd_write_string("0. BACK              ",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_score_draw(uint8_t *buffer, char *hs1, char *hs2, char *hs3) {
    memset(buffer,0x00,512);
    lcd_write_string("HIGHSCORES           ",buffer,1,1);
    lcd_write_string("STAGE 1: ",buffer,55,2);
    lcd_write_string(hs1,buffer,104,2);
    lcd_write_string("STAGE 2: ",buffer,55,3);
    lcd_write_string(hs2,buffer,104,3);
    lcd_write_string("0. BACK  STAGE 3: ",buffer,1,4);
    lcd_write_string(hs3,buffer,104,4);
    lcd_push_buffer(buffer);
}

void menu_pause_draw(uint8_t *buffer, char *score) {
    memset(buffer,0x00,512);
    lcd_write_string("PAUSE MENU           ",buffer,1,1);
    lcd_write_string("YOUR SCORE IS: ",buffer,1,2);
    lcd_write_string(score,buffer,84,2);
    lcd_write_string("PRESS P TO UNPAUSE   ",buffer,1,3);
    lcd_write_string("PPRESS E TO EXIT GAME",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_warning_draw(uint8_t *buffer) {
    memset(buffer,0x00,512);
    lcd_write_string("WARNING!             ",buffer,1,1);
    lcd_write_string("REALLY WANT TO EXIT? ",buffer,1,2);
    lcd_write_string("1. YES          2. NO",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_dead_draw(uint8_t *buffer, char *score) {
    memset(buffer,0x00,512);
    lcd_write_string("YOU DIED!            ",buffer,1,1);
    lcd_write_string("YOUR SCORE WAS: ",buffer,1,2);
    lcd_write_string(score,buffer,90,2);
    lcd_write_string("PLEASE PRESS SPACE TO",buffer,1,3);
    lcd_write_string("RETURN TO THE MENU   ",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_victory_draw(uint8_t *buffer, char *score, char *stage) {
    memset(buffer,0x00,512);
    lcd_write_string("CONGRATULATIONS!     ",buffer,1,1);
    lcd_write_string("YOU SURVIVED STAGE ",buffer,1,2);
    lcd_write_string(stage,buffer, 108,2);
    lcd_write_string("YOUR SCORE WAS: ",buffer,1,3);
    lcd_write_string(score,buffer,90,3);
    lcd_write_string("0. Menu 1. NEXT STAGE",buffer,1,4);
    lcd_push_buffer(buffer);
}

void menu_gamevictory_draw(uint8_t *buffer, char *score) {
    memset(buffer,0x00,512);
    lcd_write_string("CONGRATULATIONS!     ",buffer,1,1);
    lcd_write_string("YOU WON THE GAME!!!!!",buffer,1,2);
    lcd_write_string("YOUR SCORE WAS: ",buffer,1,3);
    lcd_write_string(score,buffer,90,3);
    lcd_write_string("SPACE TO CELEBRATE!!!",buffer,1,4);
    lcd_push_buffer(buffer);
}

int menu(uint8_t *buffer, char input[], const uint8_t me[][58], char *hs1, char *hs2, char *hs3) {
    int loadgame = 0;

    draw_matrix(3,3,53,6,me,1);

    while(1) {
        input[0] = uart_get_char();
        if (check_char(input,"1") == 0) {
            menu_start_draw(buffer);
            while(1) {
                input[0] = uart_get_char();
                if (check_char(input,"1") == 0) {
                    menu_stage_draw(buffer,"STAGE 1");
                    while(1) {
                        input[0] = uart_get_char();
                        if (check_char(input,"1") == 0) {
                            loadgame = 1;
                            break;
                        }
                        else if (check_char(input,"0") == 0) {
                            menu_start_draw(buffer);
                            break;
                        }
                    }
                }
                else if (check_char(input,"2") == 0) {
                    menu_stage_draw(buffer,"STAGE 2");
                    while(1) {
                        input[0] = uart_get_char();
                        if (check_char(input,"1") == 0) {
                            loadgame = 2;
                            break;
                        }
                        else if (check_char(input,"0") == 0) {
                            menu_start_draw(buffer);
                            break;
                        }
                    }
                }
                else if (check_char(input,"3") == 0) {
                    menu_stage_draw(buffer,"STAGE 3");
                    while(1) {
                        input[0] = uart_get_char();
                        if (check_char(input,"1") == 0) {
                            loadgame = 3;
                            break;
                        }
                        else if (check_char(input,"0") == 0) {
                            menu_start_draw(buffer);
                            break;
                        }
                    }
                }
                else if (check_char(input,"0") == 0) {
                    menu_main_draw(buffer);
                    break;
                }
                if (loadgame > 0) {
                    break;
                }
            }
        }
        else if (check_char(input,"2") == 0) {
            menu_score_draw(buffer, hs1, hs2, hs3);
            while(1) {
                input[0] = uart_get_char();
                if (check_char(input,"0") == 0) {
                    menu_main_draw(buffer);
                    break;
                }
            }
        }
        else if (check_char(input,"3") == 0) {
            menu_help1_draw(buffer);
            while(1) {
                input[0] = uart_get_char();
                if (check_char(input,"0") == 0) {
                    menu_main_draw(buffer);
                    break;
                }
                else if (check_char(input,"1") == 0) {
                    menu_help2_draw(buffer);
                    while(1) {
                        input[0] = uart_get_char();
                        if (check_char(input,"0") == 0) {
                            menu_help1_draw(buffer);
                            break;
                        }
                        else if (check_char(input,"1") == 0) {
                            menu_help3_draw(buffer);
                            while(1) {
                                input[0] = uart_get_char();
                                if (check_char(input,"0") == 0) {
                                    menu_help2_draw(buffer);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (loadgame > 0) {
            printf("%c[2J",ESC);
            break;
        }
    }
    return loadgame;
}

