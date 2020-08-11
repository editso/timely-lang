//
// Created by zy on 8/7/20.
//
#include "parser.h"
#include "ast/eval.h"




void move(Parser *parser) {
    parser->token = lexer_read(parser->lexer);
}

Token* peek(Parser* parser, int index){
    return lexer_peek(parser->lexer, index);
}

void match(Parser *parser, Kind kind) {
    if (kind != GET_TOKEN(parser)->kind) {
        fprintf(stderr,"需要: %s, 出现: %s: (%d,%d)",
              get_kind_meta(kind).name,
              get_kind_meta(GET_TOKEN(parser)->kind).name,
              parser->token->row_pos,
              parser->token->col_pos);
        abort();
    }
    move(parser);
}

/**
 * 匹配一行结尾
 */
void match_end(Parser* parser){
    Token* token = GET_TOKEN(parser);
    if (token->kind != NEWLINE && token->kind != SEMI && token->kind != END){
        print("在第 %d 行结尾需要 ';' 或另起一行(%d,%d),当前: %s",
              token->row_pos,
              token->row_pos,
              token->col_pos,
              token->text);
        abort();
    }
    move(parser);
}

struct parser *new_parser(Lexer *lexer) {
    struct parser *parser = malloc(sizeof(struct parser));
    parser->lexer = lexer;
    parser->root = new_tree(new_list());
    return parser;
}


void *parse_stmt(Parser *parser) {
    Token *token;
    switch ((token = GET_TOKEN(parser))->kind) {
        case COMM:
            move(parser);
        case ID: {
            if (peek(parser, 0)->kind == EQ){
                move(parser);
                move(parser);
                void* var = new_var_term(token, parse_expr(parser));
                match_end(parser);
                return var;
            }
            out_token(token);
            return parse_expr(parser);
        }
        case FUN:{
            move(parser);
            struct list *args = new_list();
            if (peek(parser,0)->kind != OP_FL_BRA){
                match(parser, OP_BRA);
                while (GET_TOKEN(parser)->kind != CL_BRA){
                    if (GET_TOKEN(parser)->kind == COMM){
                        move(parser);
                        continue;
                    }
                    list_add(args, parse_expr(parser));
                }
                match(parser, CL_BRA);
            }else{
                move(parser);
            }
            out_token(GET_TOKEN(parser));
            return new_fun_stmt(token,args, parse_block(parser));
        }
        case WHILE:
            return parse_while(parser);
        case TRY:
            return parse_try(parser);
        case SEMI:
            return new_empty(token);
        case NEWLINE:
            return new_empty(GET_TOKEN(parser));
        default:
            out_token(GET_TOKEN(parser));
            return NULL;
    }
}

int parse(Parser *parser) {
    move(parser);
    while (GET_TOKEN(parser)->kind != END) {
        list_add(parser->root->stmts, parse_stmt(parser));
        move(parser);
    }
    return -1;
}


void runner(Parser* parser){
    GET_EVAL(parser->root)->eval(NULL, parser->root);
}

void* parse_try(Parser* parser){
    move(parser);
    void* block = parse_block(parser);
    struct list *stmts = new_list();
    while (GET_TOKEN(parser)->kind == CATCH){
        list_add(stmts, parse_catch(parser));
    }
    void* stmt = NULL;
    if (GET_TOKEN(parser)->kind == FINALLY){
        move(parser);
        stmt  = parse_block(parser);
    }
    match_end(parser);
    return new_try_stmt(block, stmts, stmt);
}


void* parse_catch(Parser* parser){
    move(parser);
    match(parser, ID);
    ConstantTerm * var = new_constant_term(GET_TOKEN(parser));
    void* block = parse_block(parser);
    return new_catch_stmt(var, block);
}


void *parse_while(Parser *parser) {
    Token *token = GET_TOKEN(parser);
    move(parser);
    match(parser, OP_BRA);
    void* expr = parse_expr(parser);
    match(parser, CL_BRA);
    void* stmt = new_while_stmt(token, expr, parse_block(parser));
    return stmt;
}

void *parse_block(Parser *parser) {
    match(parser, OP_FL_BRA);
    struct list *stmts = new_list();
    while (GET_TOKEN(parser)->kind != CL_FL_BRA){
        list_add(stmts, parse_stmt(parser));
        move(parser);
    }
    match(parser, CL_FL_BRA);
    return new_block_stmt(stmts);
}


void *parse_expr(Parser *parser) {
    void* left = parse_or(parser);
    Token* token = GET_TOKEN(parser);
    while (t_true){
        // 解析二元表达式
        switch (token->kind) {
            case ADD:
            case MIN:
            case ADD_EQ:
            case MIN_EQ:
            case DIV_EQ:
            case DIV:
            case MUL:
            case MOD:
                token = GET_TOKEN(parser);
                move(parser);
                return new_binary_expr(left, token, parse_or(parser));
            default:
                return left;
        }
    }
}

