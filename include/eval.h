//
// Created by zy on 8/9/20.
//

#ifndef TIMELY_LANG_EVAL_H
#define TIMELY_LANG_EVAL_H

#include "tree.h"

void *binary_eval(Env *env, BinaryExpr *expr);

void *while_eval(Env *env, WhileStmt *stmt);

void *var_eval(Env *env, VarTerm *term);

void *constant_eval(Env *env, ConstantTerm *term);

void *block_eval(Env *env, BlockStmt *stmt);

void *start_eval(Env *env, StartTerm *stmt);

void *end_eval(Env *env, EndTerm *stmt);

void *call_eval(Env *env, CallTerm *term);

void *empty_eval(Env *env, EmptyStmt *term);

void *fun_eval(Env *env, FunStmt *fun);

void *tree_eval(Env *env, Tree *eval);

void *try_eval(Env *env, TryStmt *stmt);

void *catch_eval(Env *env, CatchStmt *stmt);

void *class_eval(Env *env, ClassStmt *stmt);

void *modifier_eval(Env *env, Modifier *stmt);

void *type_eval(Env *env, Type *stmt);

void *subscript_eval(Env *env, ArraySubscript *subscript);

void *if_eval(Env *env, IFStmt *ifStmt);

void *else_eval(Env *env, ElseStmt *elseStmt);

void *switch_eval(Env *env, SwitchStmt *switchStmt);

void *case_eval(Env *env, CaseStmt *caseStmt);

void *stmt_eval(Env* env, Stmt* stmt);
#endif //TIMELY_LANG_EVAL_H
