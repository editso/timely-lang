//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_PARSER_H
#define TIMELY_LANG_PARSER_H
#include "tree.h"
#include "lexer.h"

typedef struct parser{
    Lexer *lexer;
    Tree *root;
    Token* token;
}Parser;

/**
 * 获取当前正在解析的Token
 */
#define GET_TOKEN(parser) (parser->token)



/**
 * 创建一个解析结构体
 * @param lexer 词法分析器指针
 * @return 成功返回这个结构体指针
 */
Parser* new_parser(Lexer* lexer);

/**
 * 解释器开始解析
 * @param parser 指针
 * @return 返回解析好后的语法树
 */
Tree* parse(Parser* parser);

/**
 * 类解析
 * @param parser 指针
 * @return 解析完成后返回一个与之对于的指针
 */
void* parse_class(Parser* parser);
/**
 * 标识符解析
 * @param parser 指针
 * @return 解析完成后返回一个与之对于的指针
 */
void* parse_id(Parser* parser);
/**
 * 函数解析
 * @param parser 指针
 * @return 解析完成后返回一个函数结构指针
 */
void* parse_fun(Parser* parser);
/**
 * while 循环
 * @param parser 指针
 * @return 解析完成后返回一个与之对于的指针
 */
void* parse_while(Parser* parser);
/**
 * 异常处理
 * @param parser 指针
 * @return 解析完成后返回一个与之对于的指针
 */
void* parse_try(Parser* parser);
void* parse_catch(Parser* parser);
/**
 * {}代码块儿解析
 * @param parser 指针
 * @return 解析完成后返回一个与之对于的指针
 */
void* parse_block(Parser* parser);
/**
 * 表达式解析
 * @param parser 指针
 * @return 解析完成后返回一个与之对于的指针
 */
void* parse_expr(Parser* parser);
/**
 *  语句解析
 * @param parser
 * @return
 */
void *parse_stmt(Parser *parser);
/**
 * |
 */
void* parse_or(Parser* parser);
/**
 * ^
 */
void* parser_xor(Parser* parser);
/**
 * &
 */
void* parse_and(Parser* parser);
/**
 * !=, ==
 */
void* parse_eq(Parser* parser);
/**
 * << >>
 */
void* parse_bit_move(Parser *parser);
/**
 * +, -
 * @param parser
 * @return
 */
void* parse_add_sub(Parser* parser);
/**
 * *, /, %
 * @param parser
 */
void* parse_mul_div(Parser* parser);
/**
 * ++a, !b, --a
 */
void* parse_start(Parser* parser);
/**
 * a++, b--
 */
void* parse_end(Parser* parser);
/**
 * 1,2,3,5,a,b,c,d
 */
void* parse_constant(Parser* parser);

#endif //TIMELY_LANG_PARSER_H
