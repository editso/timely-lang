//
// Created by zy on 8/9/20.
//

#ifndef TIMELY_LANG_EVAL_H
#define TIMELY_LANG_EVAL_H
#include "tree.h"

void* binary_eval(Environment* env, BinaryExpr* expr);
void* while_eval(Environment* env, WhileStmt* stmt);
void* var_eval(Environment* env, VarTerm* term);
void* constraint_eval(Environment* env, ConstraintTerm* term);
void* block_eval(Environment* env, BlockStmt* stmt);
Eval* new_eval(void* (*eval_call)(Environment* env, void* node));


#endif //TIMELY_LANG_EVAL_H
