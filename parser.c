//
// Created by zy on 8/14/20.
//
#include "include/parser.h"



/**
 * 移动 token
 * @param parser
 */
void move(Parser *parser) {
    if (stack_size(parser->stack) > 0) {
        parser->token = pop(parser);
    } else {
        parser->token = lexer_read(parser->lexer);
    }
}


/**
 * 跳过换行
 */
void break_newline(Parser *parser) {
    while (token(parser)->kind == NEWLINE) {
        move(parser);
    }
}

void bmove(Parser *parser) {
    move(parser);
    break_newline(parser);
}

void expect(Parser *parser, Kind kind) {
    if (token(parser)->kind != kind) {
        parse_error(parser, "expect %s but appeared %s",
                    get_kind_meta(kind).name,
                    get_kind_meta(token(parser)->kind).name);
    }
    move(parser);
}

Token *peek(Parser *parser) {
    Token *tok = lexer_read(parser->lexer);
    push(parser, tok);
    return tok;
}

bool is_modifier(Token *token) {
    switch (g_kind(token)) {
        case PUBLIC:
        case PROTECTED:
        case PRIVATE:
        case STATIC:
        case FINAL:
            return true;
        default:
            return false;
    }
}

bool is_basic_type(Token *token) {
    switch (g_kind(token)) {
        case INT:
        case CHAR:
        case FLOAT:
        case STATIC:
        case BOOL:
        case ANY:
            return true;
        default:
            return false;
    }
}

bool is_operator(Token *token) {
    switch (token->kind) {
        case ADD2:
        case SUB2:
        case BIG_EQ:
        case LE_EQ:
        case DIV_EQ:
        case SUB_EQ:
        case MUL_EQ:
        case MOD_EQ:
        case OR_EQ:
        case EM_EQ:
        case ADD_EQ:
        case AND_EQ:
        case XOR_EQ:
            return true;
        default:
            return false;
    }
}

Parser *new_parser(Lexer *lexer) {
    Parser *parser = new(Parser);
    parser->lexer = lexer;
    parser->tree = new_tree(new_list());
    parser->stack = new_stack();
    return parser;
}

// 开始解析
Tree *parse(Parser *parser) {
    bmove(parser);
    while (token(parser)->kind != END) {
        list_add(parser->tree->stmts, parse_stmt(parser));
        bmove(parser);
    }
    return parser->tree;
}

void *parse_stmt(Parser *parser) {
    Token *tok = token(parser);
    switch (tok->kind) {
        case INTERFACE:
        case ID:
        case CLASS:
        case FUN:
        case PROTECTED:
        case PRIVATE:
        case PUBLIC:
        case STATIC:
        case FINAL:
            return parse_modifier(parser);
        case IF:
            return parse_if(parser);
        case WHILE:
            return parse_while(parser);
        case TRY:
            return parse_try(parser);
        case SWITCH:
            return parse_switch(parser);
        case NEWLINE:
            return new_empty(tok);
        case ADD2:
        case SUB2:
        case BREAK:
        case RETURN:
        case NUMBER:
        case THIS:
        case DOT:
            // TODO 后期写
            return new_empty(token(parser));
        default:
            log_error("Illegal expression: %s", get_kind_meta(tok->kind).name);
    }
    return NULL;
}

void *parse_modifier(Parser *parser) {
    Token *tok = token(parser);
    List *modifiers = new_list();
    while (is_modifier(tok)) {
        list_add(modifiers, tok);
        bmove(parser);
        tok = token(parser);
    }
    return parse_id(parser, new_modifier(modifiers));
}

void *parse_variable(Parser *parser, Modifier *modifier) {
    Token *tok = token(parser);
    expect(parser, ID);
    break_newline(parser);
    Kind kid = token(parser)->kind;
    Type *var_type = NULL;
    if (kid == COLON) {
        bmove(parser);
        if (is_basic_type(token(parser))) {
            bmove(parser);
        } else {
            expect(parser, ID);
        }
        var_type = new_type(token(parser));
        kid = token(parser)->kind;
    } else if (kid != EQ) {
        break_newline(parser);
        parse_error(parser, "Variable type is ambiguous", "");
    }
    void *term = new_var_term(tok, NULL, var_type, modifier);
    if (is_operator(token(parser)) || kid == EQ) {
        if (kid == EQ) {
            bmove(parser);
        }
        term = new_var_term(tok, parse_expr(parser), var_type, modifier);
    }
    return term;
}

