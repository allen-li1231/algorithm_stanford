//@Author: Allen Li		2020/7/1
#include <stdio.h>
#include "graph.h"
#include "hash.h"
#include "union-find.h"


void sortByNodeValue(hash_node** nodes, int left, int right)
{
    // quick sort implementation
	if (left >= right)
	{
		return;
	}

	hash_node *TEMP = nodes[left];
	long pivot = TEMP->value;
	int i = left;
	int j = right;
	while (left < right)
	{
		while (left < right && nodes[right]->value >= pivot)
		{
			right--;
		}
		nodes[left] = nodes[right];

		while (left < right && nodes[left]->value <= pivot)
		{
			left++;
		}
		nodes[right] = nodes[left];

	}
	nodes[left] = TEMP;

	sortByNodeValue(nodes, i, left-1);
	sortByNodeValue(nodes, right+1, j);
}


hash_node** quickSort_nodes(hash_node** nodes, unsigned int length, unsigned short ascending, unsigned short copy)
{
	if (length <= 1)
	{
		return nodes;
	}

    // make a copy of original nodes if required
	if (copy == 1)
	{
		hash_node** copied_nodes = newNodes(length);
		for (int i=0; i<length; i++)
		{
			copied_nodes[i] = newHashNode(nodes[i]->key, nodes[i]->value);
		}
		nodes = copied_nodes;
	}

    // sort by node->values
	sortByNodeValue(nodes, 0, length-1);

    // traverse to descending order if required
	if (ascending == 0)
	{
		hash_node *TEMP;
    	int i = 0;
    	int j = length-1;
    	
		while (i < j)
		{
			TEMP = nodes[i];
			nodes[i] = nodes[j];
			nodes[j] = TEMP;
			
			i++;
			j--;
		}
	}
	return nodes;
}



node_array* loadEdgeDistToNodeArray(pgraph g)
{
	node_array* nArray = newNodeArray(g->edge_count);

	pvertex v;
	int j;
	// edges mapping to an node array
	for (int i = 0; i < g->max_vertices; i++)	// for each vertex in the graph
	{
		j = 0;
		v = g->vertices[i];
		if (v == NULL)
		{
			continue;
		}

		// for each edge related to a vertex
		while (j < g->max_vertices)	// thread unsafe
		{
			if (v->first[j] != NULL && lookupNodeArray(v->first[j], nArray) == -1)
			{
				putNodeArray(v->first[j], v->first[j]->dist, nArray);
			}
			j++;
		}
	}
	return nArray;
}


pgraph readFile(char* file_path)
{
	FILE *fp = fopen(file_path, "r");
	char buff[16] = { 0 };
	char* endp;
	// read first line number, aka. number of vertices in the graph
	fgets(buff, 15, fp);
	pgraph g = newGraph(strtol(buff, &endp, 10));
	printf("Assigning vertex number: %s", buff);
	pvertex out_vtx, in_vtx;
	while (!feof(fp))
	{
		fgets(buff, 15, fp);
		out_vtx = newVertex(g, strtol(buff, &endp, 10));
		in_vtx = newVertex(g, strtol(endp, &endp, 10));
		newEdge(out_vtx, in_vtx, strtol(endp, &endp, 10), 0);
	}
	fclose(fp);
	return g;
}


int main(int argc, char *argv[])
{

	long K;
	char *file_path;
	if (argc == 2)
	{
		K = strtol(argv[0]);
		file_path = argv[1];
	}
	else
	// k-clustering in assignment requires k=4
	{
		K = 4;
		file_path = "./data/clustering1.txt";
	}

	pgraph g = readFile(file_path);
	if (g->len < K || g->edge_count - g->len < K)
	{
		printf("Unable to merge graph to %d clusters: edges not sufficient\n", K);
		return 0;
	}

	initUnionFind(g);
	// line below is time costy, my node array wheel doesn't look efficient
	node_array* nArray = loadEdgeDistToNodeArray(g);
	nArray->nodes = quickSort_nodes(nArray->nodes, nArray->length, 1, 0);

	// apply clustering using union-find method (assuming graph is fully linked)
	pedge pNode;
	int i, j;
	long max_spacing;
	// everytime we merge a vertex, number of clusters decreases by 1
	for (i = 0, j=g->len; j > K && i < nArray->length; i++, j--)
	{
		pNode = nArray->nodes[i]->key;
		// number of clusters doesn't decrease by 1 if the two vertices from a edge belong to a same cluster
		// so we j++ to cancel j--
		if (uFind(pNode->in_degree) == uFind(pNode->out_degree))
		{
			j++;
		}
		unionF(pNode->out_degree, pNode->in_degree);
	}

	// start from edges that not have been unioned
	printf("First length of outer edge: %d\n", nArray->nodes[i]->value);
	for (; i < nArray->length; i++)
	{
		pNode = nArray->nodes[i]->key;
		if (uFind(pNode->in_degree) != uFind(pNode->out_degree))
		{
			max_spacing = pNode->dist;
			break;
		}
	}
	printf("maximum spacing of a %d-clustering: %ld\n", K, max_spacing);
	getchar();
	freeNodeArray(nArray);
	freeGraph(g);
	return 0;
}