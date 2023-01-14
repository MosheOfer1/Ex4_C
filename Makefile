CC=gcc
AR=ar
FLAGS= -Wall -c -g
OBJECTS_MAIN=main.o
OBJECTS_GRAPH=graph.o
OBJECTS_NODE=nodes.o
OBJECTS_ALGO=algo.o
LIB_S=libgraph.a

all: graph
$(OBJECTS_MAIN): main.c
	$(CC) $(FLAGS) main.c -o $(OBJECTS_MAIN)

$(OBJECTS_GRAPH): graph.c
	$(CC) $(FLAGS) graph.c -o $(OBJECTS_GRAPH)
	
$(OBJECTS_NODE): nodes.c
	$(CC) $(FLAGS) nodes.c -o $(OBJECTS_NODE)
	
$(OBJECTS_ALGO): algo.c
	$(CC) $(FLAGS) algo.c -o $(OBJECTS_ALGO)

$(LIB_S): $(OBJECTS_MAIN) $(OBJECTS_GRAPH) $(OBJECTS_NODE) $(OBJECTS_ALGO) 
	$(AR) rcs $(LIB_S) $(OBJECTS_MAIN) $(OBJECTS_GRAPH) $(OBJECTS_NODE) $(OBJECTS_ALGO)

graph: $(LIB_S)
	$(CC) -o graph $(OBJECTS_MAIN) -L. $(LIB_S)

.PHONY: clean all
	
clean:
	rm -f *.o *.a "graph"

