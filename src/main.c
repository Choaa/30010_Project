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
#include <string.h>
#include <stdlib.h>

#define ESC 0x1B

/*
void draw_matrix(int cornerx, int cornery, int length, int heigth, int sprite[][1000], int drawempty);
*/
int main(void) {

    uart_init(1958400);
    uart_clear();

    lcd_init();
    time_init();

    uint8_t buffer[512];
    memset(buffer,0x00,512);

    char input[2];
    input[0] = 0x00;
    input[1] = 0x00;

    menu_main_draw(buffer);

    int stage = menu(buffer,input);

    int missiles = 3;
    int bullets = 20;
    int score = 0;
    int n = 0;
    int mn= 0;
    int angle = 360;

    struct angle shipangle = { 1,0 };
    struct spaceship playership;
    struct projectile playerprojectile[20];
    struct planet planet[20] = {{ 0,0,0,0 }};
    struct monster monster[10];
    struct monsterprojectile monsterprojectile[20];

    monster_init(monster);
    monsterprojectile_init(monsterprojectile);
    projectile_init(playerprojectile);
    planet_init(planet);
    ship_init(&playership);
    vector_init(&shipangle);
    RGB_init();

    RGB_set(2);

    ship_draw(&playership,angle);
    planet_draw(planet->x,planet->y);
    planet_draw((planet+1)->x,(planet+1)->y);

    srand(get_hs());
    int r1 = rand() % 200;
    int r2 = rand() % 200;
    int r3 = rand() % 200;

    monster_spawn(monster,350,r3,2);
    monster_spawn(monster,350,r2,1);
    monster_spawn(monster,350,r1,0);

    windowbasic(1,1,400,225,1);


    memset(buffer,0x00,512);

    while(1) {

        int flag = get_flag();

        if (flag == 1) {

            input[0] = uart_get_char();
            // Check if the current pressed key is w / a / s / d

            if (check_char(input,"w") == 0) {
                ship_clear(&playership,angle);
                ship_pos(&playership,&shipangle,0);
                ship_draw(&playership,angle);
            }

            if (check_char(input,"a") == 0) {
                ship_clear(&playership,angle);
                angle -= 15;
                if (angle == 0) angle = 360;
                if (angle == 375) angle = 15;
                vector_rot(&shipangle,angle);
                ship_draw(&playership,angle);
            }

            if (check_char(input,"d") == 0) {
                ship_clear(&playership,angle);
                angle += 15;
                if (angle == 0) angle = 360;
                if (angle == 375) angle = 15;
                vector_rot(&shipangle,angle);
                ship_draw(&playership,angle);
            }

            if (check_char(input,"p") == 0) {
                playership.hp--;
            }

            if (check_char(input,"l") == 0) {
                missiles--;
            }

            if (check_char(input,"r") == 0) {
                playership.hp = 3;
                missiles = 3;
                bullets = 20;
            }

            int hs = get_hs();

            // Joystick input
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

                bullet_monster_collision(playerprojectile,monster);
                bullet_player_collision(monsterprojectile,&playership);
                if (monster->x <= 20) {
                    monster_despawn(monster, 0);
                    }
                if ((monster+1)->x <= 20) {
                    monster_despawn(monster, 1);
                    }
                if ((monster+2)->x <= 20) {
                    monster_despawn(monster, 2);
                }

            }

            player_monster_collision(monster, &playership);

            if (hs % 10 == 0) {
            monster_clear(monster);
            monster_pos(monster,playerprojectile);
            monster_draw(monster);
            int i = 0;
                for (i = 0; i < 10; i++) {
                    if (((monsterprojectile+i)->x >= 399) || ((monsterprojectile+i)->x <= 10) || ((monsterprojectile+i)->y >= 224) || ((monsterprojectile+i)->y <=10))
                    monsterprojectile_despawn(monsterprojectile,i);
                monsterprojectile_clear(monsterprojectile,i);
                monsterprojectile_pos(monsterprojectile,i);
                monsterprojectile_draw(monsterprojectile,i);
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
                score++;
            }

            if (hs % 5 == 0) {
                int i = 0;
                for (i = 0; i < 20; i++) {
                    if (((playerprojectile+i)->x >= 399) || ((playerprojectile+i)->x <= 10) || ((playerprojectile+i)->y >= 224) || ((playerprojectile+i)->y <=10))
                        projectile_despawn(playerprojectile,i);
                    projectile_clear(playerprojectile,i);
                    projectile_pos(playerprojectile,planet,&shipangle,i);
                    projectile_draw(playerprojectile,i);
                }
            }

            char scores[100];
            sprintf(scores,"%06d", score);
            // Draw player 1 info
            lcd_write_string("Player 1",buffer,1,1);
            lcd_write_string(scores,buffer,92,1);
            if (playership.hp < 0) {
                playership.hp = 0;
            }
            lcd_draw_hearts(playership.hp,buffer,1,2);
            lcd_draw_missiles(missiles,buffer,1,3);
            lcd_draw_bullets(bullets,buffer,1,4);
            if (bullets == 0) {
                    lcd_write_string("RELOAD",buffer,85,4);
            }
            if (bullets > 0) {
                    lcd_write_string("      ",buffer,85,4);
            }
            ship_health(&playership);

            // Draw to the LCD
            lcd_push_buffer(buffer);

            flag_update();
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
