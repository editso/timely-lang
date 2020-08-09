//
// Created by zy on 8/7/20.
//
#include "parser.h"

void move(Parser *parser){
    parser->token =  lexer_read(parser->lexer);
}


void* match(Parser* parser, t_kind kind){
    if (kind != GET_TOKEN(parser)->kind){

    }
}

struct parser* new_parser(Lexer* lexer){
    struct parser* parser = malloc(sizeof(struct parser));
    parser->lexer = lexer;
    parser->root = malloc(sizeof(Tree));
    return parser;
}

void* parseExpr(Parser* parser){

}



void* parse_stmt(Parser* parser){
    switch (GET_TOKEN(parser)->kind) {
        case ID:{
            Token* token = GET_TOKEN(parser);
            move(parser);
            if (token->kind == EQ){
                move(parser);
                return new_var_term(token, parseExpr(parser));
            }
        }
        case IF:{

        }
        case WHILE:{

        }
        default:
            return NULL;
    }
}


int parse(Parser* parser){
    move(parser);
    while (GET_TOKEN(parser)->kind != END){
//        list_add(parser->root->stmts, parse_stmt(parser));
        out_token(parser->token);
        move(parser);
    }
    return -1;
}

