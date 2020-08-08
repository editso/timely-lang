//
// Created by zy on 8/8/20.
//
#include "basic.h"
#include "string.h"



void print(char *mat, ...){
    va_list args;
    va_list args1;
    va_start(args, mat);
    va_copy(args1, args);
    char buf[1 + vsnprintf(NULL, 0, mat, args)];
    va_end(args);
    vsnprintf(buf, sizeof(buf), mat, args1);
    va_end(args1);
    printf("%s\n", buf);
}


long to_number(struct list *list){
    char *buf = malloc(sizeof(char) * list->size);
    // 11110
    for (int i = 0; i < list->size; ++i) {
        buf[i] = *(char*)list_get(list, i);
    }
    long *n=malloc(sizeof(long));
    memcpy(n, buf, list->size);
    return *n;
}
