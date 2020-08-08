//
// Created by zy on 8/7/20.
//
#include "ast/tree.h"
#include "lexer.h"
#ifndef TIMELY_LANG_PARSER_H
#define TIMELY_LANG_PARSER_H

typedef struct parser{
    struct lexer *lexer;
    struct Tree *root;
}Parser;

Parser* new_parser(Lexer* lexer);

int parse(Parser* parser);


#endif //TIMELY_LANG_PARSER_H
