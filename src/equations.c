#include "equations.h"

int32_t newton_sqrt(int32_t x, int guess) {
    int i = 1;
    for(i = 1;i<10;i++) {
        guess = guess-(guess*guess-x)/(2*guess);
    }
    return guess;
}
