//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_LEXER_H
#define TIMELY_LANG_LEXER_H
#include "basic.h"
#include "token.h"
#include "list.h"
#include "stdio.h"
#define source(lexer) lexer->source


typedef struct lexer{
    /**
     * 源文件
     */
    char* source;
    FILE *file;
    uint col_pos;
    uint row_pos;
    int last_chr; // 当前字符
    List* tokens;
}Lexer;


Lexer* new_lexer(char *);

Token* lexer_read(Lexer*);

Token* lexer_peek(Lexer*, int);

#endif //TIMELY_LANG_LEXER_H
