//
// Created by zy on 8/11/20.
//
#include "include/tio.h"

void print(char *s, ...) {
    va_list args;
    va_start(args, s);
    vprintf(s,args);
    printf("\n");
    va_end(args);
}