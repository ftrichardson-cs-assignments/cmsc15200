#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "util.h"
#include "a_star.h"



int main()
{
    graph_t *g = graph_create(9);
    node_create(g, 0, 'A', 0, 0);
    node_create(g, 1, 'B', 1, 0);
    node_create(g, 2, 'C', 2, 0);
    node_create(g, 3, 'D', 3, 0);
    node_create(g, 4, 'E', 3, 1);
    node_create(g, 5, 'F', 3, 2);
    node_create(g, 6, 'G', 2, 2);
    node_create(g, 7, 'H', 1, 2);
    node_create(g, 8, 'I', 0, 2);
    add_edge(g, 0, 1);
    add_edge(g, 0, 2);
    add_edge(g, 0, 3);
    add_edge(g, 3, 4);
    add_edge(g, 4, 5);
    add_edge(g, 5, 6);
    add_edge(g, 6, 7);
    add_edge(g, 7, 8);
    graph_free(g);
}