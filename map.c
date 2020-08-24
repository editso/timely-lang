//
// Created by zy on 8/11/20.
//
#include "include/map.h"
#include "include/list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

unsigned long hash(void *key) {
    return key ? (unsigned long) key : 0;
}

unsigned int hash_fun(void *key, unsigned int m) {
    return hash(key) % m;
}

List *map_get_(Map *map, void *key) {
    unsigned int pos = hash_fun(key, map->prime);
    return map->elem[pos];
}

Elem *new_elem(void *key, void *value) {
    Elem *elem = malloc(sizeof(Elem));
    elem->key = key;
    elem->value = value;
    return elem;
}

/**
 * 获取一个数中最大的质数
 * @param number >= 2
 * @return < 2 返回 2 否则返回最大的质数
 */
unsigned int get_prime(unsigned int number) {
    for (unsigned int i = number; i >= 2; --i) {
        for (int j = 2; j < i; ++j) {
            if (i % j == 0)
                break;
            if (j == i - 1)
                return i;
        }
    }
    return 2;
}

Map *new_map(unsigned int size) {
    Map *map = malloc(sizeof(Map));
    map->size = 0;
    map->capacity = size ? size : 11;
    map->elem = malloc(sizeof(List) * map->capacity);
    map->prime = get_prime(map->capacity);
    return map;
}

void map_put(Map *map, void *key, void *value) {
    unsigned int pos = hash_fun(key, map->prime);
    if (map->elem[pos] == NULL) {
        map->elem[pos] = new_list();
    }
    List *els = map_get_(map, key);
    Elem *elem;
    Node *node = els->head;
    while (node != NULL) {
        elem = node->data;
        if (hash(key) == hash(elem->key)) {
            elem->value = value;
            return;
        }
        node = node->next;
    }
    list_add(els, new_elem(key, value));
    map->size++;
}

void *map_get(Map *map, void *key) {
    List *els = map_get_(map, key);
    if (els == NULL)return NULL;
    Elem *elem;
    Node *node = els->head;
    while (node != NULL) {
        elem = node->data;
        if (hash(key) == hash(elem->key)) {
            return elem->value;
        }
        node = node->next;
    }
    return NULL;
}

void *map_remove(Map *map, void *key) {
    List *els = map_get_(map, key);
    if (els == NULL)return NULL;
    Elem *elem;
    for (int i = 0; i < els->size; ++i) {
        elem = list_get(els, i);
        if (elem == NULL)return NULL;
        if (hash(elem->key) == hash(key)) {
            list_remove(els, i);
            break;
        }
    }
    void *value = elem->value;
    free(elem);
    map->size--;
    return value;
}