/**
 * |
 */
void *parse_or(Parser *parser) {
    void* left = parser_xor(parser);
    Token* token = GET_TOKEN(parser);
    while (GET_TOKEN(parser)->kind == OR){
        token = GET_TOKEN(parser);
        move(parser);
        left = new_binary_expr(left, token, parser_xor(parser));
    }
    return left;
}

/**
 * ^
 */
void *parser_xor(Parser *parser) {
    void* left = parse_and(parser);
    Token* token = GET_TOKEN(parser);
    while (GET_TOKEN(parser)->kind == XOR){
        token = GET_TOKEN(parser);
        move(parser);
        left = new_binary_expr(left, token, parse_and(parser));
    }
    return left;
}

/**
 * &
 */
void *parse_and(Parser *parser) {
    void* left = parse_eq(parser);
    Token* token = GET_TOKEN(parser);
    while (GET_TOKEN(parser)->kind == AND){
        token = GET_TOKEN(parser);
        move(parser);
        left = new_binary_expr(left, token, parse_eq(parser));
    }
    return left;
}

/**
 * !=, ==
 */
void *parse_eq(Parser *parser) {
    void* left = parse_bit_move(parser);
    Token* token = GET_TOKEN(parser);
    switch (token->kind) {
        case EM_EQ:
        case EQ2:
            move(parser);
            return new_binary_expr(left, token, parse_bit_move(parser));
        default:
            return left;
    }
}

/**
 * << >>
 */
void *parse_bit_move(Parser *parser) {
    void* left = parse_add_sub(parser);
    Token* token = GET_TOKEN(parser);
    while (t_true){
        switch (token->kind) {
            case LE2:
            case BIG2:
                token = GET_TOKEN(parser);
                move(parser);
                return new_binary_expr(left, token, parse_add_sub(parser));
            default:
                return left;
        }
    }
}

/**
 * +, -
 * @param parser
 * @return
 */
void *parse_add_sub(Parser *parser) {
    void* left = parse_mul_div(parser);
    Token* token = GET_TOKEN(parser);
    while (t_true){
        switch (token->kind) {
            case ADD:
            case MIN:
                token = GET_TOKEN(parser);
                move(parser);
                return new_binary_expr(left, token, parse_mul_div(parser));
            default:
                return left;
        }
    }
}


/**
 * *, /, %
 * @param parser
 */
void *parse_mul_div(Parser *parser) {
    void* left = parse_start(parser);
    Token* token = GET_TOKEN(parser);
    while (t_true){
        switch (token->kind) {
            case MUL:
            case DIV:
            case MOD:
                token = GET_TOKEN(parser);
                move(parser);
                return new_binary_expr(left, token, parse_start(parser));
            default:
                return left;
        }
    }
}

/**
 * 前缀表达式
 * ++a, !b, --a
 */
void *parse_start(Parser *parser) {
    Token* token = GET_TOKEN(parser);
    while (t_true){
        switch (GET_TOKEN(parser)->kind) {
            case ADD2:
            case MIN2:
            case EM:
                token = GET_TOKEN(parser);
                move(parser);
                return new_start_term(token, parse_end);
            default:
                return parse_end(parser);
        }
    }
}

/**
 * 后缀表达式
 * a++, b--, (), .
 */
void *parse_end(Parser *parser) {

    void* left = parse_constant(parser);

    Token* token = GET_TOKEN(parser);
    while (t_true){
        switch (token->kind) {
            case ADD2:
            case MIN2:{
                move(parser);
                return new_end_term(token, left);
            }
            case OP_BRA:{
                token = GET_TOKEN(parser);
                struct list* args = new_list();
                do {
                    move(parser);
                    if (GET_TOKEN(parser)->kind == COMM){
                        move(parser);
                        continue;
                    }else if (GET_TOKEN(parser)->kind == CL_BRA){
                        break;
                    }
                    list_add(args, parse_expr(parser));
                    if (GET_TOKEN(parser)->kind == CL_BRA){
                        break;
                    }
                }while (t_true);
                match(parser, CL_BRA);
                match_end(parser);
                return new_call_term(left, args);
            }
            case DOT:
            default:
                return left;
        }
    }
}

/**
 * 1,2,3,5,a,b,c,d
 */
void *parse_constant(Parser *parser) {
    Token* token = GET_TOKEN(parser);
    switch (token->kind) {
        case ID:
        case NUMBER:
        case STRING:
            move(parser);
            return new_constant_term(token);
        default:
            printf("无法解析的表达式: %s, ",token->text);
            out_token(token);
            abort();
    }
}