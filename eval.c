//
// Created by zy on 2020/8/23.
//
#include "include/basic.h"
#include "include/eval.h"
#include "include/tio.h"

Eval *new_eval(void *(*eval_call)(Environment *env, void *node)) {
    Eval *eval = new(Eval);
    eval->eval = eval_call;
    return eval;
}

void *binary_eval(Environment *env, BinaryExpr *expr) {
    log_debug(__FUNCTION__ );
    to_eval(expr->left)->eval(env, expr->left);
    to_eval(expr->right)->eval(env, expr->right);
    return NULL;
}

void *while_eval(Environment *env, WhileStmt *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *var_eval(Environment *env, VarTerm *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *constant_eval(Environment *env, ConstantTerm *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *block_eval(Environment *env, BlockStmt *stmt) {
    log_debug(__FUNCTION__ );
    List *comm = stmt->stmts;
    void *node;
    for (int i = 0; i < comm->size; ++i) {
        node = list_get(stmt->stmts, i);
        if (node == NULL)continue;
        to_eval(node)->eval(env, node);
    }
    return NULL;
}

void *start_eval(Environment *env, StartTerm *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *end_eval(Environment *env, EndTerm *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}


void *call_eval(Environment *env, CallTerm *term) {
    log_debug(__FUNCTION__ );

    return NULL;
}

void *fun_eval(Environment *env, FunStmt *fun) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *tree_eval(Environment *env, Tree *eval) {
    log_debug(__FUNCTION__ );
    List *stmts = eval->stmts;
    void *node;
    for (int i = 0; i < stmts->size; ++i) {
        node = list_get(stmts, i);
        to_eval(node)->eval(env, node);
    }
    return NULL;
}

void *try_eval(Environment *env, TryStmt *stmt) {

    return NULL;
}

void *catch_eval(Environment *env, CatchStmt *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *empty_eval(Environment *env, EmptyStmt *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}


void *class_eval(Environment *env, ClassStmt *stmt) {
    log_debug(__FUNCTION__ );
    stmt->block->eval.eval(env, stmt->block);
    return NULL;
}


void* modifier_eval(Environment* env, Modifier * stmt){
    log_debug(__FUNCTION__ );
}

void* type_eval(Environment* env, Type * stmt){
    log_debug(__FUNCTION__ );
}
void* subscript_eval(Environment* env, ArraySubscript* subscript){
    log_debug(__FUNCTION__ );
}
void* if_eval(Environment* env, IFStmt * ifStmt){
    log_debug(__FUNCTION__ );

}

void* else_eval(Environment* env, ElseStmt * elseStmt){
    log_debug(__FUNCTION__ );
}

void* switch_eval(Environment* env, SwitchStmt* switchStmt){
    log_debug(__FUNCTION__ );
}

void* case_eval(Environment* env, CaseStmt * caseStmt){
    log_debug(__FUNCTION__ );
}
