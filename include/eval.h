//
// Created by zy on 8/9/20.
//

#ifndef TIMELY_LANG_EVAL_H
#define TIMELY_LANG_EVAL_H
#include "tree.h"

Eval* new_eval(void* (*eval_call)(Environment* env, void* node));

void* binary_eval(Environment* env, BinaryExpr* expr);

void* while_eval(Environment* env, WhileStmt* stmt);

void* var_eval(Environment* env, VarTerm* term);

void* constant_eval(Environment* env, ConstantTerm* term);

void* block_eval(Environment* env, BlockStmt* stmt);

void* start_eval(Environment* env, StartTerm * stmt);

void* end_eval(Environment* env, EndTerm * stmt);

void* call_eval(Environment* env, CallTerm* term);

void* empty_eval(Environment* env, EmptyStmt* term);

void* fun_eval(Environment* env, FunStmt* fun);

void* tree_eval(Environment* env, Tree* eval);

void* try_eval(Environment* env, TryStmt* stmt);

void* catch_eval(Environment* env, CatchStmt* stmt);

void* class_eval(Environment* env, ClassStmt* stmt);
#endif //TIMELY_LANG_EVAL_H
