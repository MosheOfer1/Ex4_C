#ifndef NODE_
#define NODE_

void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode head);
int find_node(pnode head, int node_num);
int count_nodes(pnode head);
pnode node_in_index_of(pnode head, int index);
int min_distance_node(int dist[], int visited[], int num_nodes);

#endif
