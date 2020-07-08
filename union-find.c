//@Author: Allen Li		2020/7/1
#include "graph.h"


void initUnionFind(pgraph g)
{
	for (int i=0; i<g->len; i++)
	{
		pvertex buffer = g->vertices[i];
		buffer->data = 0;
		buffer->prev = buffer;
	}
}

pvertex uFind(pvertex v)
{
	if (v->prev != v)
	{
		v->prev = uFind(v->prev);
	}
	return v->prev;
}

pvertex unionF(pvertex x, pvertex y)
{
	pvertex xRoot = uFind(x);
	pvertex yRoot = uFind(y);

	if (xRoot == yRoot)
	{
		return xRoot;
	}
	if (xRoot->data == yRoot->data)
	{
		xRoot->data++;
		yRoot->prev = xRoot;
	}
	
	if (xRoot->data >= yRoot->data)
	{
		yRoot->prev = xRoot;
		return xRoot;
	}
	else
	{
		xRoot->prev = yRoot;
		return yRoot;
	}
}	