void *parse_all_variable(Parser *parser, Modifier *modifier) {
    void *variable = parse_variable(parser, modifier);
    if (token(parser)->kind != COMM)
        return variable;
    List *stmt = new_list();
    list_add(stmt, variable);
    while (true) {
        if (token(parser)->kind == COMM) {
            bmove(parser);
        } else {
            break;
        }
        list_add(stmt, parse_variable(parser, modifier));
    }
    return new_stmt(stmt);
}

void *parse_id(Parser *parser, Modifier *modifier) {
    Token *tok = token(parser);
    switch (g_kind(tok)) {
        case CLASS:
            bmove(parser);
            return parse_class(parser, modifier);
        case FUN:
            bmove(parser);
            return parse_fun(parser, modifier);
        case ID: {
            if (peek(parser)->kind == OP_BRA) {
                if (modifier->modifiers->size > 0)
                    
                    parse_error(parser, "Function cannot be modified by modifier","");
                free(modifier->modifiers);
                free(modifier);
                return parse_call(parser);
            }
            return parse_all_variable(parser, modifier);
        }
        default:
            
            parse_error(parser, "Unprocessable statement: %s", get_kind_meta(g_kind(tok)).name);
    }
}

void *parse_class(Parser *parser, Modifier *modifier) {
    Token *name = token(parser);
    expect(parser, ID);
    break_newline(parser);
    List *extends = new_list();
    // 解析继承关系
    if (token(parser)->kind == COLON) {
        bmove(parser);
        Token *super;
        while ((super = token(parser))->kind != OP_FL_BRA) {
            expect(parser, ID);
            list_add(extends, super);
            if (token(parser)->kind == COMM){
                bmove(parser);
            }
        }
    }
    BlockStmt *block = parse_class_block(parser);
    return new_class_stmt(name, extends, block, modifier);
}


void *parse_class_block(Parser *parser) {
    expect(parser, OP_FL_BRA);
    break_newline(parser);
    List *stmts = new_list();
    while (token(parser)->kind != CL_FL_BRA && token(parser)->kind != END) {
        list_add(stmts, parse_stmt(parser));
        bmove(parser);
    }
    expect(parser, CL_FL_BRA);
    return new_block_stmt(stmts);
}

void *parse_fun(Parser *parser, Modifier *modifier) {
    Token *name = token(parser);
    move(parser);
    expect(parser, OP_BRA);
    List *args = new_list();
    while (token(parser)->kind != CL_BRA) {
        list_add(args, parse_stmt(parser));
        if (token(parser)->kind != CL_BRA) {
            expect(parser, COMM);
        }
    }
    expect(parser, CL_BRA);
    void *block = parse_block(parser);
    return new_fun_stmt(name, args, block, modifier);
}

void *parse_block(Parser *parser) {
    break_newline(parser);
    expect(parser, OP_FL_BRA);
    List *stmts = new_list();
    break_newline(parser);
    while (token(parser)->kind != CL_FL_BRA) {
        list_add(stmts, parse_stmt(parser));
        if (token(parser)->kind == CL_FL_BRA)
            break;
        bmove(parser);
    }
    expect(parser, CL_FL_BRA);
    return new_block_stmt(stmts);
}

void *parse_call(Parser *parser) {
    Token *token = token(parser);
    List *args = new_list();
    move(parser);
    expect(parser, OP_BRA);
    while (token(parser)->kind != CL_BRA) {
        list_add(args, parse_expr(parser));
        if (token(parser)->kind == CL_BRA)break;
        move(parser);
        if (token(parser)->kind == COMM)
            move(parser);
    }
    expect(parser, CL_BRA);
    return new_call_term(new_constant_term(token), args);
}

void *parse_if(Parser *parser) {
    expect(parser, IF);
    break_newline(parser);
    expect(parser, OP_BRA);
    void *expr = parse_expr(parser);
    expect(parser, CL_BRA);
    void *block = parse_block(parser);
    void *else_expr = NULL;
    if (token(parser)->kind == ELSE)
        else_expr = parse_else(parser);
    return new_if_stmt(expr, block, else_expr);
}

void *parse_else(Parser *parser) {
    expect(parser, ELSE);
    if (token(parser)->kind == IF) {
        /**
         * if(expr){                 if(expr){
         *
         *
         * }else if(expr){   ==>     }else{
         *                               if(expr){
         *
         *                               }
         * }                         }
         *
         *
         */
        List* block = new_list();
        list_add(block, parse_if(parser));
        return new_else_stmt(new_block_stmt(block));
    }
    return new_else_stmt(parse_block(parser));
}


