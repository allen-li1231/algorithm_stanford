#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF __INT32_MAX__
#define GRAPH_MAX_MEMBER 300

typedef struct _EDGE edge, *pedge;

typedef struct _GRAPH graph, *pgraph;

typedef struct _VERTEX{
    unsigned int label;
    unsigned short explored;
    unsigned long data;
    pgraph belong;
    pedge first;
} vertex, *pvertex;

// out_degree ====> in_degree
typedef struct _EDGE{
    unsigned int dist;
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

pvertex newVertex(pgraph g);

pedge newEdge(pvertex out_degree, pvertex in_degree, unsigned distance);

pgraph newGraph();

void freeGraph(pgraph g);

void freeEdge(pedge);

void freeVertex(pvertex);

pedge getLastDegree(pedge e);

void setSource(pvertex v);


#endif