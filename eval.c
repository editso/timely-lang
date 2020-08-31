//
// Created by zy on 2020/8/23.
//
#include "include/basic.h"
#include "include/eval.h"
#include "include/tio.h"


void *binary_eval(Environment *env, BinaryExpr *expr) {
    log_debug(__FUNCTION__ );

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
    void* elem;
    List* list = stmt->stmts;
    for (int i = 0; i < list->size; ++i) {
        elem = list_get(list, i);
        tree_node(elem)->eval(env, elem);
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
    block_eval(env, fun->block);
    return NULL;
}

void *tree_eval(Environment *env, Tree *eval) {
    log_debug(__FUNCTION__ );
    List *stmts = eval->stmts;
    void *node;
    for (int i = 0; i < stmts->size; ++i) {
        node = list_get(stmts, i);
        tree_node(node)->eval(env, node);
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
    block_eval(env, stmt->block);
//    tree_node(stmt->block)->eval(env, stmt->block);
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
    block_eval(env,elseStmt->block);
}

void* switch_eval(Environment* env, SwitchStmt* switchStmt){
    log_debug(__FUNCTION__ );
}

void* case_eval(Environment* env, CaseStmt * caseStmt){
    log_debug(__FUNCTION__ );
}
