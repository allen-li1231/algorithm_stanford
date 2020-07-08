#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

//TODO: expand and shrink size of hash table, delete from table not done yet.

int _h(int seed, int num){
	// could be faster if using bitwise operation
    int idx = seed*num % HASH_PRIME;
    if (idx < 0)
	{
        return idx + HASH_PRIME;
    }
    return idx;
}


int _h_collide(long num, long *ary){
    for (int i=0; i<_REDUNDANCY; i++){
        if (ary[i] == num) return 0;
        else if (ary[i] == 0){
            ary[i] = num;
            return 0;
        }
    }
    printf("Array out of space, occured in index %ld\n", num);
    return -1;
}


hash_table* newHash(int seed) {
	hash_table *buff = malloc(sizeof(hash_table));
	long **v = malloc(sizeof(*v)*HASH_PRIME);
	for (int i = 0; i < HASH_PRIME; i++) {
		v[i] = (long*)calloc(_REDUNDANCY + 1, sizeof(long));
	}
	buff->len = 0;
	buff->values = v;
	buff->seed = seed;

	buff->h = &_h;
	buff->h_collide = &_h_collide;

	return buff;
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


hash_node* newHashNode(void* key, long value)
{
	hash_node* buff = (hash_node*) malloc(sizeof(hash_node));
	buff->key = key;
	buff->value = value;
	return buff;
}

hash_node** newNodes(unsigned int length)
{
	hash_node **v = (hash_node**) calloc(length, sizeof(hash_node));
	
	for (unsigned int i=0; i<length; i++)
	{
        v[i] = NULL;
    }
	
	return v;
}

node_array* newNodeArray(unsigned int length)
{
	if (length < 1)
	{
		return NULL;
	}
	node_array* buff = (node_array*) malloc(sizeof(node_array));
	buff->max_nodes = length;
	buff->length = 0;
	buff->nodes = newNodes(length);
	return buff;
}

void putNodeArray(void* key, long value, node_array* ary)
{
	if (ary->length >= ary->max_nodes)
	{
		printf("Unable to add node (%d, %ld) to array becasuse it is full", key, value);
		return;
	}

	hash_node* buff = (hash_node*)malloc(sizeof(hash_node));
	buff->key = key;
	buff->value = value;
	int i = 0;
	while (ary->nodes[i] != NULL)
	{
		i++;
	}
	ary->nodes[i] = buff;
	ary->length++;
}

int rmNodeArray(void* key, node_array* ary)
{
	for (int i = 0; i < ary->max_nodes; i++)
	{
		if (ary->nodes[i]->key == key)
		{
			free(ary->nodes[i]);
			ary->nodes[i] = NULL;
			ary->length--;
			return 1;
		}
	}
	return 0;
}

int lookupNodeArray(void* key, node_array* ary)
{
	for (int i = 0, j = 0; i < ary->max_nodes && j < ary->length; i++, j++)
	{
		if (ary->nodes[i]->key == key)
		{
			return i;
		}
	}
	return -1;
}

int _hMap_collide(void* key, long value, hash_node **node){
    for (int i=0; i<_REDUNDANCY; i++){
		if (node[i]->key != NULL && node[i]->key == key)
		{
			node[i]->value = value;
			return 1;
		}
        if (node[i]->key != NULL && node[i]->key == 0)
		{
            node[i]->value = value;
            return 0;
        }
    }
    printf("Array out of space, occured in value %ld\n", value);
    return -1;
}

hash_map* newHashMap(int seed){
    hash_map *buff = malloc(sizeof(hash_map));
    hash_node ***v = (hash_node***) malloc(sizeof(*v)*HASH_PRIME);
    for (int i=0; i<HASH_PRIME; i++){
        v[i] = newNodes(_REDUNDANCY);
		for (int j=0; j<_REDUNDANCY; j++)
		{
			v[i][j]->key = NULL;
			v[i][j]->value = 0;
		}

    }
    buff->len = 0;
    buff->nodes = v;
    buff->seed = seed;

    buff->h = &_h;
    buff->h_collide = &_hMap_collide;

    return buff;
}

int addMap(hash_map *t, void* key, long value)
{
	// return 1 if overwrite, 0 if normal add, -1 if fail
	int idx = t->h(t->seed, key);
	int status = t->h_collide(key, value, t->nodes[idx]);
	if (status == 0)
	{
		t->len++;
	}
	return status;
}

hash_node *lookupMap(hash_map *t, void* key)
{
    int idx = t->h(t->seed, key);
	for (int i = 0; i < _REDUNDANCY; i++) 
	{
		if (t->nodes[idx][i]->key != NULL && t->nodes[idx][i]->key == key)
		{
			return t->nodes[idx][i];
		}
	}
	printf("Key not found: %d, NULL returned\n", key);
    return NULL;
}


int rmMap(void* key, hash_map* t)
{
	int idx = t->h(t->seed, key);
	hash_node** node = t->nodes[idx];
	for (int i = 0; i < _REDUNDANCY; i++) {
		if (node[i]->key != NULL && node[i]->key == key)
		{
			node[i]->key = NULL;
			node[i]->value = 0;
			t->len--;
			return 0;
		}
	}
	return -1;
}


void freeHashMap(hash_map* h)
{
	for (int i=0; i<HASH_PRIME; i++)
	{
		for (int j=0; j<_REDUNDANCY; j++)
		{
			free(h->nodes[i][j]);
		}
		free(h->nodes[i]);
	}
	free(h->nodes);
	free(h);
}

void freeNodes(hash_node** nodes, int length)
{
	for (int i=0; i<length; i++)
	{
		if (nodes[i] != NULL)
		{
			free(nodes[i]);
		}
		
	}
	free(nodes);
}

void freeNodeArray(node_array* v)
{
	freeNodes(v->nodes, v->max_nodes);
	free(v);
}