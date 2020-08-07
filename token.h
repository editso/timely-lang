//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TOKEN_H
#define TIMELY_LANG_TOKEN_H


// token
typedef struct {
    int kind;
    char *text;
    unsigned int col_pos;
    unsigned int row_pos;
}Token;


#endif //TIMELY_LANG_TOKEN_H
