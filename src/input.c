#include "30010_io.h"
#include <string.h>

// Checks if a certain key is pressed
int check_char(char *in, char val[]) {
    int cmp = strncmp(in,val,1);
    return cmp;
    uart_clear();
}
