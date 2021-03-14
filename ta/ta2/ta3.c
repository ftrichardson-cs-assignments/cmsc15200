#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct lmr_node lmr_t;

struct lmr_node {
    lmr_t *left;
    lmr_t *middle;
    lmr_t *right;
};


/* mk_lmr_node: create an LMR node                                                                                              
 *                                                                                                                              
 * l: left subtree                                                                                                              
 * m: middle subtree                                                                                                            
 * r: right subtree                                                                                                             
 *                                                                                                                              
 * Returns: new LMR node                                                                                                        
 */
lmr_t *mk_lmr_node(lmr_t *l, lmr_t *m, lmr_t *r)
{
    lmr_t *node = (lmr_t *)malloc(sizeof(lmr_t));
    node->left = l;
    node->middle = m;
    node->right = r;
    return node;
};


/* mk_sample: construct the sample LMR tree */
lmr_t *mk_sample() {
    int N = 14;
    lmr_t *nodes[N];

    // make all the nodes be leaves to start                                                                                      
    for (int i = 0; i < N; i++) {
        nodes[i] = mk_lmr_node(NULL, NULL, NULL);
    }

    // treating the array in level order                                                                                          
    // add links                                                                                                                  
    nodes[0]->left = nodes[1];
    nodes[0]->middle = nodes[2];
    nodes[0]->right = nodes[3];

    // Level 1                                                                                                                    
    // labelled w/ 3 in the figure                                                                                                
    nodes[1]->left = nodes[4];
    nodes[1]->middle = nodes[5];
    nodes[2]->left = nodes[6];
    nodes[3]->right = nodes[7];

    // Level 2                                                                                                                    
    // labelled w/ 4 in the figure                                                                                                
    nodes[4]->left = nodes[8];
    nodes[4]->middle = nodes[9];
    nodes[4]->right = nodes[10];

    // node[5] is a leaf;                                                                                                         

    nodes[6]->left = nodes[11];
    nodes[6]->middle = nodes[12];
    nodes[6]->right = nodes[13];

    // nodes[7]-nodes[13] are all leaves.
    // node[7] is the node labelled 2                                                                                             
    // node[13] is the node labelled 1                                                                                            

    // return a pointer to the root.                                                                                              
    return nodes[0];
}

bool is_leaf_node(lmr_t* tree) 
{
	return tree->right == NULL && tree->left == NULL && tree->middle == NULL;
}

/* traverse_LMR: traverses an LMR tree based on 
 *   a LMR string                                                                                 
 *                                                                                                                                            
 * tree: an LMR tree                                                                                                                          
 * str: an LMR string                                                                                                                         
 * leaves_visited_ptr: an OUT parameter used to 
 *   return the number of leaves visited in the                                                                       
 *   in the traversal to the caller                                                                                                       
 *                                                                                                                                            
 * Returns true if the traversal ends at a leaf
 *   and false otherwise.                                                                          
 */
bool traverse_LMR(lmr_t *tree, char *str, int *leaves_visited_ptr) 
{
	*leaves_visited_ptr = 0;
	int str_len = strlen(str);

	lmr_t* root = tree;

	for (int i = 0; i < str_len; i++) 
	{
		if (str[i] == 'L') 
		{
			if (tree->left != NULL) 
			{
				tree = tree->left;

			} else 
			{
				return false;
			}
		}

		if (str[i] == 'M') 
		{
			if (tree->middle != NULL) 
			{
				tree = tree->middle;

			} else 
			{
				return false;
			}
		}

		if (str[i] == 'R') 
		{
			if (tree->right != NULL) 
			{
				tree = tree->right;

			} else 
			{
				return false;
			}
		}

		if (is_leaf_node(tree) && i == str_len - 1) 
		{
			return true;

		} else 
		{
			tree = root;
		}

		*leaves_visited_ptr += 1;
	}
	return true;
}

int main()
{
	lmr_t* sample = mk_sample();
	int number_traversals;
	bool traverse = traverse_LMR(sample, "LL", &number_traversals);
	printf("%d\n", traverse);
	printf("%d\n", number_traversals);
}
