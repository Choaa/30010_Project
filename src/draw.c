#include "draw.h"

#define ESC 0x1B

void draw_matrix(int cornerx, int cornery, int length, int heigth, const uint8_t sprite[][58], int drawempty) {

    int i = 0;
    int n = 0;
    printf("%c[%d;%dH",ESC,cornery,cornerx);
    for (i = 0; i<length;i++) {
        for(n = 0; n<heigth;n++) {
            if (sprite[i][n] == 1)
                printf("%c",219);
            else if (sprite[i][n] == 0) {
                if (drawempty == 0)
                    printf(" ");
                else if (drawempty == 1)
                    printf("%c[1C",ESC);
            }
        }
        printf("%c[%d;%dH",ESC,1+i+cornery,cornerx);
    }
}
