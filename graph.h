//@Author: Allen Lee        2019/4/12
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_

#define INF __INT32_MAX__
#define GRAPH_MAX_MEMBER 300

typedef struct _EDGE edge, *pedge;

typedef struct _GRAPH graph, *pgraph;

typedef struct _VERTEX{
    unsigned int label;     //indicate the position of vertex in the graph array.
    unsigned long data;     //store necessary data for different algorithms, for Dijkstra's shortest path, it's the shortest path.
    pgraph belong;      //indicate the graph that vertex belongs.
    pedge first;        //point to the first edge of which this vertex act as out vertex.
    struct _VERTEX* prev;   //store necessary pointer for Dijkstra's algorithm so as to trace back the shortest path.
} vertex, *pvertex;

// out_degree ====> in_degree
typedef struct _EDGE{
    unsigned int dist;      //initial length of the edge.
    pvertex out_degree;
    pvertex in_degree;
    pedge previous;    //define previous and next as sets of edges under out_degree vertex 
    pedge next;
} edge;

typedef struct _GRAPH{
    unsigned int len;       //the overall number of vertices in the graph.
    unsigned int cursor;    //a subindex for the vertices array.
    pvertex vertices[GRAPH_MAX_MEMBER];     //the vessel containing pointers of vertices in the graph
    pvertex source_vertex;
} graph;

pvertex newVertex(pgraph g, unsigned int label);

pedge newEdge(pvertex out_degree, pvertex in_degree, unsigned int distance);

pgraph newGraph();

void freeGraph(pgraph g);

void freeEdge(pedge);

void freeVertex(pvertex);

pedge getLastDegree(pedge e);

void setSource(pvertex v);


#endif