//
// Created by zy on 8/7/20.
//


#ifndef TIMELY_LANG_LIST_H
#define TIMELY_LANG_LIST_H

#include <stdlib.h>
#include "ttypes.h"


typedef struct list_node_ {
    void *data;
    struct list_node_ *prev;
    struct list_node_ *next;
} ListNode;

typedef struct list_ {
    ListNode *head;
    ListNode *tail;
    uint size;
} List;

/**
 * 创建一个新的list
 * @return 新的 list
 */
List *new_list();

/**
 * 向list指定位置插入一个元素
 * @param list 指向list的指针
 * @param 插入的位置
 * @param data数据 插入成功 1, 失败-1;
 */
int list_insert(List *list, uint index, void *elem);


/**
 * 向list添加一个元素
 * @param list 指向list的指针
 * @param data 数据
 */
void list_add(List *, void *);

/**
 * 获取指定位置的元素
 * @param list 指向list的指针
 * @param i 位置
 * @return 如果有返回元素的数据,否则NULL
 */
void *list_get(List *, uint);


/**
 * 删除一个list中指定的元素
 * @param list list 指向list的指针
 * @param i 位置
 * @return 如果删除成功返回被删除的数据,否则NULL
 */
void *list_remove(List *, uint);

/**
 * tostring
 * @return string
 */
char *list_to_string(List *);


#endif //TIMELY_LANG_LIST_H
