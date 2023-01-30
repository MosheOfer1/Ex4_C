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

char c;

int tsp_min = INT_MAX;
int flag_way = 0;
// A function to find the shortest path between two nodes
int shortest_path(pnode head, int src, int dest, int num_nodes) {
    int *dist = malloc(num_nodes * sizeof(int));
    int *visited = malloc(num_nodes * sizeof(int));
    if (!dist || !visited)
    {
        perror("not enogh space: ");
        exit(-1);
    }
    
    // Init the required data for dijkstra
    for (int i = 0; i < num_nodes; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }

    int indexOfSrc = find_node(head, src);
    dist[indexOfSrc] = 0;
    

    for (int i = 0; i < num_nodes - 1; i++) {
        int u = min_distance_node(dist, visited, num_nodes);
        visited[u] = 1;

        // current is the pointer to the linked list of the edges of the node with the min dist
        pedge current = (node_in_index_of(head, u)->edges);
        while (current != NULL) {
            int v = find_node(head, current->endpoint->node_num);
            int alt = dist[u] + current->weight;
            if (dist[u] != INT_MAX && alt < dist[v]) {
                dist[v] = dist[u] + current->weight;
            }
            current = current->next;
        }
    }
    int ans = dist[find_node(head,dest)];
    if (ans == INT_MAX)
    {
         free(dist);
        free(visited);
        dist = NULL;
        visited = NULL;
        return -1;
    }
    free(dist);
    free(visited);
    dist = NULL;
    visited = NULL;
    return ans;
}


void TSP_RECURSIVE(int *arr, int l, int r, int k,int n){
     if (l == r)
    {
        int min_distance_for_this_permute = 0;
        int flag = 0;
        for (int i = 0; i < k - 1; i++)
        {
            int way = shortest_path(head,arr[i],arr[i+1],n);
            //printf("%d",arr[i]);
            if(DEBUG)printf("The way from %d to %d is %d\n",arr[i],arr[i+1],way);
            if(way == -1) 
            {
                min_distance_for_this_permute = INT_MAX;
                flag = 1;
                break;
            }
            else {
                min_distance_for_this_permute += way;
            }
        }
        // If the flag rose no way exict in this permute
        // which means that if no flag, there is a way
        if (flag == 0)
        {
            flag_way = 1;
        }
        
        //printf("\n");
        if (min_distance_for_this_permute < tsp_min)
        {
            tsp_min = min_distance_for_this_permute;
        }
        
    }
    else
    {
        for (int i = l; i <= r; i++)
        {
            int temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
            TSP_RECURSIVE(arr, l+1, r, k, n);
            temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
        }
    }

}

void shortsPath_cmd(pnode head)
{
    int from, to;
    input = scanf(" %d %d",&from,&to);
    printf("Dijsktra shortest path: %d \n",shortest_path(head,from, to, count_nodes(head)));
}



void TSP_cmd(pnode head)
{
    int k;
    input = scanf(" %d",&k);
    int n = count_nodes(head);
    int a[k];
    for (size_t i = 0; i < k; i++)
    {
        input = scanf(" %d",&a[i]);
    }
    flag_way = 0;
    TSP_RECURSIVE(a,0,k-1,k,n);
    if(DEBUG)printf("%d\n",flag_way);
    if (flag_way == 0)
    {
        printf("TSP shortest path: -1 \n");
    }
    else
        printf("TSP shortest path: %d \n",tsp_min);
    tsp_min = INT_MAX;
}
