//
// Created by zy on 8/13/20.
//
#include "include/stack.h"
#include "include/list.h"
#include <stdlib.h>

/**
 * 创建一个 stack
 * @return 返回指向该stack的指针
 */
Stack* new_stack(){
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->container = new_list();
    return stack;
}

/**
 * 从栈顶弹出一个元素
 * @param stack 指向该stack的指针
 * @return 如果有返回该元素,否则 0
 */
void* stack_pop(Stack* stack){
    void* value = list_remove(stack->container, stack->size - 1);
    stack->size--;
    return value;
}

/**
 * 压入栈
 * @param stack 指向该stack的指针
 * @param el 该栈的元素
 */
void stack_push(Stack* stack, void* el){
    list_insert(stack->container, stack->size, el);
    stack->size++;
}

/**
 * 查看栈顶元素
 * @param stack 指向该stack的指针
 * @return 如果有返回该元素,否则 0
 */
void* stack_peek(Stack* stack){
    return list_get(stack->container, stack->size - 1);
}