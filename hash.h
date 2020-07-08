#ifndef _HASH_H_INCLUDE_
#define _HASH_H_INCLUDE_
#define HASH_PRIME 11229331
#define _REDUNDANCY 3


typedef struct _HASH_NODE{
	void* key;
	long value;
} hash_node;

typedef struct _NODE_ARRAY{
	unsigned int length;
	unsigned int max_nodes;
	hash_node** nodes;
} node_array;

typedef struct _HASH_TBL{
    int len;
    int seed;
    long **values;
    int (*h)(int, int);
    int (*h_collide)(long, long*);
} hash_table;

typedef struct _HASH_MAP{
    int len;
    int seed;
    hash_node ***nodes;
    int (*h)(int, int);
    int (*h_collide)(void*,  long,  hash_node **);
} hash_map;


hash_node* newHashNode(void* key, long value);

hash_node** newNodes(unsigned int n);

node_array* newNodeArray(unsigned int length);

hash_table* newHash(int seed);

hash_map* newHashMap(int seed);

void addHash(hash_table *t, long num);

int lookupHash(hash_table *t, long lookup_value);

int addMap(hash_map *t, void* key, long value);

hash_node* lookupMap(hash_map *t, void* key);

void putNodeArray(void* key, long value, node_array* ary);

int rmNodeArray(void* key, node_array* ary);

int lookupNodeArray(void* key, node_array* ary);

void freeHashMap(hash_map* h);

void freeNodes(hash_node** nodes, int length);

void freeNodeArray(node_array* v);

#endif