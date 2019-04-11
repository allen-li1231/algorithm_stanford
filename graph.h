#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define GRAPH_MAX_MEMBER 300
#define INF -1

typedef struct _VERTEX vertex;

typedef vertex* pvertex;

typedef struct _EDGE edge;

typedef edge* pedge;

typedef struct _GRAPH graph;

typedef graph* pgraph;

void freeEdge(pedge);

void freeVertex(pvertex);

pedge getLastDegree(pedge e);

pvertex Dijkstra_shortest_path(pgraph g, vertex v);

#endif