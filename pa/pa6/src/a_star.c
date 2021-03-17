#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "util.h"
#include "a_star.h"

/********* GRAPH *********/

/* graph_create: create a graph
 *
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

/* add_edge_h: adds a new neighbor with specified data to next open slot
 *
 * graph: the graph
 * node_num: node number
 * data: the data to add to new neighbor
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
 * neighbors: linked list of neighbor(s)
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

double euclidean_distance(graph_t *graph, int node_num_1, int node_num_2) 
{
    double latitude_1 = graph->nodes[node_num_1]->latitude;
    double longitude_1 = graph->nodes[node_num_1]->longitude;
    double latitude_2 = graph->nodes[node_num_2]->latitude;
    double longitude_2 = graph->nodes[node_num_2]->longitude;

    return sqrt(pow(latitude_1 - latitude_2, 2.0) + pow(longitude_1 - longitude_2, 2.0));
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
    // Priority queue

    // Closed set
}