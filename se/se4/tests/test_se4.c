#include <stdio.h>
#include <limits.h>
#include <criterion/criterion.h>
#include "se4.h"

#define ERR_MSG_LEN (1000)

/**************** Exercise 1 ****************/
/* helper_find_amount_of_denomination: Do the work of testing find_amount_of_denomination
 *
 * cents: total amount of cents
 * denomination: value of a coin in cents
 * num_denomination_ptr: the number of coins whose value is less than or equal 
 *     to cents (out parameter)
 * expected_total_value: the expected output
 * expected_num_denomination: the expected number of coins
 * test_name - the test name to be used in error messages.
 */
void helper_find_amount_of_denomination(int cents, int denomination, int *num_denomination_ptr,
			             int expected_total_value, int expected_num_denomination, char *test_name)
{
    int total_value = find_amount_of_denomination(cents, denomination, num_denomination_ptr);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Parameters used in failed test: find_amount_of_denomination(%d, %d, num_denomination_ptr)\n"
          "\n     Total value:"
          "\n         Actual: %d"
          "\n         Expected: %d"
          "\n     Number of coins:"
          "\n         Actual: %d"
          "\n         Expected: %d"
          "\n  The filter to run this specific test is: --filter find_amount_of_denomination/%s"),
         cents, denomination, total_value, expected_total_value, *num_denomination_ptr,  
         expected_num_denomination, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(total_value, expected_total_value, " %s", err_msg);
    cr_assert_eq(*num_denomination_ptr, expected_num_denomination, " %s", err_msg);
}

Test(find_amount_of_denomination, testA) {
    int num_coins = 0;
    helper_find_amount_of_denomination(25, 25, &num_coins, 25, 1, "testA");
}

Test(find_amount_of_denomination, testB) {
    int num_coins = 0;
    helper_find_amount_of_denomination(27, 25, &num_coins, 25, 1, "testB");
}

Test(find_amount_of_denomination, testC) {
    int num_coins = 0;
    helper_find_amount_of_denomination(102, 25, &num_coins, 100, 4, "testC");
}

Test(find_amount_of_denomination, testD) {
    int num_coins = 0;
    helper_find_amount_of_denomination(27, 10, &num_coins, 20, 2, "testD");
}

Test(find_amount_of_denomination, testE) {
    int num_coins = 0;
    helper_find_amount_of_denomination(102, 10, &num_coins, 100, 10, "testE");
}

Test(find_amount_of_denomination, testF) {
    int num_coins = 0;
    helper_find_amount_of_denomination(27, 5, &num_coins, 25, 5, "testF");
}

Test(find_amount_of_denomination, testG) {
    int num_coins = 0;
    helper_find_amount_of_denomination(102, 5, &num_coins, 100, 20, "testG");
}

Test(find_amount_of_denomination, testH) {
    int num_coins = 0;
    helper_find_amount_of_denomination(4, 1, &num_coins, 4, 4, "testH");
}

Test(find_amount_of_denomination, testI) {
    int num_coins = 0;
    helper_find_amount_of_denomination(102, 1, &num_coins, 102, 102, "testI");
}

/**************** Exercise 1 ****************/
/* helper_make_change - do the work of testing make_change
 *
 * cents: total amount of cents
 * expected_quarters: the expected number of quarters
 * expected_dimes: the expected number of dimes
 * expected_nickels: the expected number of nickels
 * expected_pennies: the expected number of pennies
 * test_name: the test name to be used in error messages.
 */

void helper_make_change(int cents, int expected_quarters, int expected_dimes, 
                        int expected_nickels, int expected_pennies, char *test_name)
{
    struct coins actual = make_change(cents);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: make_change(%d)\n"
          "\n     Quarters:"
	      "\n         Actual: %d"
	      "\n         Expected: %d"
          "\n     Dimes:"
          "\n         Actual: %d"
	      "\n         Expected: %d"
          "\n     Nickels:"
          "\n         Actual: %d"
	      "\n         Expected: %d"
          "\n     Pennies:"
          "\n         Actual: %d"
	      "\n         Expected: %d"
	      "\n  The filter to run this specific test is: --filter make_change/%s"),
	      cents, actual.quarters, expected_quarters, actual.dimes, expected_dimes,
          actual.nickels, expected_nickels, actual.pennies, expected_pennies, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual.quarters, expected_quarters, " %s", err_msg);
    cr_assert_eq(actual.dimes, expected_dimes, " %s", err_msg);
    cr_assert_eq(actual.nickels, expected_nickels, " %s", err_msg);
    cr_assert_eq(actual.pennies, expected_pennies, " %s", err_msg);
}

