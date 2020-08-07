//
// Created by zy on 8/7/20.
//
#include "parser.h"
#include "lexer.h"
#include <stdio.h>

Token* token;

void move(){
    token = read();
}

Tree* parse(char *s){
    lexer(s);
    move();
    while (token->kind != END){
        printf("stmt");
    }
    return (void*)0;
}
