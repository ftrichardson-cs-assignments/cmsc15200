#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "se5.h"

int main()
{
    inttree_t *t1 = make_tree_node(1, NULL, NULL);
    inttree_t *t2 = make_tree_node(2, NULL, NULL);
    inttree_t *t3 = make_tree_node(3, t1, t2);
    inttree_t *t4 = make_tree_node(4, NULL, NULL);
    inttree_t *t5 = make_tree_node(5, t3, t4);

    int path = preorder(t5, 2);
    printf("%d\n", path);
}