Test(make_change, testA) {
    helper_make_change(100, 4, 0, 0, 0, "testA");
}

Test(make_change, testB) {
    helper_make_change(104, 4, 0, 0, 4, "testB");
}

Test(make_change, testC) {
    helper_make_change(16, 0, 1, 1, 1, "testC");
}

Test(make_change, testD) {
    helper_make_change(116, 4, 1, 1, 1, "testD");
}

Test(make_change, testE) {
    helper_make_change(7, 0, 0, 1, 2, "testE");
}

/**************** Exercise 2 ****************/
/* helper_repeat_string/array: do the work of testing repeat
 *
 * input: the input tagged_array
 * expected: the expected tagged_array
 * tag: string representation of the input tag
 * test_name: the name of the tests for error messages
 */
void helper_repeat_string(struct tagged_array input, 
                          struct tagged_array expected, char* tag, char *test_name)
{
    struct tagged_array* actual = repeat(input);
    char err_msg[ERR_MSG_LEN];

    char* actual_tag = actual->tag ? "INT_ARRAY" : "STRING";

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: repeat(t_arr)\n"
          "\n  t_arr is the tagged_array with fields:\n"
          "\n      t_arr.tag: %s\n"
          "\n      t_arr.arr_len: %d\n"
          "\n      t_arr.data.s: %s\n"
          "\n  Actual tagged_array: \n"
          "\n      tag: %s\n"
          "\n      arr_len: %d\n"
          "\n      data.s: %s\n"
	      "\n  Expected tagged_array: \n"
          "\n      tag: %s\n"
          "\n      arr_len: %d\n"
          "\n      data.s: %s\n"
	      "\n  The filter to run this specific test is: --filter repeat/%s"),
	     tag, input.arr_len, input.data.s, actual_tag, actual->arr_len, actual->data.s,
         tag, expected.arr_len, expected.data.s, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual->tag, expected.tag, " %s", err_msg); // check tag
    cr_assert_eq(actual->arr_len, expected.arr_len, " %s", err_msg); // check arr_len
    cr_assert_str_eq(actual->data.s, expected.data.s, " %s", err_msg); // check data

    free(actual);
}

void helper_repeat_array(struct tagged_array input, struct tagged_array expected, 
                         char* tag, char* input_data, char* expected_data, char *test_name)
{
    struct tagged_array* actual = repeat(input);
    char err_msg[ERR_MSG_LEN];

    char* actual_tag = actual->tag ? "INT_ARRAY" : "STRING";

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: repeat(t_arr)\n"
          "\n  t_arr is the tagged_array with fields:\n"
          "\n      t_arr.tag: %s\n"
          "\n      t_arr.arr_len: %d\n"
          "\n      t_arr.data.a: %s\n"
          "\n  Actual tagged_array: \n"
          "\n      tag: %s\n"
          "\n      arr_len: %d\n"
	      "\n  Expected tagged_array: \n"
          "\n      tag: %s\n"
          "\n      arr_len: %d\n"
          "\n      data.a: %s\n"
	      "\n  The filter to run this specific test is: --filter repeat/%s"),
	     tag, input.arr_len, input_data, actual_tag, actual->arr_len,
         tag, expected.arr_len, expected_data, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual->tag, expected.tag, " %s", err_msg); // check tag
    cr_assert_eq(actual->arr_len, expected.arr_len, " %s", err_msg); // check arr_len
    for(int i = 0; i < expected.arr_len; i++){
        cr_assert_eq(actual->data.a[i], expected.data.a[i], " %s", err_msg); // check data
    }

    free(actual);
}

Test(repeat, testA) {
    struct tagged_array input;
    input.tag = STRING;
    input.arr_len = 1;
    input.data.s = "a";

    struct tagged_array expected;
    expected.tag = STRING;
    expected.arr_len = 2;
    expected.data.s = "aa";

    helper_repeat_string(input, expected, "STRING", "testA");
}

