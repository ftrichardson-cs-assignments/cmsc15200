#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "util.h"
#include "a_star.h"

/********* GRAPH *********/

/* graph_create: create a graph
 
 * Returns: a graph
 */ 
graph_t *graph_create(int num_nodes)
{
    graph_t* empty_graph = (graph_t*)malloc(sizeof(graph_t));
    if (empty_graph == NULL) 
    {
        fprintf(stderr, "graph_create: malloc failure\n");
        exit(1);
    }

    empty_graph->num_nodes = num_nodes;
    empty_graph->nodes = (node_t**)malloc(num_nodes * sizeof(node_t*));
    if (empty_graph->nodes == NULL) 
    {
        fprintf(stderr, "graph_create: malloc failure\n");
        exit(1);
    }

    for (int n = 0; n < num_nodes; n++) 
    {
        empty_graph->nodes[n] = NULL;
    }

    return empty_graph;
}

/* node_create: create a graph node
 *
 * graph: the graph
 * node_num: node number
 * city_name: the city
 * latitude: city latitude
 * longitude: city longitude
 * 
 */ 
void node_create(graph_t *graph, int node_num, char *city_name, 
                 double latitude, double longitude)
{    
    graph->nodes[node_num] = (node_t*)malloc(sizeof(node_t));
    if (graph->nodes[node_num] == NULL) 
    {
        fprintf(stderr, "node_create: malloc failure\n");
        exit(1);
    }

    // City
    graph->nodes[node_num]->node_num = node_num;
    graph->nodes[node_num]->city_name = city_name;
    graph->nodes[node_num]->latitude = latitude;
    graph->nodes[node_num]->longitude = longitude;

    // Neighbors
    graph->nodes[node_num]->neighbors = NULL;

    // A* fields
    graph->nodes[node_num]->parent = NULL;
    graph->nodes[node_num]->f_cost = 0;
    graph->nodes[node_num]->g_cost = 0;
    graph->nodes[node_num]->h_cost = 0;
}

/* add_edge_h: adds new neighbor with specified data to end of neighbors
 *
 * graph: the graph
 * node_num: node number
 * data: num of new neighbor
 */ 
void add_edge_h(graph_t *graph, int node_num, int data) 
{
    intlist_t* new_neighbor = (intlist_t*)malloc(sizeof(intlist_t));
    if (new_neighbor == NULL)
    {
        fprintf(stderr, "add_edge_h: malloc failure\n");
        exit(1);
    }

    new_neighbor->num = data;
    new_neighbor->next = NULL;

    // Check if neighbors empty
    if (graph->nodes[node_num]->neighbors == NULL) 
    {
        graph->nodes[node_num]->neighbors = new_neighbor;
        return;
    }

    intlist_t* neighbor = graph->nodes[node_num]->neighbors;
        
    while (neighbor->next != NULL) 
    {
        neighbor = neighbor->next;
    }

    neighbor->next = new_neighbor;
    return;
}

/* add_edge: add an edge between two nodes
 *
 * graph: the graph
 * node_num1: the first node
 * node_num2: the second node
 * 
 */ 
void add_edge(graph_t* graph, int node_num1, int node_num2)
{
    add_edge_h(graph, node_num1, node_num2);
    add_edge_h(graph, node_num2, node_num1);
}

/********* FREE FUNCTIONS *********/

/* neighbors_free: frees node's neighbor(s)
 *
 * neighbors: linked list containing neighbor(s)
 */ 
void neighbors_free(intlist_t* neighbors) 
{
    intlist_t* tmp;
    
    while (neighbors != NULL) 
    {
        tmp = neighbors;
        neighbors = neighbors->next;
        free(tmp);
    }
}

/* graph_free: free a graph and its nodes
 *
 * graph: the graph
 */ 
void graph_free(graph_t *graph)
{
    for (int i = 0; i < graph->num_nodes; i++)
    {
        if (graph->nodes[i] != NULL)
        {
            neighbors_free(graph->nodes[i]->neighbors);
            free(graph->nodes[i]);
        }
    }
    free(graph->nodes);
    free(graph);
}

/********* A* SEARCH *********/

