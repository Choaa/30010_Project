#include "stm32f30x_conf.h" // STM32 config
#include "collision.h"
#include "alien.h"
#include "alienprojectile.h"
#include "projectile.h"
#include "ship.h"
#include <string.h>

#define ALIENLENGTH 8
#define ALIENHEIGHT 6
#define PLAYERLENGTH 8
#define PLAYERRHEIGHT 8
#define NUKEDIAMETER 8
#define PLANETDIAMETER 12

int bullet_alien_collision(struct projectile *p, struct alien *a) {
    int i = 0;
    int j = 0;
    for (i = 0; i < 20; i++) {
        if ((p+i)->alive == 1) {
            for (j = 0; j < 10 ; j++) {
                if ((a+j)->alive == 1 && (p+i)->x >= (a+j)->x - ALIENLENGTH/2 && (p+i)->x <= (a+j)->x + ALIENLENGTH/2 && (p+i)->y >= (a+j)->y - ALIENHEIGHT/2 && (p+i)->y <= (a+j)->y + ALIENHEIGHT/2) {
                    projectile_despawn(p,i);
                    alien_despawn(a,j);
                    alien_animation(a,j);
                    return 10;
                }
            }
        }
        else {
            return 0;
        }
    }
}

void bullet_player_collision(struct alienprojectile *ap, struct spaceship *s) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        if ((ap+i)->alive == 1 && (ap+i)->x >= s->x - PLAYERLENGTH/2 && (ap+i)->x <= s->x + PLAYERLENGTH/2 && (ap+i)->y >= s->y - PLAYERRHEIGHT/2 && (ap+i)->y <= (s)->y + PLAYERRHEIGHT/2) {
            alienprojectile_despawn(ap,i);
            s->hp = s->hp - 1;
        }
    }
}

void player_alien_collision(struct alien *a, struct spaceship *s) {
    int i = 0;
    for (i = 0; i < 20; i++) {
        if ((a+i)->alive == 1 && s->x >= (a+i)->x - ALIENLENGTH/2 && s->x <= (a+i)->x + ALIENLENGTH/2 && s->y >= (a+i)->y - ALIENHEIGHT/2 && s->y <= (a+i)->y + ALIENHEIGHT/2) {
            alien_despawn(a,i);
            alien_animation(a,i);
            s->hp = s->hp - 1;
        }
    }
}

void player_stage_collision(struct spaceship *s, int angle, int leftx, int topy, int rightx, int bottomy) {
    if (s->x <= leftx+30) {
        ship_clear(s,angle);
        s->vx = 0;
        s->x = leftx + 31;
        ship_draw(s,angle);
    }
    if (s->y <= topy+12) {
        ship_clear(s,angle);
        s->vy = 0;
        s->y = topy + 13;
        ship_draw(s,angle);
    }
    if (s->x >= rightx-12) {
        ship_clear(s,angle);
        s->vx = 0;
        s->x = rightx - 20;
        ship_draw(s,angle);
    }
    if (s->y >= bottomy-12) {
        ship_clear(s,angle);
        s->vy = 0;
        s->y = bottomy - 13;
        ship_draw(s,angle);
    }
}

int player_pickup_collision(struct spaceship *s, struct bomb *b) {
    if ((b+1)->alive == 1 && s->x >= (b+1)->x - NUKEDIAMETER/2 && s->x <= (b+1)->x + NUKEDIAMETER/2 && s->y >= (b+1)->y - NUKEDIAMETER/2 && s->y <= (b+1)->y + NUKEDIAMETER/2) {
        bomb_clear(b+1);
        (b+1)->x = 2;
        (b+1)->y = 2;
        return 1;
    }
    else {
        return 0;
    }
}

void asteroid_collision(struct spaceship *s, struct projectile *p, struct alienprojectile *ap, struct planet *pla, struct bomb *b) {
    int i = 0;
    for (i = 0; i < 10; i++) {
        if ((pla+i)->active == 1) {
            int j = 0;
            for (j = 0; j < 10; j++) {
                if ((p+j)->alive == 1 && (p+j)->x >= (pla+i)->x - PLANETDIAMETER/2 && (p+j)->x <= (pla+i)->x + PLANETDIAMETER/2 && (p+j)->y >= (pla+i)->y - PLANETDIAMETER/2 && (p+j)->y <= (pla+i)->y + PLANETDIAMETER/2) {
                    projectile_despawn(p,j);
                    planet_draw(pla);
                }
                if ((ap+j)->alive == 1 && (ap+j)->x >= (pla+i)->x - PLANETDIAMETER/2 && (ap+j)->x <= (pla+i)->x + PLANETDIAMETER/2 && (ap+j)->y >= (pla+i)->y - PLANETDIAMETER/2 && (ap+j)->y <= (pla+i)->y + PLANETDIAMETER/2) {
                    alienprojectile_despawn(p,j);
                    planet_draw(pla);
                }
            }
            if (s->x >= (pla+i)->x - PLANETDIAMETER/2 && s->x <= (pla+i)->x + PLANETDIAMETER/2 && s->y >= (pla+i)->y - PLANETDIAMETER/2 && s->y <= (pla+i)->y + PLANETDIAMETER/2) {
                planet_draw(pla);
            }
            if (b->alive == 1 && b->x >= (pla+i)->x - PLANETDIAMETER/2 && b->x <= (pla+i)->x + PLANETDIAMETER/2 && b->y >= (pla+i)->y - PLANETDIAMETER/2 && b->y <= (pla+i)->y + PLANETDIAMETER/2) {
                bomb_despawn(b);
                planet_draw(pla);
            }
        }
    }
}
