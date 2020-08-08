//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_LEXER_H
#define TIMELY_LANG_LEXER_H
#include "token.h"
#include "list.h"

typedef struct lexer{
    int fd;
    unsigned int cur_index;
    unsigned int cur_pos;
    unsigned int cur_line;
    struct list* tokens;
}Lexer;

Lexer* new_lexer(char *);

Token* lexer_read(struct lexer*);

Token* lexer_peek(struct lexer*, int);

#endif //TIMELY_LANG_LEXER_H
