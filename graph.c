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
		buffer->edgeCount = 0;
		buffer->data = 0;
        return buffer;
    }
    else return g->vertices[label-1];
}


pedge newEdge(pvertex out_degree, pvertex in_degree, unsigned int distance, unsigned short directed){
    pedge buffer = malloc(sizeof(edge));
	buffer->directed = directed;
    buffer->in_degree = in_degree;
    buffer->out_degree = out_degree;
	buffer->previous = NULL;
    buffer->dist = distance;
    buffer->next = NULL;

    //connect previous edge if available
	if (directed == 1)
	{
		buffer->previous = getLastDegree(out_degree->first);
		if (buffer->previous != NULL) {
			pedge prev = getLastDegree(out_degree->first);
			prev->next = buffer;
		}
	}

    //if this new edge is the first edge of its out_degree, concate vertex with this edge
    if (out_degree->first == NULL)
	{
        out_degree->first = malloc(sizeof(pedge) * out_degree->belong->max_vertices);
		for (int i = 0; i < out_degree->belong->max_vertices; i++)
		{
			out_degree->first[i] = NULL;
		}
    }
	//add edge to adjacent list in vertex struct
	int i = 0;
	while (out_degree->first[i] != NULL)
	{
		i++;
	}
	out_degree->first[i] = buffer;
	out_degree->edgeCount++;
	out_degree->belong->edge_count++;
	if (directed == 0)
	{
		if (in_degree->first == NULL)
		{
			in_degree->first = malloc(sizeof(pedge) * in_degree->belong->max_vertices);
			for (int i = 0; i < in_degree->belong->max_vertices; i++)
			{
				in_degree->first[i] = NULL;
			}
		}
		i = 0;
		while (in_degree->first[i] != NULL)
		{
			i++;
		}
		in_degree->first[i] = buffer;
		in_degree->edgeCount++;
		in_degree->belong->edge_count++;
	}
    return buffer;
}


pgraph newGraph(unsigned int nVertices){
    pgraph buffer = malloc(sizeof(graph));
    buffer->len = 0;
    buffer->cursor = 0;
	buffer->max_vertices = nVertices;
	buffer->edge_count = 0;
    for (unsigned int i=0; i<nVertices; i++)
	{
        buffer->vertices[i] = NULL;
    }
    buffer->source_vertex = NULL;
	return buffer;
}


void freeVertex(pvertex v){
	int i = v->edgeCount;
    while (i > 0)
	{
        freeEdge(v->first[i - 1]);
		i--;
    }
    v->belong->len--;
    free(v);
}


void freeEdge(pedge e){
	if (e == NULL)
	{
		return;
	}

	if (e->directed == 1)
	{
		if (e->next != NULL && e->previous != NULL) {
			e->next->previous = e->previous;
			e->previous->next = e->next;
		}
		else if (e->previous != NULL)
		{
			e->previous->next = NULL;
		}
		else if (e->next != NULL) {
			e->out_degree->first[0] = e->next;
			e->next->previous = NULL;
		}
		e->out_degree->belong->edge_count--;
	}
    
	if (e->directed == 0)
	{
		int i = 0;
		if (e->out_degree->first != NULL)
		{
			while (i < e->out_degree->edgeCount && e->out_degree->first[i] != e)
			{
				i++;
			}
			e->out_degree->first[i] = NULL;
			e->out_degree->edgeCount--;
			e->out_degree->belong->edge_count--;
		}

		i = 0;
		if (e->in_degree->first != NULL)
		{
			while (i < e->in_degree->edgeCount && e->in_degree->first[i] != e)
			{
				i++;
			}
			e->in_degree->first[i] = NULL;
			e->in_degree->edgeCount--;
			e->in_degree->belong->edge_count--;
		}
	}
    free(e);
}


void freeGraph(pgraph g){
    for (int i=0; i<g->len; i++)
	{
        freeVertex(g->vertices[i]);
    }
    free(g);
}


pedge getLastDegree(pedge *e){
    pedge buffer = NULL;
    if (e != NULL){
		buffer = e[0];
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
    pgraph g = newGraph(500);
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