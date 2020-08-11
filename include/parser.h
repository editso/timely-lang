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

#define GET_TOKEN(parser) (parser->token)

Parser* new_parser(Lexer* lexer);

void* parse_while(Parser* parser);

void* parse_try(Parser* parser);
void* parse_catch(Parser* parser);
void* parse_block(Parser* parser);

void* parse_expr(Parser* parser);

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



int parse(Parser* parser);

void runner(Parser* parser, Environment *env);

#endif //TIMELY_LANG_PARSER_H
