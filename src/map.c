//
// Created by zy on 8/11/20.
//
#include "../include/map.h"
#include "../include/list.h"
#include <stdlib.h>
#include <stdio.h>

unsigned long hash(void* key){
    return key == NULL? 0: (unsigned long )key;
}

unsigned int position(void* key, unsigned int m){
    return hash(key) % m;
}

struct list* map_get_(Map* map, void* key){
    unsigned int pos = position(key, map->capacity);
    return map->elem[pos];
}

Elem* new_elem(void* key, void* value){
    Elem* elem = malloc(sizeof(Elem));
    elem->key = key;
    elem->value = value;
    return elem;
}

Map* new_map(unsigned int size){
    Map* map = malloc(sizeof(Map));
    map->size = 0;
    map->capacity = size <= 0 ? 10 : size;
    map->elem = malloc(sizeof(struct list) * map->capacity);
    return map;
}

void map_put(Map* map, void* key, void* value){
    unsigned int pos = position(key, map->capacity);
    if (map->elem[pos] == NULL){
        map->elem[pos] = new_list();
    }
    struct list* els = map_get_(map, key);
    Elem* elem;
    Node* node = els->head;
    while (node != NULL){
        elem = node->data;
        if (hash(key) == hash(elem->key)){
            elem->value = value;
            return;
        }
        node = node->next;
    }
    list_add(els, new_elem(key, value));
    map->size++;
}

void* map_get(Map* map, void* key){
    struct list* els = map_get_(map, key);
    if (els == NULL)return NULL;
    Elem* elem;
    Node* node = els->head;
    while (node != NULL){
        elem = node->data;
        if (hash(key) == hash(elem->key)){
            return elem->value;
        }
        node = node->next;
    }
    return NULL;
}

void* map_remove(Map* map, void* key){
    struct list *els = map_get_(map,key);
    if (els == NULL)return NULL;
    Elem* elem;
    for (int i = 0; i < els->size; ++i) {
        elem = list_get(els,i);
        if (elem == NULL)return NULL;
        if (hash(elem->key) == hash(key)){
            list_remove(els,i);
            break;
        }
    }
    void* value = elem->value;
    free(elem);
    map->size--;
    return value;
}
