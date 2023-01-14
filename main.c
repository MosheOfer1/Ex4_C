#include "graph.h"
#include "nodes.h"
#include "algo.h"
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>



char c = ' ';
int main()
{    
    input = 0;
    head = NULL;
    // Have to build the graoh first
    while (c != 'A')
    {
        input = scanf(" %c",&c);
    }
    
    while (1)
    {
        if (input == EOF)
        {
            break;
        }
        if (c == 'A')
        {
            if (head != NULL)
            {
                deleteGraph_cmd(head);
            }
            head = NULL;
            build_graph_cmd(&head);
        }

        if (c == 'B')
        {
            input = scanf(" %d",&from_node);
            // Chack if exict
            // If the node exicts erase all the edges from him
            pnode prev = head;
            pnode temp = prev;
            while (temp != NULL)
            {
                if (temp->node_num == from_node)
                {
                    //First we need to free the linked list of all the connected edges
                    pedge current = temp->edges;
                    pedge next;

                    while (current != NULL) {
                        next = current->next;
                        //free(current->endpoint);
                        free(current);
                        current = next;
                    }
                    temp->edges = NULL;
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            insert_node_cmd(&head);
            if(DEBUG)printGraph_cmd(head);
        }
        if (c == 'D')
        {
            pnode prev = head;
            pnode temp = prev;
            input = scanf(" %d",&from_node);
            while (temp != NULL)
            {
                // Disconnect all edges to this vertex
                pedge erase_edges = temp->edges;
                pedge p_erase_edges = erase_edges;
                while (erase_edges != NULL)
                {
                    if (erase_edges->endpoint->node_num == from_node)
                    {
                        if (p_erase_edges != erase_edges)
                        {
                            p_erase_edges->next = erase_edges->next;
                        }
                        else{
                            temp->edges = erase_edges->next;
                        }
                        free(erase_edges);
                        break;
                    }
                    p_erase_edges = erase_edges;
                    erase_edges = erase_edges->next;
                }
                prev = temp;
                temp = temp->next;
            }
            prev = head;
            temp = prev;
            while (temp != NULL)
            {
                if (temp->node_num == from_node)
                {
                    if (temp == head)
                    {
                        head = temp->next;
                    }
                    else
                        prev->next = temp->next;
                    delete_node_cmd(temp);
                    break;
                }
                prev = temp;
                temp = temp->next;
            }
            if(DEBUG) printGraph_cmd(head);
            input = scanf(" %c",&c);
        }
        if (c == 'S')
        {
            // Aplly Dijkstra on the graph
            shortsPath_cmd(head);
            input = scanf(" %c",&c);

        }
        if (c == 'T')
        {
            
            TSP_cmd(head);
            input = scanf(" %c",&c);

        }
        
    }
    return 0;
}



