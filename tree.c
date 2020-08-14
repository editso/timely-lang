//
// Created by zy on 8/9/20.
//
#include "include/eval.h"
#include "include/basic.h"
#include "string.h"
#include "stdlib.h"

void *binary_eval(Environment *env, BinaryExpr *expr) {
    print("二元运算: %s", __FUNCTION__);
    GET_EVAL(expr->left)->eval(env, expr->left);
    GET_EVAL(expr->right)->eval(env, expr->right);

    return NULL;
}

void *while_eval(Environment *env, WhileStmt *stmt) {
    print("while循环: %s", __FUNCTION__);
//    while (GET_EVAL(stmt->expr)->eval(env, stmt->expr)){
//        GET_EVAL(stmt->block)->eval(env, stmt->block);
//    }
    return NULL;
}

void *var_eval(Environment *env, VarTerm *term) {
    print("变量声明: %s", __FUNCTION__);
//    void* value = GET_EVAL(term->value)->eval(env,term);
//    map_put(&env->map, term->name->text, value);
    return NULL;
}

void *constant_eval(Environment *env, ConstantTerm *term) {
    print("常量: %s", __FUNCTION__);
    switch (term->name->kind) {
        case NUMBER:
            return "number";
        case CONST_STRING:
            return "hello world";
        case ID:
            return term->name->text;
        default:
            error("失败");
    }
    return NULL;
}

void *block_eval(Environment *env, BlockStmt *stmt) {
    print("代码块: %s", __FUNCTION__);
    List *comm = stmt->stmts;
    void *node;
    for (int i = 0; i < comm->size; ++i) {
        node = list_get(stmt->stmts, i);
        if (node == NULL)continue;
        GET_EVAL(node)->eval(env, node);
    }
    return NULL;
}

void *start_eval(Environment *env, StartTerm *stmt) {
    print("前缀表达式: %s", __FUNCTION__);
    return NULL;
}

void *end_eval(Environment *env, EndTerm *stmt) {
    print("后缀表达式: %s", __FUNCTION__);
    return NULL;
}


void *call_eval(Environment *env, CallTerm *term) {
    print("函数调用: %s", __FUNCTION__);
    ConstantTerm *constant = term->expr;
    List *args = term->args;
    char buff[1024];
    return NULL;
}

void *fun_eval(Environment *env, FunStmt *fun) {
    print("方法声明: %s", __FUNCTION__);
    return NULL;
}

void *tree_eval(Environment *env, Tree *eval) {
//    print("call: %s", __FUNCTION__ );
    List *stmts = eval->stmts;
    void *node;
    for (int i = 0; i < stmts->size; ++i) {
        node = list_get(stmts, i);
        GET_EVAL(node)->eval(env, node);
    }
    return NULL;
}

void *try_eval(Environment *env, TryStmt *stmt) {
    print("异常捕获: %s", __FUNCTION__);
    return NULL;
}

void *catch_eval(Environment *env, CatchStmt *stmt) {
    print("call: %s", __FUNCTION__);
    return NULL;
}

void *empty_eval(Environment *env, EmptyStmt *term) {
    return NULL;
}

Eval *new_eval(void *(*eval_call)(Environment *env, void *node)) {
    Eval *eval = malloc(sizeof(Eval));
    eval->eval = eval_call;
    return eval;
}

void *class_eval(Environment *env, ClassStmt *stmt) {
    print("类定义: %s", __FUNCTION__);
    return NULL;
}

Tree *new_tree(List *list) {
    Tree *tree = malloc(sizeof(Tree));
    tree->stmts = list;
    tree->eval = *new_eval(GET_FUN(tree_eval));
    return tree;
}

VarTerm *new_var_term(Token *name, void *expr) {
    VarTerm *var = malloc(sizeof(VarTerm));
    var->eval = *new_eval(GET_FUN(var_eval));
    var->name = name;
    var->value = expr;
    return var;
}

ConstantTerm *new_constant_term(Token *name) {
    ConstantTerm *constraint = malloc(sizeof(ConstantTerm));
    constraint->name = name;
    constraint->eval = *new_eval(GET_FUN(constant_eval));
    return constraint;
}

BinaryExpr *new_binary_expr(void *left, Token *op, void *right) {
    BinaryExpr *binary = malloc(sizeof(BinaryExpr));
    binary->left = left;
    binary->op = op;
    binary->right = right;
    binary->eval = *new_eval(GET_FUN(binary_eval));
    return binary;
}

BlockStmt *new_block_stmt(List *stmts) {
    BlockStmt *block = malloc(sizeof(BlockStmt));
    block->stmts = stmts;
    block->eval = *new_eval(GET_FUN(block_eval));
    return block;
}

WhileStmt *new_while_stmt(Token *name, void *expr, void *block) {
    WhileStmt *t_while = malloc(sizeof(WhileStmt));
    t_while->name = name;
    t_while->expr = expr;
    t_while->block = block;
    t_while->eval = *new_eval(GET_FUN(while_eval));
    return t_while;
}

StartTerm *new_start_term(Token *op, void *expr) {
    StartTerm *term = malloc(sizeof(StartTerm));
    term->eval = *new_eval(GET_FUN(start_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

EndTerm *new_end_term(Token *op, void *expr) {
    EndTerm *term = malloc(sizeof(EndTerm));
    term->eval = *new_eval(GET_FUN(end_eval));
    term->op = op;
    term->expr = expr;
    return term;
}

CallTerm *new_call_term(void *expr, List *args) {
    CallTerm *term = malloc(sizeof(CallTerm));
    term->expr = expr;
    term->eval = *new_eval(GET_FUN(call_eval));
    term->args = args;
    return term;
}

EmptyStmt *new_empty(Token *op) {
    EmptyStmt *empty = malloc(sizeof(EmptyStmt));
    empty->token = op;
    empty->eval = *new_eval(GET_FUN(empty_eval));
    return empty;
}

FunStmt *new_fun_stmt(Token *name, List *args, void *block) {
    FunStmt *fun = malloc(sizeof(FunStmt));
    fun->eval = *new_eval(GET_FUN(fun_eval));
    fun->name = name;
    fun->args = args;
    fun->block = block;
    return fun;
}

TryStmt *new_try_stmt(void *block, List *stmts, void *finally) {
    TryStmt *stmt = malloc(sizeof(TryStmt));
    stmt->eval = *new_eval(GET_FUN(try_eval));
    stmt->block = block;
    stmt->stmts = stmts;
    stmt->stmt = finally;
    return stmt;
}

CatchStmt *new_catch_stmt(void *expr, void *block) {
    CatchStmt *stmt = malloc(sizeof(CatchStmt));
    stmt->eval = *new_eval(GET_FUN(catch_eval));
    stmt->expr = expr;
    stmt->block = block;
    return stmt;
}

ClassStmt *new_class_stmt(Token *name, List *parent, void *block) {
    ClassStmt *stmt = malloc(sizeof(ClassStmt *));
    stmt->eval = *new_eval(GET_FUN(class_eval));
    stmt->name = name;
    stmt->parent = parent;
    stmt->block = block;
    return stmt;
}
