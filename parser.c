//
// Created by zy on 8/14/20.
//
#include "include/parser.h"

void move(Parser *parser) {
    if (stack_size(parser->stack) > 0) {
        parser->token = pop(parser);
    } else {
        parser->token = lexer_read(parser->lexer);
    }
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

t_bool is_modifier(Token *token) {
    switch (kind(token)) {
        case PUBLIC:
        case PROTECTED:
        case PRIVATE:
        case STATIC:
        case FINAL:
            return t_true;
        default:
            return t_false;
    }
}

t_bool is_basic_type(Token *token) {
    switch (kind(token)) {
        case INT:
        case CHAR:
        case FLOAT:
        case STATIC:
        case BOOL:
        case ANY:
            return t_true;
        default:
            return t_false;
    }
}

t_bool is_operator(Token *token) {
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
            return t_true;
        default:
            return t_false;
    }
}

Parser *new_parser(Lexer *lexer) {
    Parser *parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->root = new_tree(new_list());
    parser->stack = new_stack();
    return parser;
}

Tree *parse(Parser *parser) {
    move(parser);
    while (token(parser)->kind != END) {
        list_add(parser->root->stmts, parse_stmt(parser));
        move(parser);
    }
    return parser->root;
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
        case OP_BRA:
        case CL_BRA:
            // TODO 后期写
            return new_empty(token(parser));
        default:
            log_error("Illegal expression: %s",get_kind_meta(tok->kind).name);
    }
}


void *parse_modifier(Parser *parser) {
    Token *tok = token(parser);
    List *modifiers = new_list();
    while (is_modifier(tok)) {
        list_add(modifiers, tok);
        move(parser);
        tok = token(parser);
    }
    return parse_id(parser, new_modifier(modifiers));
}

void *parse_id(Parser *parser, Modifier *modifier) {
    Token *tok = token(parser);
    switch (kind(tok)) {
        case CLASS:
            move(parser);
            return parse_class(parser, modifier);
        case FUN:
            move(parser);
            return parse_fun(parser, modifier);
        case ID: {
            if (peek(parser)->kind == OP_BRA) {
                free(modifier->modifiers);
                free(modifier);
                return parse_call(parser);
            }
            return parse_variable(parser, modifier);
        }
        default:
            parse_error(parser, "Unprocessable statement: %s", get_kind_meta(kind(tok)).name);
    }
}


void *parse_class(Parser *parser, Modifier *modifier) {
    Token *name = token(parser);
    expect(parser, ID);
    List *extends = new_list();
    if (token(parser)->kind == COLON) {
        // 解析继承关系
        move(parser);
        push(parser, token(parser));
        expect(parser, ID);
        Token *super;
        Token *next;
        while ((super = token(parser))->kind != OP_FL_BRA) {
            next = peek(parser);
            if (super->kind == ID) {
                list_add(extends, super);
            } else if (super->kind != COMM && super->kind != NEWLINE || super->kind == COMM && next->kind != ID) {
                parse_error(parser, "Unacceptable statement! expect %s but appeared %s",
                          get_kind_meta(ID).name,
                          get_kind_meta(super->kind).name);
            }
            move(parser);
        }
    }
    BlockStmt *block = parse_class_block(parser);
    return new_class_stmt(name, extends, block, modifier);
}

