//
// Created by zy on 8/7/20.
//
#ifndef TIMELY_LANG_LIST_C_H
#define TIMELY_LANG_LIST_C_H
#include "include/list.h"
#include <string.h>

ListNode* new_node(void* data){
    ListNode* node = malloc(sizeof(ListNode));
    node->data = data;
    return node;
}

/**
 * 创建一个新的list
 * @return 新的 list
 */
List * new_list(){
    List * list = malloc(sizeof(List));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

/**
 * 向list添加一个元素
 * @param list 指向list的指针
 * @param data 数据
 */
void list_add(List * list, void *data){
    list_insert(list, list->size, data);
}

ListNode* list_get_(List * list, unsigned int index){
    if (index >= list->size || index < 0){
        return NULL;
    }
    int tmp = 0;
    ListNode *curNode = list->head;
    while (curNode != NULL){
        if (tmp == index){
            return curNode;
        }
        tmp++;
        curNode = curNode->next;
    }
    return NULL;
}

/**
 * 向list指定位置插入一个元素
 * @param list 指向list的指针
 * @param 插入的位置
 * @param data数据 插入成功 1, 失败-1;
 */
int list_insert(List * list, unsigned int index, void *data){
    ListNode* new = new_node(data);
    // 第一个位置插入
    if (index == 0 || index == 1){
        if (list->head == NULL){
            /**
            * 如果头为空,说明没有添加任何数据,所以直接插入
            */
            list->head = new;
        }else if (list->tail == NULL){
            /**
             * 如果尾部也是空,说明这是第二次添加, 所以直接插入到尾
             */
            list->tail = new;
            new->prev = list->head;
            list->head->next = new;
        }else{
            /**
             * 直接在第一个位置插入
             */
            list->head->prev = new;
            new->next = list->head;
            list->head = new;
        }
    }else{
        ListNode* node = list_get_(list, index);
        if (node != NULL){
            /**
             * 直接插入到指定位置
             */
            new->next = node;
            new->prev = node->prev;
            node->prev->next = new;
            node->prev = new;
        }else if(node == NULL && list->size == index){
            /**
             * node等于空且 list->size == index 说明需要更新尾部
             */
            new->prev = list->tail;
            list->tail->next = new;
            list->tail = new;
        }else{
            /**
             * 越界
             */
            return -1;
        }
    }
    /**
     * 维护 size
     */
    list->size++;
    return 1;
}

/**
 * 获取指定位置的元素
 * @param list 指向list的指针
 * @param i 位置
 * @return 如果有返回元素的数据,否则NULL
 */
void* list_get(List * list, unsigned int index){
    ListNode* node = list_get_(list, index);
    if (node == NULL)return NULL;
    return node->data;
}

/**
 * 删除一个list中指定的元素
 * @param list list 指向list的指针
 * @param i 位置
 * @return 如果删除成功返回被删除的数据,否则NULL
 */
void* list_remove(List * list, unsigned int index){
    if (index >= list->size){
        return NULL;
    }
    ListNode *node = list_get_(list, index);
    if (node == NULL)
        return NULL;
    if (index == 0){
        /**
         * 删除头
         */
        list->head = node->next;
    }else if (index == list->size - 1){
        // 删除尾
        list->tail = node->prev;
        node->prev->next = NULL;
    }else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    list->size --;
    void* data = node->data;
    free(node);
    // 防止出现野指针
    if (list->size == 0){
        list->head = list->tail = NULL;
    }
    return data;
}

/**
 * 只针对list 集合是 char 类型时有效
 * @param list 需要被转换为string的集合
 * @return 转换后的
 */
char* list_to_string(List * list){
    char* s= malloc(sizeof(char ) * list->size);
    for (int i = 0; i < list->size; ++i) {
        memmove(s+i, list_get(list, i), 1);
    }
    return s;
}



#endif //TIMELY_LANG_LIST_C_H
