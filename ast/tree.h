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


typedef struct{
    Eval *eval;
    Token *name;
    void* value;
}VarTerm;


typedef struct{
    Eval *eval;
    Token *name;
}ConstraintTerm;

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


VarTerm* new_var_term(Token* name, void* expr);

ConstraintTerm* new_constraintTerm(Token* name);

BinaryExpr* new_binary_expr(void* left,Token* op, void* right);

BlockStmt* new_block_stmt(struct list* stmts);

WhileStmt* new_while_stmt(Token* name, void* expr, BlockStmt* block);



#endif //TIMELY_LANG_TREE_H
