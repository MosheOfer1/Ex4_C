#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <limits.h>
#include "graph.h"
#include "nodes.h"
#include "algo.h"

int input;

int from_node;

pnode head;

char c ;

void insert_node_cmd(pnode *head)
{
    pnode prev = *head;
    pnode n = prev;
    while (n != NULL)
    {
        if (n->node_num == from_node)
        {
            break;
        }
        
        prev = n;
        n = n->next;
    }

    
    if (prev == NULL)
    {
        *head = malloc(sizeof(node));
        if (*head == NULL)
        {
            perror("not enogh space: ");
            exit(-1);
        }
        
        bzero(*head,sizeof(node));
        n = *head;
        n->node_num = from_node;
        n->next = NULL;
    }
    else if (n == NULL)
    {
        prev->next = malloc(sizeof(node));
        if (prev->next == NULL)
        {
            perror("not enogh space: ");
            exit(-1);
        }
        bzero(prev->next,sizeof(node));
        n = prev->next;
        n->node_num = from_node;
        n->next = NULL;
    }
    
    
    while (1)
    { 
        // scan the dest node
        input = scanf(" %s",&c);
        if(DEBUG)printf("%c\n",c);
        if (c <= '9' && c >='0')
        {
            int weight;
            input = scanf(" %d",&weight);
            
            pedge temp_edge = n->edges;
            pnode temp;
            pnode pre = temp;
            if (temp_edge == NULL)
            {
                n->edges = malloc(sizeof(edge));
                if (n->edges == NULL)
                {
                    perror("not enogh space: ");
                    exit(-1);
                }
                bzero(n->edges,sizeof(edge));
                n->edges->weight = weight;
                //Scan to find the end-point
                temp = *head;
                int f = atoi(&c);
                while (temp != NULL)
                {   
                    if (temp->node_num == f)
                    {
                        break;
                    }
                    pre = temp;
                    temp = temp->next;
                }
                if (temp == NULL)
                {
                    temp = malloc(sizeof(node));
                    if (temp == NULL)
                    {
                        perror("not enogh space: ");
                        exit(-1);
                    }
                    bzero(temp,sizeof(node)); 
                    pre->next = temp;
                }
                temp->node_num = f;
                n->edges->endpoint = temp;
                n->edges->next = NULL;

            }
            else{
                // Chain the new edge to the node's list
                while (temp_edge->next != NULL)
                {
                    temp_edge = temp_edge -> next;
                }
                temp_edge->next = malloc(sizeof(edge));
                if (temp_edge->next == NULL)
                {
                    perror("not enogh space: ");
                    exit(-1);
                }
                bzero(temp_edge->next,sizeof(edge));
                //Scan to find the end-point
                temp = *head;
                int f = atoi(&c);
                while (temp != NULL)
                {
                    
                    if (temp->node_num == f)
                    {
                        break;
                    }
                    pre = temp;
                    temp = temp->next;
                }
                if (temp == NULL)
                {
                    temp = malloc(sizeof(node));
                    if (temp == NULL)
                    {
                        perror("not enogh space: ");
                        exit(-1);
                    }
                    bzero(temp,sizeof(node));    
                    pre->next = temp;
                }
                temp->node_num = f;
                temp_edge->next->endpoint = temp;
                temp_edge->next->weight = weight;
                temp_edge->next->next = NULL;
            }   
        }
        else
            return;
    }
}

void delete_node_cmd(pnode head)
{
    //First we need to free the linked list of all the connected edges
    pedge current = (head)->edges;
    pedge next;

    while (current != NULL) {
        next = current->next;
        //free(current->endpoint);
        current->endpoint = NULL;
        free(current);
        current = next;
    }
    // Secondly we need to free the node itself
    free(head);
    head = NULL;
}


int count_nodes(pnode head){
    int counter = 0;
    pnode t = head;
    while (t != NULL)
    {
       counter++;
       t = t->next;
    }
    return counter;
}
/*
Return the index of a node given the head of a graph and the node number
If not found return -1
*/ 
int find_node(pnode head, int node_num) {
    pnode current = head;
    int i = 0;
    while (current != NULL) {
        if (current->node_num == node_num) {
            return i;
        }
        i++;
        current = current->next;
    }
    return -1;
}
/*
Returns a pointer to a node in index of index in the linked list
*/
pnode node_in_index_of(pnode head, int index){
    pnode temp = head;
    for (size_t i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    return temp;
}
/*
Returns the index of the node with the min dist
*/ 
int min_distance_node(int dist[], int visited[], int num_nodes) {
    int min_val = INT_MAX, min_index = -1;

    for (int i = 0; i < num_nodes; i++) {
        // Not visited and has shorter path so far
        if (visited[i] == 0 && dist[i] <= min_val) {
            min_val = dist[i];
            min_index = i;
        }
    }
    return min_index;
}