Test(repeat, testB) {
    struct tagged_array input;
    input.tag = STRING;
    input.arr_len = 2;
    input.data.s = "aa";

    struct tagged_array expected;
    expected.tag = STRING;
    expected.arr_len = 4;
    expected.data.s = "aaaa";

    helper_repeat_string(input, expected, "STRING", "testB");
}

Test(repeat, testC) {
    struct tagged_array input;
    input.tag = STRING;
    input.arr_len = 2;
    input.data.s = "ab";

    struct tagged_array expected;
    expected.tag = STRING;
    expected.arr_len = 4;
    expected.data.s = "abab";

    helper_repeat_string(input, expected, "STRING", "testC");
}

Test(repeat, testD) {
    struct tagged_array input;
    input.tag = STRING;
    input.arr_len = 3;
    input.data.s = "abc";

    struct tagged_array expected;
    expected.tag = STRING;
    expected.arr_len = 6;
    expected.data.s = "abcabc";

    helper_repeat_string(input, expected, "STRING", "testD");
}

Test(repeat, testE) {
    struct tagged_array input;
    input.tag = INT_ARRAY;
    input.arr_len = 1;
    int a[] = {1};
    input.data.a = a;

    struct tagged_array expected;
    expected.tag = INT_ARRAY;
    expected.arr_len = 2;
    int expected_a[] = {1, 1};
    expected.data.a = expected_a;

    helper_repeat_array(input, expected, "INT_ARRAY", "{1}", "{1, 1}", "testE");
}

Test(repeat, testF) {
    struct tagged_array input;
    input.tag = INT_ARRAY;
    input.arr_len = 2;
    int a[] = {1, 1};
    input.data.a = a;

    struct tagged_array expected;
    expected.tag = INT_ARRAY;
    expected.arr_len = 4;
    int expected_a[] = {1, 1, 1, 1};
    expected.data.a = expected_a;

    helper_repeat_array(input, expected, "INT_ARRAY", "{1, 1}", "{1, 1, 1, 1}", "testF");
}

Test(repeat, testG) {
    struct tagged_array input;
    input.tag = INT_ARRAY;
    input.arr_len = 2;
    int a[] = {1, 2};
    input.data.a = a;

    struct tagged_array expected;
    expected.tag = INT_ARRAY;
    expected.arr_len = 4;
    int expected_a[] = {1, 2, 1, 2};
    expected.data.a = expected_a;

    helper_repeat_array(input, expected, "INT_ARRAY", "{1, 2, 3}", "{1, 2, 1, 2}", "testG");
}

Test(repeat, testH) {
    struct tagged_array input;
    input.tag = INT_ARRAY;
    input.arr_len = 3;
    int a[] = {1, 2, 3};
    input.data.a = a;

    struct tagged_array expected;
    expected.tag = INT_ARRAY;
    expected.arr_len = 6;
    int expected_a[] = {1, 2, 3, 1, 2, 3};
    expected.data.a = expected_a;

    helper_repeat_array(input, expected, "INT_ARRAY", "{1, 2, 3}", "{1, 2, 3, 1, 2, 3}", "testH");
}

/**************** Exercise 3 ****************/
/* helper_create_negative: do the work of testing create_negative
 *
 * input: input image
 * len: length of one side of image
 * expected: the expected result
 * input_string: string representation of input
 * expected_string: string representation of expected
 * test_name: the name of the tests for error messages
 */
void helper_create_negative(bool** input, int len, bool** expected, 
                            char *input_string, char *expected_string, char *test_name)
{
    bool** actual = create_negative(input, len);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: create_negative(%s, %d)\n"
	      "\n     Expected: %s " 
	      "\n  The filter to run this specific test is: --filter create_negative/%s"),
	     input_string, len, expected_string, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            cr_assert_eq(actual[i][j], expected[i][j], " %s", err_msg);
        }
    }

    for(int i = 0; i < len; i++){
        free(actual[i]);
    }
    free(actual);
}

