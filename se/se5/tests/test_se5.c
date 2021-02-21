#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "se5.h"

#define ERR_MSG_LEN (1000)

/**************** Exercise 1 ****************/
/* helper_path_adds_to - do the work of testing path_adds_to
 * 
 * t: a pointer to a tree
 * num: the target sum of values of nodes on a path
 * t_string: string representation of the tree
 * expected: expected output of path_adds_to with t and num
 * test_name: the test name to be used in error messages
 */

void helper_path_adds_to(inttree_t *t, int num, char* t_string, bool expected, char *test_name)
{
    bool actual = path_adds_to(t, num);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: path_adds_to(%s, %d)\n"
	      "\n      Actual: %d"
	      "\n      Expected: %d"
	      "\n  The filter to run this specific test is: --filter path_adds_to/%s"),
	      t_string, num, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual, expected, " %s", err_msg);
}

Test(path_adds_to, testA) {
    inttree_t *t = make_tree_node(1, NULL, NULL);
    helper_path_adds_to(t, 1, "(1, NULL, NULL)", true, "testA");
}

Test(path_adds_to, testB) {
    inttree_t *t = make_tree_node(1, NULL, NULL);
    helper_path_adds_to(t, 2, "(1, NULL, NULL)", false, "testB");
}

Test(path_adds_to, testC) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_path_adds_to(t, 3, "(1, (2, NULL, NULL), (3, NULL, NULL))", true, "testC");
}

Test(path_adds_to, testD) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_path_adds_to(t, 4, "(1, (2, NULL, NULL), (3, NULL, NULL))", true, "testD");
}

Test(path_adds_to, testE) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_path_adds_to(t, 1, "(1, (2, NULL, NULL), (3, NULL, NULL))", false, "testE");
}

Test(path_adds_to, testF) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_path_adds_to(t, 5, "(1, (2, NULL, NULL), (3, NULL, NULL))", false, "testF");
}

Test(path_adds_to, testG) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_path_adds_to(t, 8, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", true, "testG");
}

Test(path_adds_to, testH) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_path_adds_to(t, 4, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", false, "testH");
}

Test(path_adds_to, testI) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_path_adds_to(t, 9, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", false, "testI");
}

Test(path_adds_to, testJ) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_path_adds_to(t, 6, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", true, "testJ");
}

Test(path_adds_to, testK) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_path_adds_to(t, 5, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", false, "testK");
}

Test(path_adds_to, testL) {
    inttree_t *t = NULL;
    helper_path_adds_to(t, 1, "NULL", false, "testL");
}

/**************** Exercise 2 ****************/
/* helper_preorder: do the work of testing preorder
 *
 * t: a pointer to a tree
 * num: the value to find
 * t_string: string representation of the tree
 * expected: expected output of preorder with t and num
 * test_name: the test name to be used in error messages
 */
void helper_preorder(inttree_t *t, int num, char* t_string, int expected, char *test_name)
{
    int actual = preorder(t, num);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: preorder(%s, %d)\n"
	      "\n      Actual: %d"
          "\n      Expected: %d"
	      "\n  The filter to run this specific test is: --filter preorder/%s"),
	     t_string, num, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual, expected, " %s", err_msg);
}

Test(preorder, testA) {
    inttree_t *t = make_tree_node(1, NULL, NULL);
    helper_preorder(t, 1, "(1, NULL, NULL)", 1, "testA");
}

Test(preorder, testB) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_preorder(t, 1, "(1, (2, NULL, NULL), (3, NULL, NULL))", 1, "testB");
}

Test(preorder, testC) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_preorder(t, 2, "(1, (2, NULL, NULL), (3, NULL, NULL))", 2, "testC");
}

Test(preorder, testD) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_preorder(t, 3, "(1, (2, NULL, NULL), (3, NULL, NULL))", 3, "testD");
}

Test(preorder, testE) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_preorder(t, 4, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 3, "testE");
}

Test(preorder, testF) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_preorder(t, 5, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 4, "testF");
}

Test(preorder, testG) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_preorder(t, 6, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 6, "testG");
}

Test(preorder, testH) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_preorder(t, 7, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 7, "testH");
}

Test(preorder, testI) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_preorder(t, 2, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 2, "testI");
}

Test(preorder, testJ) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_preorder(t, 3, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 3, "testJ");
}

Test(preorder, testK) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_preorder(t, 4, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 4, "testK");
}

Test(preorder, testL) {
    inttree_t *t = NULL;
    helper_preorder(t, 1, "NULL", 0, "testL");
}

/**************** Exercise 3 ****************/
/* helper_inorder: do the work of testing inorder
 *
 * t: a pointer to a tree
 * num: the value to find
 * t_string: string representation of the tree
 * expected: expected output of inorder with t and num
 * test_name: the test name to be used in error messages
 */
void helper_inorder(inttree_t *t, int num, char* t_string, int expected, char *test_name)
{
    int actual = inorder(t, num);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: inorder(%s, %d)\n"
	      "\n      Actual: %d"
          "\n      Expected: %d"
	      "\n  The filter to run this specific test is: --filter inorder/%s"),
	     t_string, num, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual, expected, " %s", err_msg);
}

Test(inorder, testA) {
    inttree_t *t = make_tree_node(1, NULL, NULL);
    helper_inorder(t, 1, "(1, NULL, NULL)", 1, "testA");
}

Test(inorder, testB) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_inorder(t, 1, "(1, (2, NULL, NULL), (3, NULL, NULL))", 2, "testB");
}

Test(inorder, testC) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_inorder(t, 2, "(1, (2, NULL, NULL), (3, NULL, NULL))", 1, "testC");
}

