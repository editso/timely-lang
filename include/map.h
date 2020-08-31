//
// Created by zy on 8/11/20.
//

#ifndef TIMELY_LANG_MAP_H
#define TIMELY_LANG_MAP_H
#include "ttypes.h"

typedef struct elem_{
    void* key;
    void* value;
}Elem;

typedef struct map_{
    /**
     * 当前数量
     */
    uint size;
    /**
     * 容量
     */
    uint capacity;
    /**
     * < capacity 的最大质数
     */
    uint prime;
    /**
     * 数组
     */
    void **elem;
}Map;

/**
 * 创建一个 map
 * @param size 空间大小 <= 0 那么将默认开辟10个空间
 * @return
 */
Map* new_map(uint size);

/**
 * 向Map添加一个元素
 * @param map map指针
 * @param key 键
 * @param value 值
 */
void map_put(Map* map, void* key, void* value);
/**
 * 删除一个元素
 * @param map map指针
 * @param key 键
 * @return 如果删除成功返回被删除的元素
 */
void* map_remove(Map* map, void* key);

/**
 * 获取一个元素
 * @param map map指针
 * @param key 键
 * @return 如果有返回 元素 否则 NULL
 */
void* map_get(Map* map, void* key);

#endif //TIMELY_LANG_MAP_H
