#include "stm32f30x_conf.h"
#include "maths.h"
#include "LUT.h"
#include <stdlib.h>
#include <stdio.h>

#define FIX14_SHIFT 14
#define FIX14_MULT(a, b) ( (a)*(b) >> FIX14_SHIFT )
#define FIX14_DIV(a, b) ( ((a) << FIX14_SHIFT) / b )

// Calculate the Square root using Newton's method
int32_t newton_sqrt(int32_t x, int guess) {
    int i = 1;
    for(i = 1;i<10;i++) {
        guess = guess-(guess*guess-x)/(2*guess);
    }
    return guess;
}

// Initialize a vector by bitshifting
void vector_init(struct angle *v) {
    v->x = v->x << 14;
    v->y = v->y << 14;
}

// Rotate a vector
void vector_rot(struct angle *v, int angle) {
     int x = FIX14_MULT(1 << 14,calccos(angle)) - FIX14_MULT(0 << 14,calcsin(angle));
     int y = FIX14_MULT(1 << 14,calcsin(angle)) + FIX14_MULT(0 << 14,calccos(angle));
     v->x = x;
     v->y = y;
}
