//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_TREE_H
#define TIMELY_LANG_TREE_H

#include "token.h"
#include "list.h"

typedef struct env_{
    void *tree;
    struct env_ *next;
}Env;

#define tree_node(tree) ((struct tree_node*)tree)

#define eval_handler(handler) (eval_handler_)handler

#define tree_ typedef struct

typedef void *(*eval_handler_) (Env *env, void* node);


tree_ tree_node{
    eval_handler_ eval;
    Token *token;
}TreeNode;

tree_ {
    TreeNode node;
    List *stmts;
} Tree;

tree_ modifier_ {
    TreeNode node;
    List *modifiers;
} Modifier;

tree_ stmt_ {
    TreeNode node;
    List *stmt;
} Stmt;

tree_ {
    TreeNode node;
    void *left;
    void *right;
} BinaryExpr;

tree_ {
    TreeNode node;
    void *expr;
} StartTerm;

tree_ {
    TreeNode node;
    void *expr;
} EndTerm;

tree_ type_ {
    TreeNode node;
} Type;

tree_ {
    TreeNode node;
    void *value;
    Type *type;
    Modifier *modifier;
} VarTerm;

tree_ {
    TreeNode node;
} ConstantTerm;


/**
 * 函数调用
 */
tree_ {
    TreeNode node;
    void *expr;
    List *args;
} CallTerm;


tree_ {
    TreeNode node;
    List *stmts;
} BlockStmt;

tree_ {
    TreeNode node;
} EmptyStmt;

tree_ {
    TreeNode node;
    void *expr;
    void *block;
} WhileStmt;

tree_ if_ {
    TreeNode node;
    // if(expr)
    void *expr;
    void *block;
    void *els;
} IFStmt;

tree_ else_ {
    TreeNode node;
    void *block;
} ElseStmt;

tree_ {
    TreeNode node;
    List *args;
    void *block;
    Modifier *modifier;
} FunStmt;

tree_ {
    TreeNode node;
    void *expr;
    void *block;
} CatchStmt;

tree_ {
    TreeNode node;
    void *block;
    List *stmts;
    void *stmt;
} TryStmt;

tree_ {
    TreeNode node;
    List *extends;
    BlockStmt *block;
    Modifier *modifier;
} ClassStmt;

tree_ {
    TreeNode node;
    void *name;
    void *expr;
} ArraySubscript;

tree_ {
    TreeNode node;
    void *object;
    void *expr;
} SelectMember;

tree_ expr_ {
    TreeNode node;
    void *expr;
} Expr;

tree_ switch_ {
    TreeNode node;
    void *expr;
    List *cases;
    void *t_default;
} SwitchStmt;

tree_ case_ {
    TreeNode node;
    void *expr;
    void *block;
} CaseStmt;


TreeNode * new_tree_node(Token *tok, eval_handler_ eval);

Tree *new_tree(List *list);

VarTerm *new_var_term(Token *name, void *expr, Type *type, Modifier *modifier);

ConstantTerm *new_constant_term(Token *name);

BinaryExpr *new_binary_expr(void *left, Token *op, void *right);

BlockStmt *new_block_stmt(List *stmts);

WhileStmt *new_while_stmt(void *expr, void *block);

StartTerm *new_start_term(Token *op, void *expr);

EndTerm *new_end_term(Token *op, void *expr);

EmptyStmt *new_empty(Token *op);

FunStmt *new_fun_stmt(Token *name, List *args, void *block, Modifier *modifier);

CallTerm *new_call_term(void *expr, List *args);

TryStmt *new_try_stmt(void *block, List *stmts, void *finally);

CatchStmt *new_catch_stmt(void *expr, void *block);

ClassStmt *new_class_stmt(Token *name, List *parent, BlockStmt *block, Modifier *modifier);

Modifier *new_modifier(List *modifiers);

Type *new_type(Token *name);

Stmt *new_stmt(List *stmt);

ArraySubscript *new_array_subscript(void *name, void *expr);

SelectMember *new_select_member(void *object, void *expr);

Expr *new_expr(void *expr);

IFStmt *new_if_stmt(void *expr, void *block, void *elsexpr);

ElseStmt *new_else_stmt(void *block);

SwitchStmt *new_switch_stmt(void *expr, List *cases, void *defexpr);

CaseStmt *new_case_stmt(void *expr, void *block);

#endif //TIMELY_LANG_TREE_H
