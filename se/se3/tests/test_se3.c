#include <stdio.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "se3.h"

#define ERR_MSG_LEN (1000)

/**************** Exercise 1 ****************/
/* helper_find_min_max: Do the work of testing find_min_max
 *
 * a: array of postitive ints
 * a_len: number of elements (length) of array a
 * min_ptr: pointer to the minimum value in array a (out parameter)
 * max_ptr: poitner to the maximum value in array a (out parameter)
 * expected_min: the expected minimum
 * expected_max: the expected maximum
 * a_string: string representation of a
 * test_name - the test name to be used in error messages.
 */
void helper_find_min_max(int a[], int a_len, int *min_ptr, int *max_ptr,
			             int expected_min, int expected_max, char *a_string, char *test_name)
{
    find_min_max(a, a_len, min_ptr, max_ptr);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Parameters used in failed test: find_min_max(%s, %d, min_ptr, max_ptr)\n"
          "\n     Actual min: %d"
          "\n     Actual max: %d"
          "\n     Expected min: %d"
          "\n     Expected max: %d"
          "\n  The filter to run this specific test is: --filter find_min_max/%s"),
         a_string, a_len, *min_ptr, *max_ptr, expected_min, expected_max, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(*min_ptr, expected_min, " %s", err_msg);
    cr_assert_eq(*max_ptr, expected_max, " %s", err_msg);
}

Test(find_min_max, testA) {
    int a[] = {1};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 1, &min, &max, 1, 1, "{1}", "testA");
}

Test(find_min_max, testB) {
    int a[] = {1, 2};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 2, &min, &max, 1, 2, "{1, 2}", "testB");
}

Test(find_min_max, testC) {
    int a[] = {1, 2, 3, 4, 5};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 5, &min, &max, 1, 5, "{1, 2, 3, 4, 5}", "testC");
}

Test(find_min_max, testD) {
    int a[] = {5, 4, 3, 2, 1};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 5, &min, &max, 1, 5, "{5, 4, 3, 2, 1}", "testD");
}

Test(find_min_max, testE) {
    int a[] = {7, 8, 7};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 3, &min, &max, 7, 8, "{7, 8, 7}", "testE");
}

Test(find_min_max, testF) {
    int a[] = {8, 7, 8};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 3, &min, &max, 7, 8, "{8, 7, 8}", "testE");
}

Test(find_min_max, testG) {
    int a[] = {5, 5, 5, 6, 6, 6, 4, 4, 4};
    int min = INT_MAX;
    int max = INT_MIN;
    helper_find_min_max(a, 9, &min, &max, 4, 6, "{5, 5, 5, 6, 6, 6, 4, 4, 4}", "testE");
}

/**************** Exercise 2 ****************/
/* helper_make_star_string - do the work of testing make_star_string
 *
 * n: number of stars in the string (n >= 0)
 * expected: the expected result
 * test_name: the test name to be used in error messages.
 */

void helper_make_star_string(int n, char *expected, char *test_name)
{
    char* actual = make_star_string(n);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: make_star_string(%d)\n"
	      "\n     Actual: %s"
	      "\n     Expected: %s"
	      "\n  The filter to run this specific test is: --filter make_star_string/%s"),
	     n, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_str_eq(actual, expected, " %s", err_msg);

    free(actual);
}

Test(make_star_string, testA) {
    helper_make_star_string(0, "", "testA");
}

Test(make_star_string, testB) {
    helper_make_star_string(1, "*", "testB");
}

Test(make_star_string, testC) {
    helper_make_star_string(2, "**", "testC");
}

Test(make_star_string, testD) {
    helper_make_star_string(3, "***", "testD");
}

Test(make_star_string, testE) {
    helper_make_star_string(6, "******", "testE");
}

/**************** Exercise 3 ****************/
/* helper_make_histogram: do the work of testing make_histogram
 *
 * a: array of postitive ints
 * a_len: number of elements (length) of array a
 * hist_len_ptr: pointer to the length of histogram array
 * expected: the expected result
 * expected_len: the length of the expected result
 * a_string: string representation of a
 * expected_string: string representation of expected
 * test_name: the name of the tests for error messages
 */
