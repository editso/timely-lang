//
// Created by zy on 8/7/20.
//

#ifndef TIMELY_LANG_LIST_H
#define TIMELY_LANG_LIST_H

struct node{
    void *data;
    struct node* next;
};

struct list{
    struct node node;
};

void list_add(void *);

void* list_get(int i);

void* list_remove();

#endif //TIMELY_LANG_LIST_H
