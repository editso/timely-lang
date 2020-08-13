//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_LEXER_H
#define TIMELY_LANG_LEXER_H
#include "basic.h"
#include "token.h"
#include "list.h"
#include "stdio.h"


typedef struct lexer{
    /**
     * 源文件
     */
    char* source;
    FILE *file;
    unsigned int col_pos;
    unsigned int row_pos;
    int last_chr; // 最后一次的位置
    t_bool also; // 是否已经读完了
    List* tokens;
}Lexer;


Lexer* new_lexer(char *);

Token* lexer_read(Lexer*);

Token* lexer_peek(Lexer*, int);

#endif //TIMELY_LANG_LEXER_H
