OBJ = kruskal_clustering.o graph.o union-find.o hash.o
CFLAGS = -I.


kruskal_test : $(OBJ)
	gcc -o kruskal_test $(OBJ)

kruskal_clustering.o : kruskal_clustering.c graph.h union-find.h hash.h

graph.o : graph.c graph.h

union-find.o : union-find.c graph.h

hash.o : hash.c hash.h

.PHONY: clean
clean :
	rm -f $(OBJ)