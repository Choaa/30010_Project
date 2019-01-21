#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "ansi.h"
#include "collision.h"
#include "struct.h"
#include "monster.h"
#include "monsterprojectile.h"
#include "projectile.h"
#include <string.h>

#define MONSTERLENGTH 10
#define MONSTERHEIGHT 7
#define PLAYERLENGTH 10
#define PLAYERRHEIGHT 10

void bullet_monster_collision(struct projectile *p, struct monster *m) {
    int i = 0;
    int n = 0;
    for (i=0; i < 20 ;i++) {
        if ((p+i)->alive == 1) {
            for (n=0; n < 10 ;n++) {
                if ((m+n)->alive == 1) {
                    if ((p+i)->x >= (m+n)->x - MONSTERLENGTH/2 && (p+i)->x <= (m+n)->x + MONSTERLENGTH/2 && (p+i)->y >= (m+n)->y - MONSTERHEIGHT/2 && (p+i)->y <= (m+n)->y + MONSTERHEIGHT/2) {
                        projectile_despawn(p,i);
                        monster_despawn(m,n);
                    }
                }
            }
        }
    }
}

void bullet_player_collision(struct monsterprojectile *p, struct spaceship *s) {
    int n = 0;
    for (n=0;n<10;n++) {
        if ((p+n)->alive == 1) {
            if ((p+n)->x >= s->x - PLAYERLENGTH/2 && (p+n)->x <= s->x + PLAYERLENGTH/2 && (p+n)->y >= s->y - PLAYERRHEIGHT/2 && (p+n)->y <= (s)->y + PLAYERRHEIGHT/2)
            {
                monsterprojectile_despawn(p,n);
                s->hp = s->hp - 1;
            }
        }
    }
}

void player_monster_collision(struct monster *m, struct spaceship *s) {
    int n = 0;
    for (n=0;n<20;n++) {
        if (s->x >= (m+n)->x - MONSTERLENGTH/2 && s->x <= (m+n)->x + MONSTERLENGTH/2 && s->y >= (m+n)->y - MONSTERHEIGHT/2 && s->y <= (m+n)->y + MONSTERHEIGHT/2)
        {
            monster_despawn(m,n);
            s->hp = s->hp - 1;
        }
    }
}