/* euclidean_distance: calculates euclidean distance between two nodes
 * 
 * graph: the graph
 * node_num1: the first node
 * node_num2: the second node
 *
 * Returns: euclidean distance
 */
double euclidean_distance(graph_t *graph, int node_num1, int node_num2) 
{
    double latitude1 = graph->nodes[node_num1]->latitude;
    double longitude1 = graph->nodes[node_num1]->longitude;
    double latitude2 = graph->nodes[node_num2]->latitude;
    double longitude2 = graph->nodes[node_num2]->longitude;

    return sqrt(pow(latitude1 - latitude2, 2.0) + pow(longitude1 - longitude2, 2.0));
}

/* calculate_g_cost: calculates g_cost
 *
 * graph: the graph
 * start_node_num: the starting node number
 * node_num: node number
 *
 * Returns: g_cost value
 */
double calculate_g_cost(graph_t* graph, int parent_num, int node_num) 
{
    double parent_to_node_cost = euclidean_distance(graph, parent_num, node_num);

    return graph->nodes[parent_num]->g_cost + parent_to_node_cost;
}

/* set parent: sets parent field of node
 *
 * graph: the graph
 * node_num_parent: the parent node number
 * node_num_child: the child node number
 */
void set_parent(graph_t *graph, int node_num_parent, int node_num_child) 
{
    graph->nodes[node_num_child]->parent = graph->nodes[node_num_parent];
}

/* set_path_costs: sets h_cost, g_cost and f_cost of node
 * 
 * graph: the graph
 * node_num: node for which to set path costs 
 * h_cost: the h_cost
 * g_cost: the g_cost
 * f_cost: the f_cost
 */
void set_path_costs(graph_t* graph, int node_num, double h_cost, 
                    double g_cost, double f_cost) 
{
    graph->nodes[node_num]->h_cost = h_cost;
    graph->nodes[node_num]->g_cost = g_cost;
    graph->nodes[node_num]->f_cost = f_cost;
}

/* a_star: performs A* search
 *
 * graph: the graph
 * start_node_num: the staring node number
 * end_node_num: the ending node number
 * 
 * Returns: the distance of the path between the start node and end node
 */ 
double a_star(graph_t *graph, int start_node_num, int end_node_num)
{
    queue_t* open_set = queue_create();
    set_t* closed_set = set_create();

    // Set start node path costs
    double h_cost = euclidean_distance(graph, start_node_num, end_node_num);
    double g_cost = 0;
    double f_cost = g_cost + h_cost;
    set_path_costs(graph, start_node_num, h_cost, g_cost, f_cost);

    // Add to open set
    queue_add(open_set, start_node_num, f_cost);

    // Open set
    while (!queue_is_empty(open_set))
    {
        int current_node = queue_remove(open_set);

        // Break if current_node is end node
        if (current_node == end_node_num) 
        {
            break;
        }

        intlist_t* current_neighbor = graph->nodes[current_node]->neighbors;

        while (current_neighbor != NULL)
        {
            int node_num = current_neighbor->num;

            // Check if parent field NULL
            if (graph->nodes[node_num]->parent == NULL)
            {
                set_parent(graph, current_node, node_num);
            }

            double h_cost = euclidean_distance(graph, node_num, end_node_num);
            double g_cost = calculate_g_cost(graph, current_node, node_num);
            double f_cost = h_cost + g_cost;

            if (set_query(closed_set, node_num) || (queue_query(open_set, 
                node_num) && graph->nodes[node_num]->f_cost < f_cost))
            {
                current_neighbor = current_neighbor->next;
                continue;
            }
            
            set_path_costs(graph, node_num, h_cost, g_cost, f_cost);
            set_parent(graph, current_node, node_num);
 
            if (queue_query(open_set, node_num)) 
            {
                queue_change_priority(open_set, node_num, f_cost);

            } else 
            {
                queue_add(open_set, node_num, f_cost);
            }

            current_neighbor = current_neighbor->next;
        }
        set_add(closed_set, current_node);
    }

    queue_free(open_set);
    set_free(closed_set);

    // No path
    if (graph->nodes[end_node_num]->f_cost == 0)
    {
        return -1;
    }

    return graph->nodes[end_node_num]->f_cost;
}