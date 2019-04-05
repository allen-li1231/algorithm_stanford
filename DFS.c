#include <stdlib.h>
#include <stdio.h>
#define BOOL int
#define TRUE 1
#define FALSE 0


typedef struct _VERTEX{
    int label;
    int data;
    BOOL explored;
} vertex;
typedef vertex* pvertex;


typedef struct _EDGE{
    int label;
    pvertex out_degree;
    pvertex in_degree;
} edge;
typedef edge* pedge;


typedef struct _VERTEX_LIST{
    int len;
    //int level;
    pvertex head;
    pvertex tail;
} list;
typedef list *plist;


pvertex newVertex(int label, int data){
    pvertex buffer = malloc(sizeof(vertex));
    buffer->label = label;
    buffer->data = data;
    buffer->explored = FALSE;
    return buffer;
}


plist newList(){
    plist buffer = malloc(sizeof(list));
    buffer->len = 0;
    buffer->head = NULL;
    buffer->tail = NULL;
    return buffer;
}


void appendList(plist list_to_append, int data){
    pvertex new_vtx = newVertex(list_to_append->len, data);
    if (list_to_append->len==0){
        list_to_append->head = new_vtx;
        list_to_append->tail = new_vtx;
    }
    else {
        pvertex buffer = list_to_append->tail;
        list_to_append->tail = new_vtx;
    }
    list_to_append->len++;
}

int main(){
    printf("%d, %d\n", sizeof(list), sizeof(vertex));
}