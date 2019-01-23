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
#include "motion.h"
#include "LUT.h"
#include "ship.h"
#include "struct.h"
#include "projectile.h"
#include "objects.h"
#include "draw.h"
#include "monster.h"
#include "monsterprojectile.h"
#include "collision.h"
#include "menu.h"
#include "stage.h"
#include <string.h>
#include <stdlib.h>

#define ESC 0x1B

int main(void) {

    uart_init(1958400);
    uart_clear();

    // Initialize lcd & time
    lcd_init();
    time_init();
    RGB_init();
    RGB_set(0);

    // Clear the lcd
    uint8_t buffer[512];
    memset(buffer,0x00,512);

    // Clear the screen
    printf("%c[2J",ESC);

    // Create input array
    char input[2];
    input[0] = 0x00;
    input[1] = 0x00;

    // Matrix to draw text
    const uint8_t excelexe[6][58] = {
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1},
    {1,1,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1},
    {1,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0},
    {1,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1},
    };

    const uint8_t menuonlcd[6][58] = {
    {1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,1,1,0},
    {1,1,0,1,1,0,1,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,0},
    };
    while(1) {

        // Default settings
        int bullets = 20;
        int score = 0;
        int angle = 360;
        int reloadtime = 0;
        int reloading = 0;
        int toggledrift = 0;
        int drift = 0;
        int saveanglex = 0;
        int saveangley = 0;
        int nuke = 1;
        int dead = 0;
        int exitgame = 0;

        // Draw main menu
        menu_main_draw(buffer);

        // Set stage
        int stage = menu(buffer,input,menuonlcd);

        // Projectile variables
        int n = 0;
        int mn= 0;

        char scores[100] = "";

        // Create necessary structures
        struct angle shipangle = { 1,0 };
        struct spaceship playership;
        struct projectile playerprojectile[20];
        struct planet planet[20] = {{ 0,0,0,0 }};
        struct monster monster[10];
        struct monsterprojectile monsterprojectile[20];
        struct bomb bomb[2];

        monster_init(monster);
        monsterprojectile_init(monsterprojectile);
        projectile_init(playerprojectile);
        bomb_init(bomb);
        vector_init(&shipangle);
        ship_init(&playership);

        // Initialize stage
        stage_init(stage, &playership, angle, planet);

        memset(buffer,0x00,512);
        lcd_push_buffer(buffer);

        while(1) {

            if (check_char(input, "b") == 0 || check_char(input, "B") == 0) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,41,6,excelexe,1);
                RGB_set(0);
                while(1) {
                    input[0] = uart_get_char();
                    if (check_char(input,"b") == 0 || check_char(input, "B") == 0) {
                        printf("%c[2J",ESC);
                        NVIC_EnableIRQ(TIM2_IRQn);
                        break;
                    }
                }
                stage_init(stage,&playership,angle,planet);
            }

            if (check_char(input, "p") == 0 || check_char(input, "P") == 0) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,53,6,menuonlcd,1);
                menu_pause_draw(buffer);
                while(1) {
                    input[0] = uart_get_char();
                    if (check_char(input,"p") == 0 || check_char(input, "P") == 0) {
                        printf("%c[2J",ESC);
                        memset(buffer,0x00,512);
                        NVIC_EnableIRQ(TIM2_IRQn);
                        stage_init(stage,&playership,angle,planet);
                        break;
                    }
                    else if (check_char(input,"e") == 0 || check_char(input,"E") == 0) {
                        menu_warning_draw(buffer);
                        while(1) {
                            input[0] = uart_get_char();
                            if (check_char(input,"1") == 0) {
                                exitgame = 1;
                                printf("%c[2J",ESC);
                                memset(buffer,0x00,512);
                                NVIC_EnableIRQ(TIM2_IRQn);
                                break;
                            }
                            else if (check_char(input,"2") == 0) {
                                menu_pause_draw(buffer);
                                break;
                            }
                        }
                    }
                    if (exitgame == 1) {
                        break;
                    }
                }
            }
            if (exitgame == 1) {
                break;
            }

            int flag = get_flag2();

            if (flag == 1) {

                // Read the time from the timer
                int hs = get_hs();

                input[0] = uart_get_char();
                // Check if the current pressed key is w / a / s / d

                // Move in the direction of the ship
                if (check_char(input,"w") == 0 || check_char(input,"W") == 0) {
                    ship_clear(&playership,angle);
                    ship_pos(&playership,&shipangle);
                    ship_draw(&playership,angle);
                    toggledrift = 1;
                    drift = 0;
                    saveanglex = shipangle.x;
                    saveangley = shipangle.y;
                }

                if (toggledrift == 1 && hs % 5 == 0 && check_char(input,"w") != 0 && check_char(input,"W") != 0) {
                    drift++;
                    ship_clear(&playership,angle);
                    ship_drift(&playership,saveanglex,saveangley,drift);
                    ship_draw(&playership,angle);
                    if (drift >= 35) {
                        toggledrift = 0;
                        drift = 0;
                    }
                }

                // Turn the ship counter clockwise
                if (check_char(input,"a") == 0 || check_char(input,"A") == 0) {
                    ship_clear(&playership,angle);
                    angle -= 15;
                    if (angle == 0) angle = 360;
                    if (angle == 375) angle = 15;
                    vector_rot(&shipangle,angle);
                    ship_draw(&playership,angle);
                }

                // Turn the ship clockwise
                if (check_char(input,"d") == 0 || check_char(input,"D") == 0) {
                    ship_clear(&playership,angle);
                    angle += 15;
                    if (angle == 0) angle = 360;
                    if (angle == 375) angle = 15;
                    vector_rot(&shipangle,angle);
                    ship_draw(&playership,angle);
                }

                // Shoot missiles with space
                if (check_char(input," ") == 0) {
                    if (nuke > 0 && bomb->alive == 0) {
                        bomb_spawn(bomb,&playership,&shipangle);
                        nuke--;
                    }
                    else if (bomb->alive == 1) {
                        bomb_explode(bomb,monsterprojectile,monster);
                    }
                }

                if (check_char(input,"o") == 0) {
                    playership.hp--;
                }

                if (hs % 30 == 0 && bomb->alive == 1) {
                    bomb_clear(bomb);
                    bomb_pos(bomb);
                    bomb_draw(bomb);
                }

                // Reload the ammunition with r
                if (check_char(input,"r") == 0 || check_char(input,"R") == 0) {
                    if (reloading == 0 && bullets < 20) {
                        reloadtime = get_hs();
                        bullets = 0;
                        reloading = 1;
                    }
                }

                // Reload timer
                if (reloading == 1 && get_hs() > reloadtime + 50) {
                    bullets = 20;
                    reloading = 0;
                }

                // Read Joystick input
                int joyval = readIO();

                if (hs % 5 == 0) {
                    if ((joyval > 0) & (bullets > 0)) {
                        // Pressed down
                        if (joyval == 32) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,n,0);
                        }
                        // Down
                        else if (joyval == 1) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,n,2);
                        }
                        // Left
                        else if (joyval == 2) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,n,3);
                        }
                        // Right
                        else if (joyval == 3) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,n,1);
                        }
                        // Up
                        else if (joyval == 16) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,n,4);
                        }
                        bullets--;
                        n++;
                        if (n == 20)
                            n = 0;
                    }
                    // Check for projectile collision
                    bullet_monster_collision(playerprojectile,monster);
                    bullet_player_collision(monsterprojectile,&playership);

                    // Delete the monsters when they hit the edge of the screen
                }


                if (hs % 20 == 0) {
                        int i = 0;
                        for (i = 0; i < 4; i++) {
                            if ((monster+i)->x <= 20) {
                                monster_despawn(monster,i);
                                (monster+i)->alive = 0;
                                (monster+i)->animation = 15;
                                monster_clear(monster);
                            }
                        }
                    }

                if (hs % 5 == 0) {
                    int i = 0;
                    for (i = 0; i < 4; i++) {
                        if ((monster+i)->animation > 0) {
                            monster_animation(monster,i);
                        }
                    }
                }
                if (hs % 5 == 0) {
                // Check for player collision
                player_monster_collision(monster, &playership);
                player_stage_collision(&playership, angle, 1, 1, 400, 225);
                }
                // Move the enemies

                if (hs < 2000) {
                if (hs % 10 == 0) {
                monster_clear(monster);
                monster_pos(monster,playerprojectile);
                monster_draw(monster);
                }
                }
                else if (hs >= 2000) {
                if (hs % 5 == 0) {
                monster_clear(monster);
                monster_pos(monster,playerprojectile);
                monster_draw(monster);
                }
                }

                if (hs % 200 == 0) {
                    int i = 0;
                    for (i = 0; i < 10; i++) {
                        if ((monster+i)->alive == 1) {
                            monsterprojectile_spawn(monster+i,&playership, monsterprojectile,mn);
                            mn++;
                            if (mn == 20)
                                mn = 0;
                        }
                    }
                    score = score + 5;
                }

                // Projectile movement
                if (hs % 5 == 0) {
                    int i = 0;
                    for (i = 0; i < 20; i++) {
                        if (((playerprojectile+i)->x >= 399) || ((playerprojectile+i)->x <= 10) || ((playerprojectile+i)->y >= 224) || ((playerprojectile+i)->y <=10))
                            projectile_despawn(playerprojectile,i);
                        projectile_clear(playerprojectile,i);
                        projectile_pos(playerprojectile,planet,&shipangle,i);
                        projectile_draw(playerprojectile,i);
                    }
                    i = 0;
                    for (i = 0; i < 10; i++) {
                        if (((monsterprojectile+i)->x >= 399) || ((monsterprojectile+i)->x <= 10) || ((monsterprojectile+i)->y >= 224) || ((monsterprojectile+i)->y <=10))
                        monsterprojectile_despawn(monsterprojectile,i);
                    monsterprojectile_clear(monsterprojectile,i);
                    monsterprojectile_pos(monsterprojectile,i);
                    monsterprojectile_draw(monsterprojectile,i);
                    }
                }

                if (playership.hp < 0) {
                    playership.hp = 0;
                }

                if (playership.hp == 0) {
                    dead = 1;
                }

                if (nuke == 1) {
                    lcd_draw_nuke(buffer,1,4);
                }
                if (nuke == 0) {
                    memset(buffer,0x00,512);
                }

                char stg[1];

                sprintf(scores,"%04d", score);
                sprintf(stg," %d",stage);

                lcd_write_string("STAGE ",buffer,1,1);
                lcd_write_string(stg,buffer,31,1);
                lcd_write_string("SCORE: ",buffer,69,1);
                lcd_write_string(scores,buffer,104,1);
                lcd_draw_hearts(playership.hp,buffer,1,2);
                lcd_draw_bullets(bullets,buffer,1,3);

                if (bullets == 0) {
                        lcd_write_string("RELOAD",buffer,85,3);
                }
                if (bullets > 0) {
                        lcd_write_string("      ",buffer,85,3);
                }

                ship_health(&playership);

                // Draw to the LCD
                lcd_push_buffer(buffer);

                ship_health(&playership);



                flag2_update();
            }
            if (dead == 1) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,53,6,menuonlcd,1);
                menu_dead_draw(buffer);
                while(1) {
                    input[0] = uart_get_char();
                    if (check_char(input," ") == 0) {
                        NVIC_EnableIRQ(TIM2_IRQn);
                        exitgame = 1;
                        break;
                    }
                }
            }
            if (exitgame == 1) {
                break;
            }
        }
    }
}
/*
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
*/
