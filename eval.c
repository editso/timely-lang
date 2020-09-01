//
// Created by zy on 2020/8/23.
//
#include "include/basic.h"
#include "include/eval.h"
#include "include/tio.h"



void *binary_eval(Env *env, BinaryExpr *expr) {
    log_debug(__FUNCTION__ );

    return NULL;
}


void *while_eval(Env *env, WhileStmt *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *var_eval(Env *env, VarTerm *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *constant_eval(Env *env, ConstantTerm *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *block_eval(Env *env, BlockStmt *stmt) {
    void* elem;
    List* list = stmt->stmts;
    for (int i = 0; i < list->size; ++i) {
        elem = list_get(list, i);
        if (elem == NULL)continue;
        tree_node(elem)->eval(env, elem);
    }
    return NULL;
}


void *start_eval(Env *env, StartTerm *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *end_eval(Env *env, EndTerm *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}


void *call_eval(Env *env, CallTerm *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *fun_eval(Env *env, FunStmt *fun) {
    log_debug(__FUNCTION__ );
    block_eval(env, fun->block);
    return NULL;
}

void *tree_eval(Env *env, Tree *eval) {
    log_debug(__FUNCTION__ );
    List *stmts = eval->stmts;
    void *node;
    for (int i = 0; i < stmts->size; ++i) {
        node = list_get(stmts, i);
        tree_node(node)->eval(env, node);
    }
    return NULL;
}



void *try_eval(Env *env, TryStmt *stmt) {

    return NULL;
}

void *catch_eval(Env *env, CatchStmt *stmt) {
    log_debug(__FUNCTION__ );
    return NULL;
}

void *empty_eval(Env *env, EmptyStmt *term) {
    log_debug(__FUNCTION__ );
    return NULL;
}


void *class_eval(Env *env, ClassStmt *stmt) {
    log_debug(__FUNCTION__ );
    block_eval(env, stmt->block);
//    tree_node(stmt->block)->eval(env, stmt->block);
    return NULL;
}


void* modifier_eval(Env* env, Modifier * stmt){
    log_debug(__FUNCTION__ );
}

void* type_eval(Env* env, Type * stmt){
    log_debug(__FUNCTION__ );
}
void* subscript_eval(Env* env, ArraySubscript* subscript){
    log_debug(__FUNCTION__ );
}


void* if_eval(Env* env, IFStmt * ifStmt){
    log_debug(__FUNCTION__ );
    if (ifStmt->els != NULL){
        else_eval(env, ifStmt->els);
    }
}

void* else_eval(Env* env, ElseStmt * elseStmt){
    log_debug(__FUNCTION__ );
    block_eval(env,elseStmt->block);
}

void* switch_eval(Env* env, SwitchStmt* switchStmt){
    log_debug(__FUNCTION__ );
}

void* case_eval(Env* env, CaseStmt * caseStmt){
    log_debug(__FUNCTION__ );
}

void *stmt_eval(Env* env, Stmt* stmt){
    void* elem;
    List* stmts = stmt->stmt;
    for (int i = 0; i < stmts->size; ++i) {
        elem = list_get(stmts, i);
        tree_node(elem)->eval(env, elem);
    }
}