void helper_make_histogram(int a[], int a_len, int *hist_len_ptr, 
                           int expected[], int expected_len, 
                           char *a_string, char *expected_string, char *test_name)
{
    int* actual = make_histogram(a, a_len, hist_len_ptr);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: make_histogram(%s, %d, hist_len_ptr)\n"
	      "\n     Expected: %s"
	      "\n  The filter to run this specific test is: --filter make_histogram/%s"),
	     a_string, a_len, expected_string, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    for(int i = 0; i < expected_len; i++){
        cr_assert_eq(actual[i], expected[i], " %s", err_msg);
    }

    free(actual);
}

Test(make_histogram, testA) {
    int a[] = {1};
    int hist_len = 0;
    int expected[] = {1};
    helper_make_histogram(a, 1, &hist_len, expected, 1, "{1}", "{1}", "testA");
}

Test(make_histogram, testB) {
    int a[] = {1, 2};
    int hist_len = 0;
    int expected[] = {1, 1};
    helper_make_histogram(a, 2, &hist_len, expected, 1, "{1, 2}", "{1, 1}", "testB");
}

Test(make_histogram, testC) {
    int a[] = {1, 1, 1};
    int hist_len = 0;
    int expected[] = {3};
    helper_make_histogram(a, 3, &hist_len, expected, 1, "{1, 1, 1}", "{3}", "testC");
}

Test(make_histogram, testD) {
    int a[] = {3, 3, 4, 4};
    int hist_len = 0;
    int expected[] = {2, 2};
    helper_make_histogram(a, 4, &hist_len, expected, 2, "{3, 3, 4, 4}", "{2, 2}", "testD");
}

Test(make_histogram, testE) {
    int a[] = {5, 6, 7, 8, 9};
    int hist_len = 0;
    int expected[] = {1, 1, 1, 1, 1};
    helper_make_histogram(a, 5, &hist_len, expected, 5, "{5, 6, 7, 8, 9}", "{1, 1, 1, 1, 1}", "testE");
}

Test(make_histogram, testF) {
    int a[] = {5, 6, 7, 8, 9, 8, 7, 6, 5};
    int hist_len = 0;
    int expected[] = {2, 2, 2, 2, 1};
    helper_make_histogram(a, 9, &hist_len, expected, 5, "{5, 6, 7, 8, 9, 8, 7, 6, 5}", "{2, 2, 2, 2, 1}", "testF");
}

Test(make_histogram, testG) {
    int a[] = {6, 9};
    int hist_len = 0;
    int expected[] = {1, 0, 0, 1};
    helper_make_histogram(a, 2, &hist_len, expected, 2, "{6, 9}", "{1, 0, 0, 1}", "testG");
}

/**************** Exercise 4 ****************/
/* helper_make_star_array: do the work of testing make_star_array
 *
 * a: array of nonnegative ints
 * a_len: number of elements (length) of array a
 * expected: the expected result
 * expected_len: the length of the expected result
 * a_string: string representation of a
 * expected_string: string representation of expected
 * test_name: the name of the tests for error messages
 */
void helper_make_star_array(int a[], int a_len, char **expected, int expected_len,
                            char *a_string, char *expected_string, char *test_name)
{
    char** actual = make_star_array(a, a_len);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: make_star_array(%s, %d)\n"
	      "\n     Expected: %s (array of strings)" 
	      "\n  The filter to run this specific test is: --filter make_star_array/%s"),
	     a_string, a_len, expected_string, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    for(int i = 0; i < expected_len; i++){
        cr_assert_str_eq(actual[i], expected[i], " %s", err_msg);
    }

    for(int i = 0; i < expected_len; i++){
        free(actual[i]);
    }
    free(actual);
}

Test(make_star_array, testA) {
    int a[] = {1};
    char** expected = (char**)malloc(sizeof(char*) * 1);
    expected[0] = "*";
    helper_make_star_array(a, 1, expected, 1, "{1}", "{*}", "testA");
    free(expected);
}

Test(make_star_array, testB) {
    int a[] = {1, 1};
    char** expected = (char**)malloc(sizeof(char*) * 2);
    expected[0] = "*";
    expected[1] = "*";
    helper_make_star_array(a, 1, expected, 1, "{1}", "{*, *}", "testB");
    free(expected);
}

Test(make_star_array, testC) {
    int a[] = {1, 2, 3};
    char** expected = (char**)malloc(sizeof(char*) * 3);
    expected[0] = "*";
    expected[1] = "**";
    expected[2] = "***";
    helper_make_star_array(a, 3, expected, 3, "{1, 2, 3}", "{*, **, ***}", "testC");
    free(expected);
}

