#include "graph.h"
#include "nodes.h"
#include "algo.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>


extern int input;

extern int from_node;

extern pnode head;

extern char c ;


void build_graph_cmd(pnode *head)
{
    int num_of_nodes;
    input = scanf(" %d",&num_of_nodes);

    //The first 'n'
    if (num_of_nodes > 0) input = scanf(" %c",&c);
    
    while (c == 'n')
    {
        input = scanf(" %d",&from_node);
        insert_node_cmd(head);
    }
    if(DEBUG)printGraph_cmd(*head);
}



void deleteGraphRecursive(pnode node) {
    if (node == NULL) {
        return;
    }
    pedge current_edge = node->edges;
    while (current_edge != NULL) {
        // pnode endpoint = current_edge->endpoint;
        // deleteGraphRecursive(endpoint);
        pedge next_edge = current_edge->next;
        current_edge->endpoint = NULL;
        current_edge->next = NULL;
        node->edges = NULL;
        free(current_edge);
        current_edge = next_edge;
    }
    pnode next_node = node->next;
    node->next = NULL;
    free(node);
    deleteGraphRecursive(next_node);
}

void deleteGraph_cmd(pnode head)
{
    deleteGraphRecursive(head);
}





//for self debug
void printGraph_cmd(pnode head)
{
    pnode temp = head;
    do
    {
        printf("Node num %d:\n",temp->node_num);
        pedge ed = temp->edges;
        while (ed != NULL)
        {
            printf("Has edge to %d weight %d\n",ed->endpoint->node_num,ed->weight);
            ed = ed->next;
        }
        temp = temp->next;
    } while (temp != NULL);
    printf("That it\n");
} 
