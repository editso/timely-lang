//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_PARSER_H
#define TIMELY_LANG_PARSER_H
#include "ast/tree.h"
#include "lexer.h"

typedef struct parser{
    Lexer *lexer;
    Tree *root;
    Token* token;
}Parser;

#define GET_TOKEN(parser) (parser->token)

Parser* new_parser(Lexer* lexer);

int parse(Parser* parser);


#endif //TIMELY_LANG_PARSER_H
