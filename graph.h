#ifndef GRAPH_
#define GRAPH_


#define DEBUG 0


typedef struct GRAPH_NODE_ *pnode;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;


void build_graph_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode head);
void shortsPath_cmd(pnode head);
void TSP_cmd(pnode head);

#endif
