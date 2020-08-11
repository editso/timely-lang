//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TREE_H
#define TIMELY_LANG_TREE_H
#include "token.h"
#include "list.h"
#include "envir.h"


typedef struct{
    void* (*eval)(Environment* env, void* node);
}Eval;

#define GET_EVAL(eval) ((Eval*)eval)

#define GET_FUN(fun) ((void *(*)(Environment *, void *))fun)


typedef struct{
    Eval eval;
    struct list* stmts;
}Tree;

typedef struct {
    Eval eval;
    void* left;
    Token *op;
    void* right;
}BinaryExpr;


typedef struct {
    Eval eval;
    Token *op;
    void* expr;
}StartTerm;

typedef struct {
    Eval eval;
    Token *op;
    void* expr;
}EndTerm;

typedef struct{
    Eval eval;
    Token *name;
    void* value;
}VarTerm;


typedef struct{
    Eval eval;
    Token *name;
}ConstantTerm;

/**
 * 函数调用
 */
typedef struct{
    Eval eval;
    void *expr;
    struct list* args;
}CallTerm;


typedef struct{
    Eval eval;
    struct list* stmts;
}BlockStmt;

typedef struct {
    Eval eval;
    Token* token;
}EmptyStmt;

typedef struct{
    Eval eval;
    Token *name;
    void* expr;
    void* block;
}WhileStmt;

typedef struct {
    Eval eval;
    Token* name;
    struct list* args;
    void* block;
}FunStmt;

typedef struct{
    Eval eval;
    void* expr;
    void* block;
}CatchStmt;


typedef struct {
    Eval eval;

    /**
     * try{
     *
     * }
     */
    void* block;
    /**
     * try{
     *
     * }catch(){
     *
     * }catch(){
     *
     * }
     */
    struct list* stmts;
    /**
     * try{
     *
     * }catch{
     *
     * }finally{
     *
     * }
     */
    void* stmt;
}TryStmt;


Tree* new_tree(struct list* list);

VarTerm* new_var_term(Token* name, void* expr);

ConstantTerm* new_constant_term(Token* name);

BinaryExpr* new_binary_expr(void* left,Token* op, void* right);

BlockStmt* new_block_stmt(struct list* stmts);

WhileStmt* new_while_stmt(Token* name, void* expr, void* block);

StartTerm* new_start_term(Token* op, void* expr);

EndTerm* new_end_term(Token* op, void* expr);

EmptyStmt* new_empty(Token *op);

FunStmt* new_fun_stmt(Token* name, struct list* args, void* block);

CallTerm* new_call_term(void* expr, struct list* args);

TryStmt* new_try_stmt(void* block, struct list *stmts, void* finally);

CatchStmt* new_catch_stmt(void* expr, void* block);
#endif //TIMELY_LANG_TREE_H