void *parse_class_block(Parser *parser) {
    expect(parser, OP_FL_BRA);
    List *stmts = new_list();
    while (token(parser)->kind != CL_FL_BRA && token(parser)->kind != END) {
        list_add(stmts, parse_stmt(parser));
        move(parser);
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

void *parse_variable(Parser *parser, Modifier *modifier) {
    Token *name = token(parser);
    expect(parser, ID);
    if (token(parser)->kind == COLON) {
        move(parser);
        Token *type = token(parser);
        if (!is_basic_type(token(parser))) {
            expect(parser, ID);
        } else {
            move(parser);
        }
        if (token(parser)->kind == COMM) {
            List *variables = new_list();
            do {
                move(parser);
                list_add(variables, new_var_term(name, NULL, new_type(type), modifier));
                name = token(parser);
                expect(parser, ID);
                if (token(parser)->kind == EQ || token(parser)->kind == DOT || is_operator(token(parser))) {
                    move(parser);
                    list_add(variables, new_var_term(name, parse_expr(parser), new_type(NULL), modifier));
                } else if (token(parser)->kind == COLON) {
                    move(parser);
                    type = token(parser);
                    if (!is_basic_type(token(parser))) {
                        expect(parser, ID);
                    }
                    move(parser);
                } else {
                    parse_error(parser, "Variable type is ambiguous: %s", get_kind_meta(name->kind).name);
                }
                if (token(parser)->kind == EQ) {
                    move(parser);
                    list_add(variables, new_var_term(name, parse_expr(parser), new_type(NULL), modifier));
                }
//                else if (token(parser)->kind != COMM
//                        && token(parser)->kind != NEWLINE
//                        && token(parser)->kind != END){
//                    out_token(token(parser));
//                    fprintf(stderr,"%s: Variable type is ambiguous: %s",
//                            get_token_pos(name),
//                            get_kind_meta(name->kind).name);
//                    exit(1);
//                }
            } while (token(parser)->kind == COMM || token(parser)->kind == ID);
            return new_stmt(variables);
        } else if (token(parser)->kind == EQ) {
            move(parser);
            return new_var_term(name, parse_expr(parser), new_type(NULL), modifier);
        }
    } else if (token(parser)->kind == EQ || token(parser)->kind == DOT || is_operator(token(parser))) {
        move(parser);
        return new_var_term(name, parse_expr(parser), new_type(NULL), modifier);
    } else {
        // 变量类型不明确
        parse_error(parser, "Variable type is ambiguous: %s",get_kind_meta(name->kind).name);
    }
    return NULL;
}

void *parse_block(Parser *parser) {
    expect(parser, OP_FL_BRA);
    List *stmts = new_list();
    while (token(parser)->kind != CL_FL_BRA) {
        list_add(stmts, parse_stmt(parser));
        move(parser);
    }
    expect(parser, CL_FL_BRA);
    return new_block_stmt(stmts);
}

void *parse_call(Parser *parser) {
    return NULL;
}

void *parse_if(Parser *parser) {
    expect(parser, IF);
    expect(parser, OP_BRA);
    void *expr = parse_expr(parser);
    expect(parser, CL_BRA);
    List *elseif = new_list();
    void *elsexpr = NULL;
    void *block = parse_block(parser);
    while (token(parser)->kind == ELSE) {
        if (elsexpr != NULL) {
            parse_error(parser, "%s: Invalid statement: %s",
                      get_token_pos(token(parser)),
                      get_kind_meta(token(parser)->kind).name);
        }
        move(parser);
        if (token(parser)->kind == IF) {
            move(parser);
            expect(parser, OP_BRA);
            void *exr = parse_expr(parser);
            expect(parser, CL_BRA);
            list_add(elseif, new_if_stmt(exr, parse_block(parser), NULL, NULL));
        } else {
            push(parser, token(parser));
            expect(parser, OP_FL_BRA);
            elsexpr = parse_block(parser);
        }
    }
    return new_if_stmt(expr, block, elseif, elsexpr);
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
            parse_error(parser, "Invalid statement: %s",get_kind_meta(token(parser)->kind).name);
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
                while (t_true) {
                    if (token(parser)->kind == CASE ||
                        token(parser)->kind == DEFAULT ||
                        token(parser)->kind == CL_FL_BRA)
                        break;
//                    out_token(token(parser));
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
    while (kind(tok) == LE2 || kind(tok) == BIG2) {
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
    while (kind(tok) == ADD || kind(tok) == SUB) {
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
    while (kind(tok) == MUL || kind(tok) == DIV) {
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
    while (kind(tok) == AND2 || kind(tok) == SUB2) {
        tok = token(parser);
        move(parser);
        if (left == NULL) {
            expr = new_start_term(tok, NULL);
            p = expr->expr;
        } else {
            expr = new_start_term(tok, expr);
        }
    }
    switch (kind(tok)) {
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
    switch (kind(tok)) {
        case AND2:
        case SUB2: {
            // ++, ----
            EndTerm *end = NULL;
            void **p;
            while (t_true) {
                switch (kind(tok)) {
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
                    parse_error(parser, "Illegal expression: %s",get_kind_meta(tok->kind).name);
                }
            }
            expect(parser, CL_BRA);
            return new_call_term(left, args);
        }
        case DO: {
            move(parser);
            if (peek(parser)->kind != ID) {
                parse_error(parser, "Illegal expression: %s",get_kind_meta(tok->kind).name);
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
    switch (kind(tok)) {
        case NUMBER:
        case FLOAT:
        case ID:
            move(parser);
            return new_constant_term(tok);
        default:
            parse_error(parser, "Illegal expression: %s", get_kind_meta(tok->kind).name);
    }
}