void *parse_while(Parser *parser) {
    expect(parser, WHILE);
    expect(parser, OP_BRA);
    void *expr = parse_expr(parser);
    expect(parser, CL_BRA);
    return new_while_stmt(expr, parse_block(parser));
}

void *parse_try(Parser *parser) {
    expect(parser, TRY);
    expect(parser, OP_FL_BRA);
    List *stmts = new_list();
    while (token(parser)->kind != CL_FL_BRA) {
        list_add(stmts, parse_stmt(parser));
        move(parser);
    }
    expect(parser, CL_FL_BRA);
    List *catch = new_list();
    while (token(parser)->kind == CATCH) {
        expect(parser, CATCH);
        Token *name = token(parser);
        expect(parser, ID);
        expect(parser, COLON);
        Token *type = token(parser);
        if (!is_basic_type(token(parser))) {
            expect(parser, ID);
        }
        list_add(catch, new_catch_stmt(new_var_term(name, NULL, new_type(type), NULL),
                                       parse_block(parser)));
    }
    void *finally = NULL;
    if (token(parser)->kind == FINALLY) {
        expect(parser, FINALLY);
        finally = parse_block(parser);
    }
    return new_try_stmt(stmts, catch, finally);
}


void *parse_switch(Parser *parser) {
    expect(parser, SWITCH);
    Token *id = token(parser);
//    out_token(token(parser));
    expect(parser, ID);
    expect(parser, OP_FL_BRA);
    List *case_stmt = new_list();
    List *block;
    void *def_expr = NULL;
    while (token(parser)->kind != CL_FL_BRA) {
        if (token(parser)->kind == END) {
            expect(parser, CL_FL_BRA);
        }
        if (def_expr != NULL) {
            parse_error(parser, "Invalid statement: %s", get_kind_meta(token(parser)->kind).name);
        }
        move(parser);
        if (token(parser)->kind == CASE) {
            expect(parser, CASE);
            void *constant = parse_constant(parser);
            expect(parser, COLON);
            if (token(parser)->kind == OP_FL_BRA) {
                list_add(case_stmt, new_case_stmt(constant, parse_block(parser)));
            } else {
                block = new_list();
                while (true) {
                    if (token(parser)->kind == CASE ||
                        token(parser)->kind == DEFAULT ||
                        token(parser)->kind == CL_FL_BRA)
                        break;
                    list_add(block, parse_stmt(parser));
                    move(parser);
                }
                list_add(case_stmt, new_block_stmt(block));
                push(parser, token(parser));
            }
        } else if (token(parser)->kind == DEFAULT) {
            move(parser);
            expect(parser, COLON);
            if (token(parser)->kind == OP_FL_BRA) {
                def_expr = parse_block(parser);
            } else {
                block = new_list();
                while (token(parser)->kind != END &&
                       token(parser)->kind != CL_FL_BRA &&
                       token(parser)->kind != CASE) {
                    list_add(block, parse_stmt(parser));
                    move(parser);
                }
                def_expr = new_block_stmt(block);
            }
        }
    }
    expect(parser, CL_FL_BRA);
    return new_switch_stmt(new_constant_term(id), case_stmt, def_expr);
}


void *parse_expr(Parser *parser) {
    return parse_logic(parser);
}

/**
 * &&,||
 */
void *parse_logic(Parser *parser) {
    void *left = parse_or(parser);
    Token *tok = token(parser);
    switch (token(parser)->kind) {
        case AND2:
        case OR2:
            move(parser);
            return new_binary_expr(left, tok, parse_or(parser));
        default:
            return left;
    }
}

/**
 * or
 */
void *parse_or(Parser *parser) {
    void *left = parse_xor(parser);
    Token *tok = token(parser);
    while (token(parser)->kind == OR) {
        tok = token(parser);
        move(parser);
        left = new_binary_expr(left, tok, parse_xor(parser));
    }
    return left;
}


void *parse_xor(Parser *parser) {
    void *left = parse_and(parser);
    Token *tok = token(parser);
    while (token(parser)->kind == XOR) {
        tok = token(parser);
        move(parser);
        left = new_binary_expr(left, tok, parse_and(parser));
    }
    return left;
}

/**
 *
 */
void *parse_and(Parser *parser) {
    void *left = parse_equals(parser);
    Token *tok = token(parser);
    while (token(parser)->kind == AND) {
        tok = token(parser);
        move(parser);
        left = new_binary_expr(left, tok, parse_equals(parser));

    }
    return left;
}

/**
 * !=, ==, >, <, >= <=
 */