Test(make_star_array, testD) {
    int a[] = {2, 2, 1, 1};
    char** expected = (char**)malloc(sizeof(char*) * 4);
    expected[0] = "**";
    expected[1] = "**";
    expected[2] = "*";
    expected[3] = "*";

    helper_make_star_array(a, 4, expected, 4, "{2, 2, 1, 1}", "{**, **, *, *}", "testD");
    free(expected);
}

Test(make_star_array, testE) {
    int a[] = {4, 0, 1};
    char** expected = (char**)malloc(sizeof(char*) * 3);
    expected[0] = "****";
    expected[1] = "";
    expected[2] = "*";
    helper_make_star_array(a, 3, expected, 3, "{4, 0, 1}", "{****, , *}", "testE");
    free(expected);
}

/**************** Exercise 5 ****************/
/* helper_make_histogram_visualization: do the work of testing make_histogram_visualization
 *
 * a: array of postitive ints
 * a_len: number of elements (length) of array a
 * hist_len_ptr: pointer to the number of elements (length) of histogram array (out paramter)
 * expected_a: the expected result array
 * expected_his_len: the expected histogram length
 * a_string: string representation of a
 * expected_string: string representation of expected
 * test_name: the name of the tests for error messages
 */
void helper_make_histogram_visualization(int a[], int a_len, int *hist_len_ptr, char** expected, int expected_hist_len,
                                         char *a_string, char *expected_string, char *test_name)
{
    char** actual = make_histogram_visualization(a, a_len, hist_len_ptr);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: make_histogram_visualization(%s, %d, hist_len_ptr)\n"
	      "\n     Expected: %s (array of strings)"
	      "\n  The filter to run this specific test is: --filter make_histogram_visualization/%s"),
	      a_string, a_len, expected_string, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(*hist_len_ptr, expected_hist_len, " %s", err_msg);

    for(int i = 0; i < expected_hist_len; i++){
        cr_assert_str_eq(actual[i], expected[i], " %s", err_msg);
    }
}

Test(make_histogram_visualization, testA) {
    int a[] = {1};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 1);
    expected[0] = "*";
    helper_make_histogram_visualization(a, 1, &hist_len, expected, 1, "{1}", 
                                       "{*}", "testA");
    free(expected);
}

Test(make_histogram_visualization, testB) {
    int a[] = {1, 2};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 2);
    expected[0] = "*";
    expected[1] = "*";
    helper_make_histogram_visualization(a, 2, &hist_len, expected, 2, "{1, 2}", 
                                       "{*, *}", "testB");
    free(expected);
}

Test(make_histogram_visualization, testC) {
    int a[] = {1, 1, 1};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 1);
    expected[0] = "***";
    helper_make_histogram_visualization(a, 3, &hist_len, expected, 1, "{1, 1, 1}", 
                                       "{***}", "testC");
    free(expected);
}

Test(make_histogram_visualization, testD) {
    int a[] = {3, 3, 4, 4};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 2);
    expected[0] = "**";
    expected[1] = "**";
    helper_make_histogram_visualization(a, 4, &hist_len, expected, 2, "{3, 3, 4, 4}", 
                                       "{**, **}", "testD");
    free(expected);
}

Test(make_histogram_visualization, testE) {
    int a[] = {5, 6, 7, 8, 9};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 5);
    expected[0] = "*";
    expected[1] = "*";
    expected[2] = "*";
    expected[3] = "*";
    expected[4] = "*";
    helper_make_histogram_visualization(a, 5, &hist_len, expected, 5, "{5, 6, 7, 8, 9}", 
                                       "{*, *, *, *, *}", "testE");
    free(expected);
}

Test(make_histogram_visualization, testF) {
    int a[] = {5, 6, 7, 8, 9, 8, 7, 6, 5};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 5);
    expected[0] = "**";
    expected[1] = "**";
    expected[2] = "**";
    expected[3] = "**";
    expected[4] = "*";
    helper_make_histogram_visualization(a, 9, &hist_len, expected, 5, "{5, 6, 7, 8, 9, 8, 7, 6, 5}", 
                                       "{**, **, **, **, *}", "testF");
    free(expected);
}

Test(make_histogram_visualization, testG) {
    int a[] = {6, 9};
    int hist_len = 0;
    char** expected = (char**)malloc(sizeof(char*) * 4);
    expected[0] = "*";
    expected[1] = "";
    expected[2] = "";
    expected[3] = "*";
    helper_make_histogram_visualization(a, 2, &hist_len, expected, 4, "{6, 9}", 
                                       "{*, , , *}", "testG");
    free(expected);
}