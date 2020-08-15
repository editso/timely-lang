//
// Created by zy on 8/13/20.
//

#ifndef TIMELY_LANG_STACK_H
#define TIMELY_LANG_STACK_H
#define stack_size(stack) stack->size

typedef struct stack_{
    /**
     * 栈大小
     */
    int size;
    /**
     *  存放 stack的容器指针
     */
    void* container;
}Stack;
/**
 * 创建一个 stack
 * @return 返回指向该stack的指针
 */
Stack* new_stack();

/**
 * 从栈顶弹出一个元素
 * @param stack 指向该stack的指针
 * @return 如果有返回该元素,否则 0
 */
void* stack_pop(Stack* stack);

/**
 * 压入栈
 * @param stack 指向该stack的指针
 * @param el 该栈的元素
 */
void stack_push(Stack* stack, void* el);

/**
 * 查看栈顶元素
 * @param stack 指向该stack的指针
 * @return 如果有返回该元素,否则 0
 */
void* stack_peek(Stack* stack);
#endif //TIMELY_LANG_STACK_H
