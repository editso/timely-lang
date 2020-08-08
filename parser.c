//
// Created by zy on 8/7/20.
//
#include "parser.h"

void move(Parser *parser){
    parser->token =  lexer_read(parser->lexer);
}

struct parser* new_parser(Lexer* lexer){
    struct parser* parser = malloc(sizeof(struct parser));
    parser->lexer = lexer;
    parser->root = malloc(sizeof(Tree));
    return parser;
}


int parse(Parser* parser){
    move(parser);
    while (parser->token->kind != END){
        print("kind: %d,  text: %s, line: %d, pos: %d, size: %d",
              parser->token->kind,
              parser->token->text,
              parser->token->row_pos,
              parser->token->col_pos,
              parser->lexer->tokens->size);
        move(parser);
    }
    return -1;
}

Tree expr(Parser *parser){

}




