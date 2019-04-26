//@Author: Allen Lee        2019/4/12
#include <stdlib.h>
#include "graph.h"


pvertex newVertex(pgraph g, unsigned int label){
    if (g->vertices[label-1] == NULL){
        pvertex buffer = malloc(sizeof(vertex));
        buffer->label = label;
        buffer->belong = g;
        buffer->first = NULL;
        buffer->prev = NULL;
        g->vertices[label-1] = buffer;
        ++g->len;
        return buffer;
    }
    else return g->vertices[label-1];
}


pedge newEdge(pvertex out_degree, pvertex in_degree, unsigned int distance){
    pedge buffer = malloc(sizeof(edge));
    buffer->in_degree = in_degree;
    buffer->out_degree = out_degree;
    buffer->dist = distance;
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
    for (int i=0; i<GRAPH_MAX_MEMBER; i++){
        buffer->vertices[i] = NULL;
    }
    buffer->source_vertex = NULL;
}


void freeVertex(pvertex v){
    while (v->first != NULL){
        freeEdge(v->first);
    }
    v->belong->len--;
    free(v);
}


void freeEdge(pedge e){
    e->dist = 0;
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
        e->next->previous = NULL;
    }
    else e->out_degree->first = NULL;
    free(e);
}


void freeGraph(pgraph g){
    for (int i=0; i<g->len; i++){
        freeVertex(g->vertices[i]);
    }
    g->len = 0;
    g->cursor = 0;
    g->source_vertex = NULL;
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


void setSource(pvertex v){
    pgraph g = v->belong;
    g->source_vertex = v;
    for (int i=0; i<g->len; i++){
        g->vertices[i]->data = INF;
        g->vertices[i]->prev = NULL;
    }
    v->data = 0;
}

/*How to use:
int main(){
    pgraph g = newGraph();
    pvertex v1 = newVertex(g);
    pvertex v2 = newVertex(g);
    pvertex v3 = newVertex(g);
    pedge e1 = newEdge(v1, v2, 3);
    pedge e2 = newEdge(v1, v3, 2);
    printf("g->len: %d, %d, %p, %p, %p\n", g->len, v2->label, v1->first, e1->next->previous, e1);
    for (int i=0; i<=g->len;i++){
        printf("%p\n", g->vertices[i]);
    }
    freeGraph(g);
    return 0;
}*/