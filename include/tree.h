//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TREE_H
#define TIMELY_LANG_TREE_H

#include "token.h"
#include "list.h"
#include "envir.h"

#define to_eval(any) ((Eval*)any)

#define eval_callback(fun) ((void *(*)(Environment *, void *))fun)

#define tree_node typedef struct

tree_node {
    void *(*eval)(Environment *env, void *node);
} Eval;

tree_node {
    Eval eval;
    List *stmts;
} Tree;

tree_node modifier_{
    Eval eval;
    List* modifiers;
}Modifier;

tree_node stmt_{
    Eval eval;
    List* stmt;
}Stmt;

tree_node {
    Eval eval;
    void *left;
    Token *op;
    void *right;
} BinaryExpr;

tree_node{
    Eval eval;
    Token *op;
    void *expr;
} StartTerm;

tree_node {
    Eval eval;
    Token *op;
    void *expr;
} EndTerm;

tree_node type_{
    Eval eval;
    Token* name;
}Type;

tree_node {
    Eval eval;
    Token *name;
    void *value;
    Type* type;
    Modifier* modifier;
} VarTerm;

tree_node {
    Eval eval;
    Token *name;
} ConstantTerm;


/**
 * 函数调用
 */
tree_node {
    Eval eval;
    void *expr;
    List *args;
} CallTerm;


tree_node {
    Eval eval;
    List *stmts;
} BlockStmt;

tree_node {
    Eval eval;
    Token *token;
} EmptyStmt;

tree_node {
    Eval eval;
    void *expr;
    void *block;
} WhileStmt;

tree_node if_{
    Eval eval;
    void* expr;
    void* block;
    void* elsexpr;
}IFStmt;

tree_node else_{
    Eval eval;
    void* block;
}ElseStmt;

tree_node {
    Eval eval;
    Token *name;
    List *args;
    void *block;
    Modifier* modifier;
} FunStmt;

tree_node {
    Eval eval;
    void *expr;
    void *block;
} CatchStmt;

tree_node{
    Eval eval;

    /**
     * try{
     *
     * }
     */
    void *block;
    /**
     * try{
     *
     * }catch e{
     *
     * }catch e{
     *
     * }
     */
    List *stmts;
    /**
     * try{
     *
     * }catch e{
     *
     * }finally{
     *
     * }
     */
    void *stmt;
} TryStmt;

tree_node {
    Eval eval;
    Token *name;
    List *extends;
    BlockStmt *block;
    Modifier* modifier;
} ClassStmt;

tree_node{
    Eval eval;
    void* name;
    void* expr;
}ArraySubscript;

tree_node{
    Eval eval;
    void* object;
    void* expr;
}SelectMember;

tree_node expr_{
    Eval eval;
    void* expr;
}Expr;

tree_node switch_{
    Eval eval;
    void* expr;
    List* cases;
    void* defexpr;
}SwitchStmt;

tree_node case_{
    Expr eval;
    void* expr;
    void* block;
}CaseStmt;

Tree *new_tree(List *list);

VarTerm *new_var_term(Token *name, void *expr, Type* type, Modifier* modifier);

ConstantTerm *new_constant_term(Token *name);

BinaryExpr *new_binary_expr(void *left, Token *op, void *right);

BlockStmt *new_block_stmt(List *stmts);

WhileStmt *new_while_stmt(void *expr, void *block);

StartTerm *new_start_term(Token *op, void *expr);

EndTerm *new_end_term(Token *op, void *expr);

EmptyStmt *new_empty(Token *op);

FunStmt *new_fun_stmt(Token *name, List *args, void *block, Modifier* modifier);

CallTerm *new_call_term(void *expr, List *args);

TryStmt *new_try_stmt(void *block, List *stmts, void *finally);

CatchStmt *new_catch_stmt(void *expr, void *block);

ClassStmt *new_class_stmt(Token *name, List *parent, BlockStmt *block, Modifier* modifier);

Modifier* new_modifier(List* modifiers);
Type* new_type(Token* name);

Stmt* new_stmt(List* stmt);

ArraySubscript*  new_array_subscript(void* name, void* expr);

SelectMember* new_select_member( void* object, void* expr);

Expr* new_expr(void* expr);

IFStmt* new_if_stmt(void* expr, void* block, void*  elsexpr);
ElseStmt* new_else_stmt(void *block);

SwitchStmt* new_switch_stmt(void* expr, List* cases, void* defexpr);

CaseStmt* new_case_stmt(void* expr, void* block);
#endif //TIMELY_LANG_TREE_H
