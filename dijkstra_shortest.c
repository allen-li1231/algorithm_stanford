#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


pgraph readFromAssignment(){
    /*The file contains an adjacency list representation of an undirected weighted graph with 200 vertices labeled 1 to 200. 
    Each row consists of the node tuples that are adjacent to that particular vertex along with the length of that edge. 
    For example, the 6th row has 6 as the first entry indicating that this row corresponds to the vertex labeled 6. 
    The next entry of this row "141,8200" indicates that there is an edge between vertex 6 and vertex 141 that has length 8200.
    The rest of the pairs of this row indicate the other vertices adjacent to vertex 6 and the lengths of the corresponding edges.*/
    /*Data example:
    1	80,982	163,8164	170,2620	145,648	200,8021	
    2	42,1689	127,9365	5,8026	170,9342	131	
    3	57,1239	101,3381	43,7313	41,7212	91
    4	162,3924	70,5285	195,2490
    5	200,4009	112,1522	25,3496	23,9432	64,7836	56,8262	120,1862
    6	141,8200	98,5594	66,6627	159,9500	143,3110	129,8525	118,8547	88,2039	83
    ....
    */
   FILE *pf = fopen("./dijkstraData.txt", "r");
   char buff[300] = {0};
   char* ptok;
   pgraph g = newGraph();
   pvertex vout, vin;
    while (!feof(pf)){
        fgets(buff, 300, pf);
        ptok = strtok(buff, "	");
        vout = newVertex(g, atoi(ptok));
        while (1){
            ptok = strtok(NULL, ",\n");
            if (ptok == NULL || *ptok == '\n') break;
            vin = newVertex(g, atoi(ptok));
            ptok = strtok(NULL, "\n	");
            newEdge(vout, vin, atoi(ptok));
        }
    }
    return g;
}


void dijkstra_shortest(pvertex v){
    pedge e = v->first;
    if (e != NULL){
        while (e->next != NULL){
            if (e->in_degree->data > v->data + e->dist){
            ///if (e->in_degree->explored == 0){
                e->in_degree->data = v->data + e->dist;
                e->in_degree->explored ++;
                dijkstra_shortest(e->in_degree);
            }
            e = e->next;
        }
        if (e->in_degree->data > v->data + e->dist){
        ///if (e->in_degree->explored == 0){
            e->in_degree->data = v->data + e->dist;
            e->in_degree->explored ++;
            dijkstra_shortest(e->in_degree);
        }
    }
    else return;
}


int main(){
    pgraph g0 = readFromAssignment();
    pvertex source_v = g0->vertices[0];
    setSource(source_v);
    dijkstra_shortest(source_v);
    printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
    g0->vertices[6]->data, g0->vertices[36]->data, 
    g0->vertices[58]->data, g0->vertices[81]->data, 
    g0->vertices[98]->data, g0->vertices[114]->data, 
    g0->vertices[132]->data, g0->vertices[164]->data, 
    g0->vertices[187]->data, g0->vertices[196]->data);
    return 0;
}
