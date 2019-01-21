#include "lcd.h"
#include "30010_io.h"
#include <string.h>

int check_char(char *in, char val[]) {
    int cmp = strncmp(in,val,1);
    return cmp;
    uart_clear();
}
