/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 99 $
   Last changed by:    $Author: Mathias $
   Last changed date:  $Date:  25/01/2019 $
   ID:                 $Id: $
**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "ansi.h"
#include "mc_io.h"
#include "charset.h"
#include "lcd.h"
#include "input.h"
#include "maths.h"
#include "LUT.h"
#include "ship.h"
#include "struct.h"
#include "projectile.h"
#include "objects.h"
#include "draw.h"
#include "alien.h"
#include "alienprojectile.h"
#include "collision.h"
#include "menu.h"
#include "stage.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ESC 0x1B

int main(void) {

    // Set baud rate and clear FIFO buffer
    uart_init(1152000);
    uart_clear();

    // Initialize LCD, IRQ and RGB
    lcd_init();
    time_init();
    RGB_init();
    RGB_set(0);

    // Clear the LCD
    uint8_t buffer[512];
    memset(buffer,0x00,512);

    // Clear the console
    printf("%c[2J",ESC);

    // Create input array for reading key presses
    char input[2];
    input[0] = 0x00;
    input[1] = 0x00;

    // Matrix to draw text EXCEL.EXE
    const uint8_t excelexe[6][58] = {
    {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1},
    {1,1,1,1,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1},
    {1,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,0,0,0},
    {1,1,1,1,0,1,0,0,0,1,0,0,1,1,0,0,1,1,1,1,0,1,1,0,1,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,1},
    };

    // Matrix to draw text MENU ON LCD
    const uint8_t menuonlcd[6][58] = {
    {1,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,1,1,0},
    {1,1,0,1,1,0,1,0,0,0,0,1,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,1},
    {1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1,1,1,0,1,0,0,1,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,1,0},
    };

    // Variables that shouldn't be looped at all
    int stage;
    int stagevictory = 0;
    int highscore1 = 0;
    int highscore2 = 0;
    int highscore3 = 0;
    char high1[6] = "";
    char high2[6] = "";
    char high3[6] = "";

    while(1) {

        // Wipe the screen
        printf("%c[2J",ESC);

        // Default settings for certain variables
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

        // Projectile variables
        int pnum = 0;
        int apnum= 0;

        // Set the high scores so they can be read
        sprintf(high1,"%04d", highscore1);
        sprintf(high2,"%04d", highscore2);
        sprintf(high3,"%04d", highscore3);

        // Only loads the main menu at start of game or if you exit the stages
        if (stagevictory == 0) {
            // Draw main menu
            menu_main_draw(buffer);

            // Set stage level
            stage = menu(buffer,input,menuonlcd, high1, high2, high3);
        }

        // Ensures that you haven't won the stage before it began
        stagevictory = 0;

        // Create score counter
        char scores[6] = "";
        // Create stage counter
        char stg[1] = "";


        // Create necessary structures
        struct angle shipangle = { 1,0 };
        struct spaceship playership;
        struct projectile playerprojectile[20];
        struct planet planet[20] = {{ 0,0,0,0 }};
        struct alien alien[10];
        struct alienprojectile alienprojectile[20];
        struct bomb bomb[2];

        // Initialize game objects
        alien_init(alien);
        alienprojectile_init(alienprojectile);
        projectile_init(playerprojectile);
        bomb_init(bomb);
        vector_init(&shipangle);
        ship_init(&playership);

        // Initialize stage
        stage_init(stage, &playership, angle, planet);

        memset(buffer,0x00,512);
        lcd_push_buffer(buffer);

        srand(get_hs());
        // Set a random amount of extra time for the bomb spawn
        int randnuketime = rand() % ((1000 + 1 - 1) + 1);

        // Reset the timer
        time_set(0);

        while(1) {

            // Get the flag from the IRQ
            int flag = get_flag2();

            // Only run if the flag is raised (Every 1/100th of a second)
            if (flag == 1) {

                // Read the time from the timer
                int hs = get_hs();

                // Put the last keypress from the FIFO buffer into the input array
                input[0] = uart_get_char();

                // Set the alien wave patterns
                stage_waves(stage, alien, hs);

                // Move in the direction of the ship
                if (check_char(input,"w") == 0 || check_char(input,"W") == 0) {
                    ship_clear(&playership,angle);
                    ship_pos(&playership,&shipangle);
                    ship_draw(&playership,angle);
                    // Ensures that the ship will float after you release w at the angle of the ship
                    toggledrift = 1;
                    drift = 0;
                    saveanglex = shipangle.x;
                    saveangley = shipangle.y;
                }

                // Drift for a certain distance after releasing w
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

                // Launch NUKES with space and explode them if you've launched one
                if (check_char(input," ") == 0) {
                    if (nuke > 0 && bomb->alive == 0) {
                        bomb_spawn(bomb,&playership,&shipangle,angle);
                        nuke--;
                    }
                    else if (bomb->alive == 1) {
                        bomb_explode(bomb,alienprojectile,alien);
                    }
                }

                // Reload the ammunition with r
                if (check_char(input,"r") == 0 || check_char(input,"R") == 0) {
                    if (reloading == 0 && bullets < 20) {
                        reloadtime = get_hs();
                        bullets = 0;
                        reloading = 1;
                    }
                }

                // Update the position of the NUKE every 30/100th of a second
                if (hs % 30 == 0 && bomb->alive == 1) {
                    bomb_clear(bomb);
                    bomb_pos(bomb);
                    bomb_draw(bomb);
                }

                // Reload timer
                if (reloading == 1 && get_hs() > reloadtime + 50) {
                    bullets = 20;
                    reloading = 0;
                }

                // Read Joystick input
                int joyval = readIO();

                // Everything that should be called every 5/100th second
                if (hs % 5 == 0) {
                    // Shoot with the joystick in a certain direction
                    if ((joyval > 0) & (bullets > 0)) {
                        // Center - Shooting in the facing direction
                        if (joyval == 32) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,pnum,0,angle);
                        }
                        // Down - Shooting down
                        else if (joyval == 1) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,pnum,2,angle);
                        }
                        // Left - Shooting left
                        else if (joyval == 2) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,pnum,3,angle);
                        }
                        // Right - Shooting right
                        else if (joyval == 3) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,pnum,1,angle);
                        }
                        // Up - Shooting up
                        else if (joyval == 16) {
                            projectile_spawn(&playership,playerprojectile,&shipangle,pnum,4,angle);
                        }
                        // Remove a bullet every time you shoot
                        bullets--;
                        // Sets the projectile structure array index and loops it at 20
                        pnum++;
                        if (pnum == 20)
                            pnum = 0;
                    }

                    // Check for projectile collision
                    score += bullet_alien_collision(playerprojectile,alien)*10;
                    bullet_player_collision(alienprojectile,&playership,angle);

                    // Check for player collision
                    player_alien_collision(alien, &playership,angle);
                    player_stage_collision(&playership, angle, 1, 1, 400, 225);
                    nuke += player_pickup_collision(&playership, bomb);

                    // Ensure you can't have more than 1 nuke at a time
                    if (nuke > 1) {
                        nuke = 1;
                    }

                    // Ensure that you can't have less than 0 hp
                    if (playership.hp < 0) {
                        playership.hp = 0;
                    }

                    // Check for asteroid collision
                    asteroid_collision(&playership,playerprojectile,alienprojectile,alien,planet,bomb);

                    // Destroy the projectiles if they exit the game area
                    int i = 0;
                    for (i = 0; i < 20; i++) {
                        if (((playerprojectile+i)->x >= 380) || ((playerprojectile+i)->x <= 20) || ((playerprojectile+i)->y >= 205) || ((playerprojectile+i)->y <=20)) {
                            projectile_despawn(playerprojectile,i);
                        }
                        projectile_clear(playerprojectile,i);
                        projectile_pos(playerprojectile,planet,&shipangle,i);
                        projectile_draw(playerprojectile,i);
                    }
                    i = 0;
                    for (i = 0; i < 10; i++) {
                        if (((alienprojectile+i)->x >= 380) || ((alienprojectile+i)->x <= 20) || ((alienprojectile+i)->y >= 205) || ((alienprojectile+i)->y <=20)) {
                            alienprojectile_despawn(alienprojectile,i);
                        }
                    alienprojectile_clear(alienprojectile,i);
                    alienprojectile_pos(alienprojectile,i);
                    alienprojectile_draw(alienprojectile,i);
                    }
                    if (((bomb)->x >= 380) || ((bomb)->x <= 20) || ((bomb)->y >= 205) || ((bomb)->y <=20)) {
                        bomb_despawn(bomb);
                    }

                    // Destroy the aliens if they exit the game area
                    i = 0;
                    for (i = 0; i < 10; i++) {
                        if ((alien+i)->x <= 20) {
                            alien_despawn(alien,i);
                            (alien+i)->alive = 0;
                            (alien+i)->animation = 15;
                            alien_clear(alien);
                            score -= 10;
                        }
                    }

                    // Death animation for aliens
                    i = 0;
                    for (i = 0; i < 10; i++) {
                        if ((alien+i)->animation > 0) {
                            alien_animation(alien,i);
                        }
                    }
                }

                // Everything that should be called every 2. second
                if (hs % 200 == 0) {
                    // Make the aliens shoot
                    int i = 0;
                    for (i = 0; i < 10; i++) {
                        if ((alien+i)->alive == 1) {
                            alienprojectile_spawn(alien+i,&playership, alienprojectile,apnum);
                            apnum++;
                            if (apnum == 20) {
                                apnum = 0;
                            }
                        }
                    }

                    // Gives you 5 score
                    score += 5;
                }

                // Gradual speed increase in the aliens movement depending on the elapsed game time
                if (hs < 2000) {
                    if (hs % 10 == 0) {
                        alien_clear(alien);
                        alien_pos(alien,playerprojectile);
                        alien_draw(alien);
                    }
                }
                else if (hs >= 2000 && hs < 4000) {
                    if (hs % 6 == 0) {
                        alien_clear(alien);
                        alien_pos(alien,playerprojectile);
                        alien_draw(alien);
                    }
                }
                else if (hs >= 4000 && hs < 6000) {
                    if (hs % 3 == 0) {
                        alien_clear(alien);
                        alien_pos(alien,playerprojectile);
                        alien_draw(alien);
                    }
                }
                else if (hs >= 6000 && hs < 9000) {
                    if (hs % 2 == 0) {
                        alien_clear(alien);
                        alien_pos(alien,playerprojectile);
                        alien_draw(alien);
                    }
                }
                // Ends the stage at a certain time
                if (stage == 1) {
                    if (hs >= 5500) {
                        stagevictory = 1;
                    }
                }
                else if (stage == 2 || stage == 3) {
                    if (hs >= 9000) {
                        stagevictory = 1;
                    }
                }

                // Spawn a nuke in the interval of every 40-50 seconds at a pseudo-random position
                if (hs % (4000+randnuketime) == 0) {
                    bomb_create(bomb);
                }

                // Update the LCD
                // Draw a NUKE notification if you have one
                if (nuke == 1) {
                    lcd_draw_nuke(buffer,1,4);
                }
                if (nuke == 0) {
                    memset(buffer,0x00,512);
                }

                // Take the score and the stage so the LCD can process it
                sprintf(scores,"%04d", score);
                sprintf(stg," %d",stage);

                // Update all the info on the LCD
                lcd_write_string("STAGE ",buffer,1,1);
                lcd_write_string(stg,buffer,31,1);
                lcd_write_string("SCORE: ",buffer,69,1);
                lcd_write_string(scores,buffer,104,1);
                lcd_draw_hearts(playership.hp,buffer,1,2);
                lcd_draw_bullets(bullets,buffer,1,3);

                // Reload notification
                if (bullets == 0) {
                    lcd_write_string("RELOAD",buffer,85,3);
                }
                if (bullets > 0) {
                    lcd_write_string("      ",buffer,85,3);
                }

                // Draw to the LCD
                lcd_push_buffer(buffer);

                // Set the RGB to the ships health
                ship_health(&playership);

                // Check to see if the player is dead
                if (playership.hp == 0) {
                    dead = 1;
                }

                // Turn off the flag until next interrupt
                flag2_update();
            }

            // Boss key
            if (check_char(input, "b") == 0 || check_char(input, "B") == 0) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,41,6,excelexe,1);
                memset(buffer,0x00,512);
                RGB_set(0);
                while(1) {
                    // Unbosskey the game
                    input[0] = uart_get_char();
                    if (check_char(input,"b") == 0 || check_char(input, "B") == 0) {
                        printf("%c[2J",ESC);
                        NVIC_EnableIRQ(TIM2_IRQn);
                        break;
                    }
                }
                stage_init(stage,&playership,angle,planet);
            }

            // Pause key
            if (check_char(input, "p") == 0 || check_char(input, "P") == 0) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,53,6,menuonlcd,1);
                menu_pause_draw(buffer,scores);
                while(1) {
                    input[0] = uart_get_char();
                    // Unpause the game
                    if (check_char(input,"p") == 0 || check_char(input, "P") == 0) {
                        printf("%c[2J",ESC);
                        memset(buffer,0x00,512);
                        stage_init(stage,&playership,angle,planet);
                        NVIC_EnableIRQ(TIM2_IRQn);
                        break;
                    }
                    // Return to menu
                    else if (check_char(input,"e") == 0 || check_char(input,"E") == 0) {
                        menu_warning_draw(buffer);
                        while(1) {
                            input[0] = uart_get_char();
                            if (check_char(input,"1") == 0) {
                                exitgame = 1;
                                printf("%c[2J",ESC);
                                memset(buffer,0x00,512);
                                if (stage == 1) {
                                    if (score >= highscore1) {
                                        highscore1 = score;
                                    }
                                }
                                else if (stage == 2) {
                                    if (score >= highscore2) {
                                        highscore2 = score;
                                    }
                                }
                                else if (stage == 3) {
                                    if (score >= highscore3) {
                                        highscore3 = score;
                                    }
                                }
                                NVIC_EnableIRQ(TIM2_IRQn);
                                break;
                            }
                            else if (check_char(input,"2") == 0) {
                                menu_pause_draw(buffer,scores);
                                break;
                            }
                        }
                    }
                    if (exitgame == 1) {
                        break;
                    }
                }
            }

            // Death screen
            if (dead == 1) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,53,6,menuonlcd,1);
                menu_dead_draw(buffer,scores);
                if (stage == 1) {
                    if (score >= highscore1) {
                        highscore1 = score;
                    }
                }
                else if (stage == 2) {
                    if (score >= highscore2) {
                        highscore2 = score;
                    }
                }
                else if (stage == 3) {
                    if (score >= highscore3) {
                        highscore3 = score;
                    }
                }
                while(1) {
                    input[0] = uart_get_char();
                    if (check_char(input," ") == 0) {
                        exitgame = 1;
                        NVIC_EnableIRQ(TIM2_IRQn);
                        break;
                    }
                }
            }

            // Stage victory
            if (stagevictory == 1) {
                NVIC_DisableIRQ(TIM2_IRQn);
                printf("%c[2J",ESC);
                draw_matrix(3,3,53,6,menuonlcd,1);
                if (stage == 1) {
                    menu_victory_draw(buffer,scores,stg);
                    if (score >= highscore1) {
                        highscore1 = score;
                    }
                }
                else if (stage == 2) {
                    menu_victory_draw(buffer,scores,stg);
                    if (score >= highscore2) {
                        highscore2 = score;
                    }
                }
                else if (stage == 3) {
                    menu_gamevictory_draw(buffer,scores);
                    if (score >= highscore3) {
                        highscore3 = score;
                    }
                    stagevictory = 0;
                }
                stage += 1;
                while(1) {
                    input[0] = uart_get_char();
                    // Next stage
                    if (check_char(input,"1") == 0) {
                        exitgame = 1;
                        NVIC_EnableIRQ(TIM2_IRQn);
                        break;
                    }
                    // Return to menu
                    else if (check_char(input,"0") == 0 || (stage == 4 && check_char(input," ") == 0)) {
                        exitgame = 1;
                        stagevictory = 0;
                        NVIC_EnableIRQ(TIM2_IRQn);
                        break;
                    }
                }
            }

            // Checks if the stage should be exited
            if (exitgame == 1) {
                break;
            }
        }
    }
}
