//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TREE_H
#define TIMELY_LANG_TREE_H
#include "../token.h"
#include "../list.h"


typedef struct{

}Environment;

typedef struct{
    void* (*eval)(Environment* env, void* node);
}Eval;

#define GET_EVAL(eval) ((Eval*)eval)



#define GET_FUN(fun) ((void *(*)(Environment *, void *))fun)


typedef struct{
    Eval *eval;
    struct list* stmts;
}Tree;

typedef struct {
    Eval *eval;
    void* left;
    Token *op;
    void* right;
}BinaryExpr;


typedef struct {
    Eval *eval;
    Token *op;
    void* expr;
}StartTerm;

typedef struct {
    Eval *eval;
    Token *op;
    void* expr;
}EndTerm;

typedef struct{
    Eval *eval;
    Token *name;
    void* value;
}VarTerm;

typedef struct{
    Eval *eval;
    Token *name;
}ConstantTerm;

/**
 * 函数调用
 */
typedef struct{
    Eval *eval;
    void *expr;
    struct list* args;
}CallTerm;


typedef struct{
    Eval *eval;
    struct list* stmts;
}BlockStmt;

typedef struct {

}EmptyStmt;

typedef struct{
    Eval *eval;
    Token *name;
    void* expr;
    BlockStmt* block;
}WhileStmt;

Tree* new_tree(struct list* list);

VarTerm* new_var_term(Token* name, void* expr);

ConstantTerm* new_constant_term(Token* name);

BinaryExpr* new_binary_expr(void* left,Token* op, void* right);

BlockStmt* new_block_stmt(struct list* stmts);

WhileStmt* new_while_stmt(Token* name, void* expr, BlockStmt* block);

StartTerm* new_start_term(Token* op, void* expr);

EndTerm* new_end_term(Token* op, void* expr);

CallTerm* new_call_term(void* expr, struct list* args);
#endif //TIMELY_LANG_TREE_H
