//
// Created by zy on 8/9/20.
//
#include "include/eval.h"
#include "include/basic.h"
#define tree_node_(tok, eval) *new_tree_node(tok, eval_handler(eval))

TreeNode* new_tree_node(Token *tok, eval_handler_ eval){
    TreeNode* treeNode = new(TreeNode);
    treeNode->token = tok;
    treeNode->eval = eval;
    return treeNode;
}

Tree *new_tree(List *list) {
    Tree *tree = new(Tree);
    tree->node = tree_node_(NULL,eval_handler(tree_eval));
    tree->stmts = list;
    return tree;
}

VarTerm *new_var_term(Token *name, void *expr, Type* type, Modifier* modifier) {
    VarTerm *term = new(VarTerm);
    term->node = tree_node_(name, eval_handler(var_eval));
    term->value = expr;
    term->modifier = modifier;
    term->type = type;
    return term;
}

ConstantTerm *new_constant_term(Token *name) {
    ConstantTerm *term = new(ConstantTerm);
    term->node = tree_node_(name, eval_handler(constant_eval));
    return term;
}

BinaryExpr *new_binary_expr(void *left, Token *op, void *right) {
    BinaryExpr *expr = new(BinaryExpr);
    expr->node = tree_node_(op, eval_handler(binary_eval));
    expr->left = left;
    expr->right = right;
    return expr;
}

BlockStmt *new_block_stmt(List *stmts) {
    BlockStmt *stmt = new(BlockStmt);
    stmt->node = tree_node_(NULL, eval_handler(block_eval));
    stmt->stmts = stmts;
    return stmt;
}

WhileStmt *new_while_stmt(void *expr, void *block) {
    WhileStmt *stmt = new(WhileStmt);
    stmt->node = tree_node_(NULL, eval_handler(while_eval));
    stmt->expr = expr;
    stmt->block = block;
    return stmt;
}

StartTerm *new_start_term(Token *op, void *expr) {
    StartTerm *term = new(StartTerm);
    term->node = tree_node_(NULL, eval_handler(start_eval));
    term->expr = expr;
    return term;
}

EndTerm *new_end_term(Token *op, void *expr) {
    EndTerm *term = new(EndTerm);
    term->node = tree_node_(NULL, eval_handler(end_eval));
    term->expr = expr;
    return term;
}

CallTerm *new_call_term(void *expr, List *args) {
    CallTerm *term = new(CallTerm);
    term->node = tree_node_(NULL, eval_handler(call_eval));
    term->expr = expr;
    term->args = args;
    return term;
}

EmptyStmt *new_empty(Token *op) {
    EmptyStmt *empty = new(EmptyStmt);
    empty->node = tree_node_(op, eval_handler(empty_eval));
    return empty;
}

FunStmt *new_fun_stmt(Token *name, List *args, void *block, Modifier* modifier) {
    FunStmt *fun = new(FunStmt);
    fun->node = tree_node_(name, eval_handler(fun_eval));
    fun->args = args;
    fun->block = block;
    fun->modifier = modifier;
    return fun;
}

TryStmt *new_try_stmt(void *block, List *stmts, void *finally) {
    TryStmt *stmt = new(TryStmt);
    stmt->node = tree_node_(NULL, eval_handler(try_eval));
    stmt->block = block;
    stmt->stmts = stmts;
    stmt->stmt = finally;
    return stmt;
}

CatchStmt *new_catch_stmt(void *expr, void *block) {
    CatchStmt *stmt = new(CatchStmt);
    stmt->node = tree_node_(NULL, eval_handler(catch_eval));
    stmt->expr = expr;
    stmt->block = block;
    return stmt;
}

ClassStmt *new_class_stmt(Token *name, List *extends, BlockStmt *block, Modifier* modifier) {
    ClassStmt *stmt = new(ClassStmt);
    stmt->node = tree_node_(name, eval_handler(class_eval));
    stmt->extends = extends;
    stmt->block = block;
    stmt->modifier = modifier;
    return stmt;
}

Modifier* new_modifier(List* modifiers){
    Modifier* modifier = new(Modifier);
    modifier->node = tree_node_(NULL, eval_handler(modifier_eval));
    modifier->modifiers = modifiers;
    return modifier;
}

Stmt* new_stmt(List* stmt){
    Stmt* stmts = new(Stmt);
    stmts->node = tree_node_(NULL, eval_handler(stmt_eval));
    stmts->stmt = stmt;
    return stmts;
}

Type* new_type(Token* name){
    Type* type = new(Type);
    type->node = tree_node_(name, eval_handler(type_eval));
    return type;
}

ArraySubscript*  new_array_subscript(void* name, void* expr){
    ArraySubscript* term  = new(ArraySubscript);
    term->node = tree_node_(NULL, eval_handler(subscript_eval));
    term->name = name;
    term->expr = expr;
    return term;
}

Expr* new_expr(void* expr){
    Expr* expr_ = new(Expr);
    expr_->expr = expr;
    return expr_;
}


SelectMember* new_select_member( void* object, void* expr){
    SelectMember* member = new(SelectMember);
    member->expr = expr;
    member->object = object;
    return member;
}

IFStmt* new_if_stmt(void* expr, void* block, void* els){
    IFStmt* stmt = new(IFStmt);
    stmt->node = tree_node_(NULL, eval_handler(if_eval));
    stmt->expr = expr;
    stmt->block = block;
    stmt->els = els;
    return stmt;
}

ElseStmt* new_else_stmt(void *block){
    ElseStmt* stmt = new(ElseStmt);
    stmt->node = tree_node_(NULL, eval_handler(else_eval));
    stmt->block = block;
    return stmt;
}

SwitchStmt* new_switch_stmt(void* expr, List* cases, void* defexpr){
    SwitchStmt* stmt = new(SwitchStmt);
    stmt->node = tree_node_(NULL, eval_handler(switch_eval));
    stmt->expr = expr;
    stmt->cases = cases;
    stmt->t_default = defexpr;
    return stmt;
}

CaseStmt* new_case_stmt(void* expr, void* block){
    CaseStmt* stmt = new(CaseStmt);
    stmt->node = tree_node_(NULL, eval_handler(case_eval));
    stmt->block = block;
    stmt->expr = expr;
    return stmt;
}