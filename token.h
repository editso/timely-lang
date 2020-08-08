//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TOKEN_H
#define TIMELY_LANG_TOKEN_H


#define token_define static const int

token_define ID         = 200; // 标识符
token_define END        = 201; // 项目结束符
token_define IF         = 202; // if
token_define ELSE       = 203; // else
token_define WHILE      = 204; // while
token_define DO         = 205; // do
token_define FUN        = 206; // fun
token_define CLASS      = 207; // class
token_define NUMBER     = 208; // number

token_define PS         = 37; // %
token_define AND        = 38; // &
token_define OR         = 124;// |
token_define EM         = 33; // !
token_define XOR        = 94; // ^

token_define PS_EQ      = 180;// %=
token_define AND_EQ     = 181;// &=
token_define OR_EQ      = 182;// |=
token_define XOR_ER     = 183;// ^=

token_define MUL        = 42; // *
token_define ADD        = 43; // +
token_define MIN        = 45; // -
token_define DIV        = 47; // /

token_define MUL_EQ     = 170; // *=
token_define ADD_EQ     = 171; // +=
token_define MIN_EQ     = 172; // -=
token_define DIV_EQ     = 173; // /=
token_define ADD2       = 174; // ++
token_define MIN2       = 175; // --

token_define LE         = 60; // <
token_define EQ         = 61; // =
token_define BIG        = 62; // >

token_define LE_EQ      = 160; // <=
token_define BIG_EQ     = 161; // >=
token_define EQ2        = 163; // ==
token_define EM_EQ      = 164; // !=

token_define COLON      = 58; // :
token_define SEMI       = 59; // ;
token_define DOT        = 46; // .
token_define DQ         = 34; // "
token_define COMM       = 44; // ,

token_define OP_SQ_BRA  = 91; // [
token_define CL_SQ_BRA  = 93; // ]
token_define OP_BRA     = 40; // (
token_define CL_BRA     = 41; // )
token_define OP_FL_BRA  = 123; // {
token_define CL_FL_BRA  = 125; // }

// token
typedef struct {
    int kind;
    char *text;
    unsigned int col_pos;
    unsigned int row_pos;
}Token;


#endif //TIMELY_LANG_TOKEN_H