Test(create_negative, testA) {
    int len = 2;
    bool** input = (bool**)malloc(sizeof(bool*)*len);
    bool** expected = (bool**)malloc(sizeof(bool*)*len);

    for(int i = 0; i < len; i++){
        input[i] = (bool*)malloc(sizeof(bool)*len);
        expected[i] = (bool*)malloc(sizeof(bool)*len);
    }
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            input[i][j] = 0;
            expected[i][j] = 1;
        }
    }
    helper_create_negative(input, 2, expected, "{{0, 0}, {0, 0}}", "{{1, 1}, {1, 1}}", "testA");

    for(int i = 0; i < len; i++){
        free(input[i]);
        free(expected[i]);
    }
    free(input);
    free(expected);
}

Test(create_negative, testB) {
    int len = 2;
    bool** input = (bool**)malloc(sizeof(bool*)*len);
    bool** expected = (bool**)malloc(sizeof(bool*)*len);

    for(int i = 0; i < len; i++){
        input[i] = (bool*)malloc(sizeof(bool)*len);
        expected[i] = (bool*)malloc(sizeof(bool)*len);
    }
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            input[i][j] = 1;
            expected[i][j] = 0;
        }
    }
    helper_create_negative(input, 2, expected, "{{1, 1}, {1, 1}}", "{{0, 0}, {0, 0}}", "testB");

    for(int i = 0; i < len; i++){
        free(input[i]);
        free(expected[i]);
    }
    free(input);
    free(expected);
}

Test(create_negative, testC) {
    int len = 2;
    bool** input = (bool**)malloc(sizeof(bool*)*len);
    bool** expected = (bool**)malloc(sizeof(bool*)*len);

    for(int i = 0; i < len; i++){
        input[i] = (bool*)malloc(sizeof(bool)*len);
        expected[i] = (bool*)malloc(sizeof(bool)*len);
    }
    input[0][0] = 0;
    expected[0][0] = 1;
    input[0][1] = 1;
    expected[0][1] = 0;
    input[1][0] = 1;
    expected[1][0] = 0;
    input[1][1] = 0;
    expected[1][1] = 1;

    helper_create_negative(input, 2, expected, "{{0, 1}, {1, 0}}", "{{1, 0}, {0, 1}}", "testC");

    for(int i = 0; i < len; i++){
        free(input[i]);
        free(expected[i]);
    }
    free(input);
    free(expected);
}

Test(create_negative, testD) {
    int len = 2;
    bool** input = (bool**)malloc(sizeof(bool*)*len);
    bool** expected = (bool**)malloc(sizeof(bool*)*len);

    for(int i = 0; i < len; i++){
        input[i] = (bool*)malloc(sizeof(bool)*len);
        expected[i] = (bool*)malloc(sizeof(bool)*len);
    }
    input[0][0] = 1;
    expected[0][0] = 0;
    input[0][1] = 0;
    expected[0][1] = 1;
    input[1][0] = 0;
    expected[1][0] = 1;
    input[1][1] = 1;
    expected[1][1] = 0;

    helper_create_negative(input, 2, expected, "{{1, 0}, {0, 1}}", "{{0, 1}, {1, 0}}", "testD");

    for(int i = 0; i < len; i++){
        free(input[i]);
        free(expected[i]);
    }
    free(input);
    free(expected);
}

Test(create_negative, testE) {
    int len = 3;
    bool** input = (bool**)malloc(sizeof(bool*)*len);
    bool** expected = (bool**)malloc(sizeof(bool*)*len);

    for(int i = 0; i < len; i++){
        input[i] = (bool*)malloc(sizeof(bool)*len);
        expected[i] = (bool*)malloc(sizeof(bool)*len);
    }
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            input[i][j] = 0;
            expected[i][j] = 1;
        }
    }

    input[0][0] = 1;
    expected[0][0] = 0;
    input[0][1] = 1;
    expected[0][1] = 0;

    helper_create_negative(input, 2, expected, "{{1, 1, 0}, {0, 0, 0}, {0, 0, 0}}", 
                           "{{0, 0, 1}, {1, 1, 1}, {1, 1, 1}}", "testE");

    for(int i = 0; i < len; i++){
        free(input[i]);
        free(expected[i]);
    }
    free(input);
    free(expected);
}