#include <stdlib.h>
#include "hash.h"

//TODO: expand and shrink size of hash table, delete from table not done yet.

hash_table* newHash(int *func, int *func_collide, int seed){
    hash_table *buff = malloc(sizeof(hash_table));
    long **v = malloc(sizeof(*v)*HASH_PRIME);
    for (int i=0; i<HASH_PRIME; i++){
        v[i] = (long*)calloc(_REDUNDANCY+1, sizeof(long));
    }
    buff->len = 0;
    buff->values = v;
    buff->seed = seed;

    if (func == NULL){
        buff->h = &_h;
    }
    else {
        buff->h = func;
    }

    if (func_collide == NULL){
        buff->h_collide = &_h_collide;
    }
    else{
        buff->h_collide = func_collide;
    }
    return buff;
}


int _h(int seed, long num){
    int idx = seed*num % HASH_PRIME;
    if (idx<0){
        return idx+HASH_PRIME;
    }
    else return idx;
}


int _h_collide(long num, long *ary){
    for (int i=0; i<_REDUNDANCY; i++){
        if (ary[i] == num) return 0;
        else if (ary[i] == 0){
            ary[i] = num;
            return 0;
        }
    }
    printf("Array out of space, occured in index %d\n", num);
    return -1;
}


void addHash(hash_table *t, long num){
    int idx = t->h(t->seed, num);
    if (t->values[idx][0] == 0) t->values[idx][0] = num;
    else t->h_collide(num, t->values[idx]);
}


int lookupHash(hash_table *t, long lookup_value){
    int idx = t->h(t->seed, lookup_value);
    int i = 0;
    while (t->values[idx][i]){
        if (t->values[idx][i] == lookup_value) return 1;
        i++;
    }
    return 0;
}