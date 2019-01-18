#include "lcd.h"
#include <string.h>

// Check if w is pressed
int check_w(char *in) {
    char w[1] = "w";
    int cmp = strncmp(in,w,1);
    return cmp;
}

// Check if a is pressed
int check_a(char *in) {
    char a[1] = "a";
    int cmp = strncmp(in,a,1);
    return cmp;
}

// Check if s is pressed
int check_s(char *in) {
    char s[1] = "s";
    int cmp = strncmp(in,s,1);
    return cmp;
}

// Check if d is pressed
int check_d(char *in) {
    char d[1] = "d";
    int cmp = strncmp(in,d,1);
    return cmp;
}

// Check if r is pressed
int check_r(char *in) {
    char r[1] = "r";
    int cmp = strncmp(in,r,1);
    return cmp;
}

int check_v(char *in) {
    char v[1] = "v";
    int cmp = strncmp(in,v,1);
    return cmp;
}

int check_p(char *in) {
    char p[1] = "p";
    int cmp = strncmp(in,p,1);
    return cmp;
}

int check_l(char *in) {
    char l[1] = "l";
    int cmp = strncmp(in,l,1);
    return cmp;
}

// Check if space is pressed
int check_space(char *in) {
    char space[1] = " ";
    int cmp = strncmp(in,space,1);
    return cmp;
}
