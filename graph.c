#include <stdlib.h>
#include "graph.h"


typedef struct _VERTEX{
    unsigned int label;
    unsigned int dist;
    unsigned short explored;
    pedge first;
} vertex;


// out_degree ====> in_degree
typedef struct _EDGE{
    pvertex out_degree;
    pvertex in_degree;
    //define previous and next as sets of edges under out_degree vertex 
    pedge previous;
    pedge next;
} edge;


typedef struct _GRAPH{
    unsigned int len;
    unsigned int cursor;
    pvertex vertices[GRAPH_MAX_MEMBER];
    pvertex source_vertex;
} graph;


pvertex newVertex(pgraph g, int data){
    pvertex buffer = malloc(sizeof(vertex));
    g->vertices[g->len] = buffer;
    buffer->label = ++g->len;
    buffer->dist = data;
    buffer->explored = 0;
    buffer->first = NULL;
    return buffer;
}


pedge newEdge(pvertex out_degree, pvertex in_degree){
    pedge buffer = malloc(sizeof(edge));
    buffer->in_degree = in_degree;
    buffer->out_degree = out_degree;
    buffer->previous = getLastDegree(out_degree->first);
    buffer->next = NULL;

    //connect previous edge if available
    if (buffer->previous != NULL){
        pedge prev = getLastDegree(out_degree->first);
        prev->next = buffer;
    }
    //if this new edge is the first edge of its out_degree, concate vertex with this edge
    if (out_degree->first == NULL){
        out_degree->first = buffer;
    }
    return buffer;
}


pgraph newGraph(){
    pgraph buffer = malloc(sizeof(graph));
    buffer->len = 0;
    buffer->cursor = 0;
}


void freeVertex(pvertex v){
    while (v->first != NULL){
        freeEdge(v->first);
    }
    free(v);
}


void freeEdge(pedge e){
    if (e->next != NULL && e->previous != NULL){
        e->next->previous = e->previous;
        e->previous->next = e->next;
    }
    else if (e->previous != NULL)
    {
        e->previous->next = NULL;
    }
    else if (e->next != NULL){
        e->out_degree->first = e->next;
    }
    else e->out_degree->first = NULL;
    free(e);
}


void freeGraph(pgraph g){
    for (int i=0; i<=g->len; i++){
        freeVertex(g->vertices[i]);
    }
    free(g);
}


pedge getLastDegree(pedge e){
    pedge buffer = e;
    if (e != NULL){
        while (buffer->next != NULL){
            buffer = buffer->next;
        }
    }
    return buffer;
}


int main(){
    pgraph g = newGraph();
    pvertex v1 = newVertex(g, 10);
    pvertex v2 = newVertex(g, 12);
    pvertex v3 = newVertex(g, 3);
    pedge e1 = newEdge(v1, v2);
    pedge e2 = newEdge(v1, v3);
    printf("g->len: %d, %d, %p, %p, %p\n", g->len, v2->label, v1->first, e1->next->previous, e1);
    for (int i=0; i<=g->len;i++){
        printf("%p\n", g->vertices[i]);
    }
    return 0;
}