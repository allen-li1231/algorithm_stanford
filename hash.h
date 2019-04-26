#ifndef _HASH_H_INCLUDE_
#define _HASH_H_INCLUDE_
#define HASH_PRIME 11229331
#define _REDUNDANCY 4

typedef struct _HASH_TBL{
    int len;
    int seed;
    long **values;
    int (*h)(int, long);
    int (*h_collide)(long, long*);
} hash_table;

hash_table* newHash(int *func, int *func_collide, int seed);

int _h(int seed, long num);

int _h_collide(long num, long *ary);

void addHash(hash_table *t, long num);

#endif