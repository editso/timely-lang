//
// Created by zy on 8/7/20.
//
#include "parser.h"

void move(){
//    token = lexer_read();
}

struct parser* new_parser(Lexer* lexer){
    struct parser* parser = malloc(sizeof(struct parser));
    parser->lexer = lexer;
    parser->root = malloc(sizeof(Tree));
    return parser;
}


int parse(struct parser* parser){
    while (lexer_read(parser->lexer)->kind  != END){

    }
    return -1;
}