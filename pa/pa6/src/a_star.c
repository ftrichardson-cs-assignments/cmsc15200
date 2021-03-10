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
    //  YOUR CODE HERE
    return NULL;
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
    //  YOUR CODE HERE
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
    //  YOUR CODE HERE
    return;
}

/* graph_free: free a graph and its nodes
 *
 * graph: the graph
 */ 
void graph_free(graph_t* graph)
{
    //  YOUR CODE HERE
    return;
}

/********* A* SEARCH *********/

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
    //  YOUR CODE HERE
    return 0;
}