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
token_define EMPTY      = 209; // 什么都没有

token_define PS         = 37; // %
token_define AND        = 38; // &
token_define OR         = 124;// |
token_define EM         = 33; // !
token_define XOR        = 94; // ^

token_define PS_EQ      = 180;// %=
token_define AND_EQ     = 181;// &=
token_define OR_EQ      = 182;// |=
token_define XOR_ER     = 183;// ^=
token_define OR2        = 184;// ||
token_define AND2       = 185;// &&


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


typedef struct{
    const int kind;
    const char* symbol;
}Symbol;


static const Symbol symbol_table[] = {
        {ADD2, "++"},
        {EQ2, "=="},
        {ADD_EQ, "+="},
        {AND_EQ,"&="},
        {OR_EQ, "|="},
        {MUL_EQ, "*="},
        {DIV_EQ, "/="},
        {MIN_EQ, "-="},
        {MIN2, "--"},
        {PS_EQ, "%="},
        {XOR_ER, "^="},
        {LE_EQ, "<="},
        {BIG_EQ, ">="},
        {EM_EQ, "!="},
        {OR2, "||"},
        {AND2, "&&"},
        {IF, "if"},
        {ELSE, "else"},
        {WHILE, "while"},
        {DO, "do"},
        {FUN, "fun"},
};

/**
 * 空符号
 */
static const  Symbol EMPTY_SYMBOL = {EMPTY};

/**
 * 符号表数量
 */
static const int symbol_count = sizeof(symbol_table) / sizeof(Symbol);

// token
typedef struct {
    int kind;
    char *text;
    unsigned int col_pos;
    unsigned int row_pos;
}Token;

/**
 * 查找符号
 * @return 没有找到返回 EMPTY_SYMBOL  否则被找到的符号
 */
Symbol find_symbol(char *symbol);

#endif //TIMELY_LANG_TOKEN_H
