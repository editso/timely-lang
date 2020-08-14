//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TOKEN_H
#define TIMELY_LANG_TOKEN_H


typedef enum {
    ID                  = 200, // 标识符
    END                 = 201, // 项目结束符
    IF                  = 202, // if
    ELSE                = 203, // else
    WHILE               = 204, // while
    DO                  = 205, // do
    FUN                 = 206, // fun
    CLASS               = 207, // class
    NUMBER              = 208, // number
    EMPTY               = 209, // 什么都没有
    CONST_STRING        = 210, // string
    NEWLINE             = 211, // newline \r\n
    IMPORT              = 212, // import
    DOT2                = 213, // ..
    RETURN              = 214, // return
    BREAK               = 215, // break
    CONTINUE            = 216, // continue
    TRY                 = 227, // try
    CATCH               = 228, // catch
    FINALLY             = 229, // finally
    ARROW_FUN           = 230, // =>
    SUPER               = 231, // super



    PUBLIC              = 232, // public
    PRIVATE             = 233, // private
    PROTECTED           = 234, // protected
    INTERFACE           = 235, // interface
    STATIC              = 236, // static



    // Basic Type
    ANY                 = 237, // any 任意类型
    INT                 = 238, // int
    FLOAT               = 239, // float
    CHAR                = 240, // char
    VOID                = 241, // void

    THIS                = 242, // this
    ENUM                = 243, // enum
    FINAL               = 245, // final
    SWITCH              = 246, // switch
    CASE                = 247, // case
    DEFAULT             = 248, // default


    CONST_CHAR          = 249,  // char 'c'

    MOD                 = 37,   // %
    AND                 = 38,   // &
    OR                  = 124,  // |
    EM                  = 33,   // !
    XOR                 = 94,   // ^

    MOD_EQ              = 180,  // %=
    AND_EQ              = 181,  // &=
    OR_EQ               = 182,  // |=
    XOR_EQ              = 183,  // ^=
    OR2                 = 184,  // ||
    AND2                = 185,  // &&

    MUL                 = 42,   // *
    ADD                 = 43,   // +
    SUB                 = 45,   // -
    DIV                 = 47,   // /

    MUL_EQ              = 170,  // *=
    ADD_EQ              = 171,  // +=
    SUB_EQ              = 172,  // -=
    DIV_EQ              = 173,  // /=
    ADD2                = 174,  // ++
    SUB2                = 175,  // --

    LE                  = 60,   // <
    EQ                  = 61,   // =
    BIG                 = 62,   // >

    LE_EQ               = 160,  // <=
    BIG_EQ              = 161,  // >=
    EQ2                 = 163,  // ==
    EM_EQ               = 164,  // !=
    LE2                 = 165,  // <<
    BIG2                = 166,  // >>

    COLON               = 58,   // :
    SEMI                = 59,   // ;
    DOT                 = 46,   // .
    DQ                  = 34,   // "
    COMM                = 44,   // ,


    OP_SQ_BRA           = 91,   // [
    CL_SQ_BRA           = 93,   // ]
    OP_BRA              = 40,   // (
    CL_BRA              = 41,   // )
    OP_FL_BRA           = 123,  // {
    CL_FL_BRA           = 125,  // }
}Kind;


/**
 * Kind 元信息
 */
typedef struct{
    Kind kind;
    const char* name;
}KindMeta;


static const KindMeta kind_table[] = {
        {ADD2,      "++"},
        {SUB2,      "--"},
        {EQ2,       "=="},
        {ADD_EQ,    "+="},
        {AND_EQ,    "&="},
        {OR_EQ,     "|="},
        {MUL_EQ,    "*="},
        {DIV_EQ,    "/="},
        {SUB_EQ,    "-="},
        {MOD_EQ,    "%="},
        {XOR_EQ,    "^="},
        {LE_EQ,     "<="},
        {BIG_EQ,    ">="},
        {EM_EQ,     "!="},
        {OR2,       "||"},
        {AND2,      "&&"},
        {IF,        "if"},
        {ELSE,      "else"},
        {WHILE,     "while"},
        {DO,        "do"},
        {FUN,       "fun"},
        {IMPORT,    "import"},
        {DOT2,      ".."},
        {RETURN,    "return"},
        {CONTINUE,  "continue"},
        {BREAK,     "break"},
        {TRY,       "try"},
        {CATCH,     "catch"},
        {FINALLY,   "finally"},
        {CLASS,     "class"},
        {ARROW_FUN, "=>"},
        {SUPER,     "super"},
        {ID,        "<标识符>"},
        {NEWLINE,   "<New Line>"},
        {PUBLIC,    "public"},
        {PRIVATE,   "private"},
        {PROTECTED, "protected"},
        {INTERFACE, "interface"},
        {STATIC,    "static"},
        {ANY,       "any"},
        {INT,       "int"},
        {FLOAT,     "float"},
        {CHAR,      "char"},
        {VOID,      "void"},
        {THIS,      "this"},
        {ENUM,      "enum"},
        {DEFAULT,   "default"},
        {SWITCH,    "switch"},
        {CASE, "case"}
};

/**
 * 空符号
 */
static const  KindMeta EMPTY_KIND = {EMPTY};

/**
 * 符号表数量
 */
static const int kind_count = sizeof(kind_table) / sizeof(KindMeta);

// token
typedef struct {
    Kind kind;
    char *text;
    unsigned int col_pos;
    unsigned int row_pos;
}Token;


/**
 * 查找符号
 * @return 没有找到返回 EMPTY_KIND  否则被找到的符号
 */
KindMeta find_kind(char *kind);


KindMeta get_kind_meta(Kind kind);


#endif //TIMELY_LANG_TOKEN_H