Test(inorder, testD) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_inorder(t, 3, "(1, (2, NULL, NULL), (3, NULL, NULL))", 3, "testD");
}

Test(inorder, testE) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_inorder(t, 4, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 1, "testE");
}

Test(inorder, testF) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_inorder(t, 5, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 3, "testF");
}

Test(inorder, testG) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_inorder(t, 6, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 5, "testG");
}

Test(inorder, testH) {
    inttree_t *t = make_tree_node(1, make_tree_node(2, make_tree_node(4, NULL, NULL), make_tree_node(5, NULL, NULL)), make_tree_node(3, make_tree_node(6, NULL, NULL), make_tree_node(7, NULL, NULL)));
    helper_inorder(t, 7, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 7, "testH");
}

Test(inorder, testI) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_inorder(t, 2, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 3, "testI");
}

Test(inorder, testJ) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_inorder(t, 3, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 2, "testJ");
}

Test(inorder, testK) {
    inttree_t *t = make_tree_node(1, NULL, make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(4, NULL, NULL)));
    helper_inorder(t, 4, "(1, (2, (4, NULL, NULL), (5, NULL, NULL)), (3, (6, NULL, NULL), (7, NULL, NULL)))", 4, "testK");
}

Test(inorder, testL) {
    inttree_t *t = NULL;
    helper_inorder(t, 1, "NULL", 0, "testL");
}

/**************** Exercise 4 ****************/
/* helper_is_not_bst: do the work of testing is_not_bst
 *
 * t: a pointer to a tree
 * t_string: string representation of the tree
 * expected: expected output of is_not_bst with t
 * test_name: the test name to be used in error messages
 */
void helper_is_not_bst(inttree_t *t, char* t_string, bool expected, char *test_name)
{
    int actual = is_not_bst(t);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: is_not_bst(%s)\n"
	      "\n      Actual: %d"
          "\n      Expected: %d"
	      "\n  The filter to run this specific test is: --filter is_not_bst/%s"),
	     t_string, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual, expected, " %s", err_msg);
}

Test(is_not_bst, testA) {
    inttree_t *t = make_tree_node(2, NULL, NULL);
    helper_is_not_bst(t, "(2, NULL, NULL)", false, "testA");
}

Test(is_not_bst, testB) {
    inttree_t *t = make_tree_node(2, make_tree_node(1, NULL, NULL), NULL);
    helper_is_not_bst(t, "(2, (1, NULL, NULL), NULL)", false, "testB");
}

Test(is_not_bst, testC) {
    inttree_t *t = make_tree_node(2, make_tree_node(3, NULL, NULL), NULL);
    helper_is_not_bst(t, "(2, (3, NULL, NULL), NULL)", true, "testC");
}

Test(is_not_bst, testD) {
    inttree_t *t = make_tree_node(2, NULL, make_tree_node(3, NULL, NULL));
    helper_is_not_bst(t, "(2, NULL, (3, NULL, NULL))", false, "testD");
}

Test(is_not_bst, testE) {
    inttree_t *t = make_tree_node(2, NULL, make_tree_node(1, NULL, NULL));
    helper_is_not_bst(t, "(2, NULL, (1, NULL, NULL))", true, "testE");
}

Test(is_not_bst, testF) {
    inttree_t *t = make_tree_node(2, make_tree_node(1, NULL, NULL), make_tree_node(3, NULL, NULL));
    helper_is_not_bst(t, "(2, (1, NULL, NULL), (3, NULL, NULL))", false, "testF");
}

Test(is_not_bst, testG) {
    inttree_t *t = make_tree_node(2, make_tree_node(3, NULL, NULL), make_tree_node(1, NULL, NULL));
    helper_is_not_bst(t, "(2, (3, NULL, NULL), (1, NULL, NULL))", true, "testG");
}

Test(is_not_bst, testH) {
    inttree_t *t = make_tree_node(5, make_tree_node(3, make_tree_node(1, NULL, NULL), make_tree_node(4, NULL, NULL)), make_tree_node(7, NULL, NULL));
    helper_is_not_bst(t, "(5, (3, (1, NULL, NULL), (4, NULL, NULL)), (7, NULL, NULL))", false, "testH");
}

Test(is_not_bst, testI) {
    inttree_t *t = make_tree_node(5, make_tree_node(3, make_tree_node(2, NULL, NULL), make_tree_node(1, NULL, NULL)), make_tree_node(7, NULL, NULL));
    helper_is_not_bst(t, "(5, (3, (2, NULL, NULL), (1, NULL, NULL)), (7, NULL, NULL))", true, "testI");
}

Test(is_not_bst, testJ) {
    inttree_t *t = make_tree_node(5, make_tree_node(3, NULL, NULL), make_tree_node(7, make_tree_node(6, NULL, NULL), make_tree_node(8, NULL, NULL)));
    helper_is_not_bst(t, "(5, (3, NULL, NULL), (7, (6, NULL, NULL), (8, NULL, NULL)))", false, "testJ");
}

Test(is_not_bst, testK) {
    inttree_t *t = make_tree_node(5, make_tree_node(3, NULL, NULL), make_tree_node(7, make_tree_node(4, NULL, NULL), make_tree_node(8, NULL, NULL)));
    helper_is_not_bst(t, "(5, (3, NULL, NULL), (7, (4, NULL, NULL), (8, NULL, NULL)))", true, "testK");
}

Test(is_not_bst, testL) {
    inttree_t *t = NULL;
    helper_is_not_bst(t, "NULL", false, "testL");
}