void *parse_equals(Parser *parser) {
    void *left = parse_bit_move(parser);
    Token *tok = token(parser);
    switch (token(parser)->kind) {
        case EM_EQ:
        case EQ2:
        case BIG:
        case LE:
        case LE_EQ:
        case BIG_EQ:
            move(parser);
            return new_binary_expr(left, tok, parse_bit_move(parser));
        default:
            return left;
    }
}

/**
 * << >>
 */
void *parse_bit_move(Parser *parser) {
    void *left = parse_add_sub(parser);
    Token *tok = token(parser);
    while (g_kind(tok) == LE2 || g_kind(tok) == BIG2) {
        tok = token(parser);
        move(parser);
        left = new_binary_expr(left, tok, parse_add_sub(parser));
    }
    return left;
}

/**
 * + -
 */
void *parse_add_sub(Parser *parser) {
    void *left = parse_mul_div(parser);
    Token *tok = token(parser);
    while (g_kind(tok) == ADD || g_kind(tok) == SUB) {
        tok = token(parser);
        move(parser);
        left = new_binary_expr(left, tok, parse_mul_div(parser));
    }
    return left;
}

/**
 * * /
 */
void *parse_mul_div(Parser *parser) {
    void *left = parse_start(parser);
    Token *tok = token(parser);
    while (g_kind(tok) == MUL || g_kind(tok) == DIV) {
        tok = token(parser);
        move(parser);
        left = new_binary_expr(left, tok, parse_start(parser));
    }
    return left;
}

/**
 * ++, --, !, ~,-
 */
void *parse_start(Parser *parser) {
    void *left = NULL;
    Token *tok = token(parser);
    StartTerm *expr = NULL;
    void ***p;
    while (g_kind(tok) == AND2 || g_kind(tok) == SUB2) {
        tok = token(parser);
        move(parser);
        if (left == NULL) {
            expr = new_start_term(tok, NULL);
            p = expr->expr;
        } else {
            expr = new_start_term(tok, expr);
        }
    }
    switch (g_kind(tok)) {
        case EM:
        case REV:
        case SUB: {
            if (expr == NULL) {
                return new_start_term(tok, parse_end(parser));
            } else {
                expr = new_start_term(tok, expr);
            }
            break;
        }
        default:
            return parse_end(parser);
    }
    *p = parse_end(parser);
    return expr;
}

/**
 * ++, --, &,  [], (), .
 */
void *parse_end(Parser *parser) {
    void *left = parse_constant(parser);
    Token *tok = token(parser);
    switch (g_kind(tok)) {
        case AND2:
        case SUB2: {
            // ++, ----
            EndTerm *end = NULL;
            void **p;
            while (true) {
                switch (g_kind(tok)) {
                    case AND2:
                    case SUB2:
                        tok = token(parser);
                        move(parser);
                        if (end == NULL) {
                            end = new_end_term(tok, NULL);
                            p = end->expr;
                        } else {
                            end = new_end_term(tok, end);
                        }
                        continue;
                    default:
                        break;
                }
                if (end != NULL) {
                    *p = left;
                } else {
                    break;
                }
            }
            return end;
        }
        case AND:
            return new_end_term(tok, left);
        case OP_SQ_BRA: {
            move(parser);
            void *expr = parse_expr(parser);
            expect(parser, CL_FL_BRA);
            return new_array_subscript(left, expr);
        }
        case OP_BRA: {
            move(parser);
            List *args = new_list();
            while (token(parser)->kind != CL_BRA) {
                list_add(args, parse_expr(parser));
                move(parser);
                if (token(parser)->kind == COMM) {
                    move(parser);
                    continue;
                }
                if (token(parser)->kind != CL_BRA) {
                    
                    parse_error(parser, "Illegal expression: %s", get_kind_meta(tok->kind).name);
                }
            }
            expect(parser, CL_BRA);
            return new_call_term(left, args);
        }
        case DO: {
            move(parser);
            if (peek(parser)->kind != ID) {
                
                parse_error(parser, "Illegal expression: %s", get_kind_meta(tok->kind).name);
            }
            return new_select_member(left, parse_expr(parser));
        }
        default:
            return left;
    }
}

/**
 * 1,2,3,5,a,b,c,d
 */
void *parse_constant(Parser *parser) {
    Token *tok = token(parser);
    switch (g_kind(tok)) {
        case NUMBER:
        case FLOAT:
        case ID:
            move(parser);
            return new_constant_term(tok);
        default:
            parse_error(parser, "Illegal expression: %s", get_kind_meta(tok->kind).name);
    }
}
