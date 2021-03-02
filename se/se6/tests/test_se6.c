#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include "se6.h"

#define ERR_MSG_LEN (1000)
htable_t *table1()
{
    htable_t *ht = (htable_t*)malloc(sizeof(htable_t));
    ht->size = 4;
    ht->table = (char **)malloc(sizeof(char*) * ht->size);

    ht->table[0] = "d";
    ht->table[1] = "a";
    ht->table[2] = "b";
    ht->table[3] = "c";

    return ht;
}

char *table1_s()
{
    return "      ht.size = 4\n      ht.table[0] = 'd'\n      ht.table[1] = 'a'\n      ht.table[2] = 'b'\n      ht.table[3] = 'c'\n";
}

htable_t *table2()
{
    htable_t *ht = (htable_t*)malloc(sizeof(htable_t));
    ht->size = 4;
    ht->table = (char **)malloc(sizeof(char*) * ht->size);

    for(int i = 0; i < ht->size; i++) {
        ht->table[i] = NULL;
    }

    return ht;
}

char *table2_s()
{
    return "      ht.size = 4\n      ht.table[0] = NULL\n      ht.table[1] = NULL\n      ht.table[2] = NULL\n      ht.table[3] = NULL\n";
}

htable_t *table3()
{
    htable_t *ht = (htable_t*)malloc(sizeof(htable_t));
    ht->size = 4;
    ht->table = (char **)malloc(sizeof(char*) * ht->size);

    ht->table[0] = "d";
    ht->table[1] = NULL;
    ht->table[2] = NULL;
    ht->table[3] = "c";

    return ht;
}

char *table3_s()
{
    return "      ht.size = 4\n      ht.table[0] = 'd'\n      ht.table[1] = NULL\n      ht.table[2] = NULL\n      ht.table[3] = 'c'\n";
}

htable_t *table4()
{
    htable_t *ht = (htable_t*)malloc(sizeof(htable_t));
    ht->size = 4;
    ht->table = (char **)malloc(sizeof(char*) * ht->size);

    ht->table[0] = "d";
    ht->table[1] = "e";
    ht->table[2] = "b";
    ht->table[3] = "a";

    return ht;
}

char *table4_s()
{
    return "      ht.size = 4\n      ht.table[0] = 'd'\n      ht.table[1] = 'e'\n      ht.table[2] = 'b'\n      ht.table[3] = 'a'\n";
}

htable_t *table5()
{
    htable_t *ht = (htable_t*)malloc(sizeof(htable_t));
    ht->size = 4;
    ht->table = (char **)malloc(sizeof(char*) * ht->size);

    ht->table[0] = "a";
    ht->table[1] = "e";
    ht->table[2] = "b";
    ht->table[3] = "c";

    return ht;
}

char *table5_s()
{
    return "      ht.size = 4\n      ht.table[0] = 'a'\n      ht.table[1] = 'e'\n      ht.table[2] = 'b'\n      ht.table[3] = 'c'\n";
}

/**************** Exercise 1 ****************/
/* helper_is_full
 *
 * ht: hash table
 * expected: expected output
 * ht_string: string representation of hash table
 * test_name: name of test
 */
void helper_is_full(htable_t ht, bool expected, char* ht_string, char *test_name)
{
    bool actual = is_full(ht);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: is_full(ht)\n"
          "\n      Actual: %d"
          "\n      Expected: %d"
          "\n  The filter to run this specific test is: --filter is_full/%s"),
         ht_string, actual, expected, test_name);
    
    cr_assert_eq(actual, expected, " %s", err_msg);
}

TestSuite(is_full, .timeout=60);

Test(is_full, testA) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    helper_is_full(*ht, true, ht_string, "testA");

    free(ht->table);
    free(ht);
}

Test(is_full, testB) {
    htable_t *ht = table2();
    char *ht_string = table2_s();
    helper_is_full(*ht, false, ht_string, "testB");

    free(ht->table);
    free(ht);
}

Test(is_full, testC) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    helper_is_full(*ht, false, ht_string, "testC");

    free(ht->table);
    free(ht);
}

/**************** Exercise 2 ****************/
/* helper_found_at
 *
 * ht: hash table
 * s: string to query
 * expected_found: expected out paramter
 * expected_return: expected output
 * ht_string: string representation of hash table
 * test_name: name of test
 */
void helper_found_at(htable_t ht, char *s, bool expected_found, int expected_return, char* ht_string, char *test_name)
{
    bool actual_found = false;
    int actual_return = found_at(ht, s, &actual_found);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: found_at(ht, '%s', found)\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(ht, s));
    
    cr_assert_eq(actual_return, expected_return, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter found_at/%s", err_msg, actual_return, expected_return, test_name);
    cr_assert_eq(actual_found, expected_found, " %s\n  Checking out parameter (found):\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter found_at/%s", err_msg, actual_found, expected_found, test_name);

}

TestSuite(found_at, .timeout=60);

Test(found_at, testA) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    helper_found_at(*ht, "a", true, 1, ht_string, "testA");
    free(ht->table);
    free(ht);
}

Test(found_at, testB) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    helper_found_at(*ht, "b", true, 2, ht_string, "testB");
    free(ht->table);
    free(ht);
}

Test(found_at, testC) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    helper_found_at(*ht, "z", false, -1, ht_string, "testC");
    free(ht->table);
    free(ht);
}

Test(found_at, testD) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    helper_found_at(*ht, "ac", false, 1, ht_string, "testD");
    free(ht->table);
    free(ht);
}

Test(found_at, testE) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    helper_found_at(*ht, "ab", false, 1, ht_string, "testE");
    free(ht->table);
    free(ht);
}

Test(found_at, testF) {
    htable_t *ht = table4();
    char *ht_string = table4_s();
    helper_found_at(*ht, "a", true, 3, ht_string, "testF");
    free(ht->table);
    free(ht);
}

Test(found_at, testG) {
    htable_t *ht = table5();
    char *ht_string = table5_s();
    helper_found_at(*ht, "a", true, 0, ht_string, "testG");
    free(ht->table);
    free(ht);
}

/**************** Exercise 3 ****************/
/* helper_query
 *
 * ht: hash table
 * s: string to query
 * expected: expected output
 * ht_string: string representation of hash table
 * test_name: name of test
 */
void helper_query(htable_t ht, char *s, bool expected, char* ht_string, char *test_name)
{
    bool actual = query(ht, s);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: query(ht, '%s')\n"
          "\n      Actual: %d"
          "\n      Expected: %d"
          "\n  The filter to run this specific test is: --filter query/%s"),
         ht_string, s, actual, expected, test_name);
    
    cr_assert_eq(actual, expected, " %s", err_msg);
}

TestSuite(query, .timeout=60);

Test(query, testA) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    helper_query(*ht, "a", true, ht_string, "testA");
    free(ht->table);
    free(ht);
}

Test(query, testB) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    helper_query(*ht, "z", false, ht_string, "testB");
    free(ht->table);
    free(ht);
}

Test(query, testC) {
    htable_t *ht = table2();
    char *ht_string = table2_s();
    helper_query(*ht, "a", false, ht_string, "testC");
    free(ht->table);
    free(ht);
}

Test(query, testD) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    helper_query(*ht, "a", false, ht_string, "testD");
    free(ht->table);
    free(ht);
}

Test(query, testE) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    helper_query(*ht, "d", true, ht_string, "testE");
    free(ht->table);
    free(ht);
}

Test(query, testF) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    helper_query(*ht, "b", false, ht_string, "testF");
    free(ht->table);
    free(ht);
}

Test(query, testG) {
    htable_t *ht = table4();
    char *ht_string = table4_s();
    helper_query(*ht, "a", true, ht_string, "testG");
    free(ht->table);
    free(ht);
}

Test(query, testH) {
    htable_t *ht = table5();
    char *ht_string = table5_s();
    helper_query(*ht, "a", true, ht_string, "testH");
    free(ht->table);
    free(ht);
}


/**************** Exercise 4 ****************/
/* helper_add
 *
 * ht: hash table
 * ht_string: string representation of hash table
 * s: string to add
 * actual: actual output
 * expected: expected output
 * test_name: name of test
 */
Test(add, testA) {
    htable_t *ht = table2();
    char *ht_string = table2_s();
    char *s = "a";
    char *test_name = "testA";

    bool actual = add(*ht, s);
    bool expected = true;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);
    cr_assert_eq(strcmp(ht->table[1], "a"), 0, " %s\n  Checking ht.table[1]:\n      Actual: '%s'\n      Expected: '%s'\n  The filter to run this specific test is: --filter add/%s", err_msg, ht->table[1], s, test_name);

    free(ht->table);
    free(ht);
}

TestSuite(add, .timeout=60);

Test(add, testB) {
    htable_t *ht = table1();
    char *ht_string = table1_s();
    char *s = "a";
    char *test_name = "testB";

    bool actual = add(*ht, s);
    bool expected = false;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);
    
    free(ht->table);
    free(ht);
}

Test(add, testC) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    char *s = "b";
    char *test_name = "testC";

    bool actual = add(*ht, s);
    bool expected = true;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);
    cr_assert_eq(strcmp(ht->table[2], s), 0, " %s\n  Checking ht.table[2]:\n      Actual: '%s'\n      Expected: '%s'\n  The filter to run this specific test is: --filter add/%s", err_msg, ht->table[1], s, test_name);

    free(ht->table);
    free(ht);
}

Test(add, testD) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    char *s = "bb";
    char *test_name = "testD";

    bool actual = add(*ht, s);
    bool expected = true;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);
    cr_assert_eq(strcmp(ht->table[1], s), 0, " %s\n  Checking ht.table[1]:\n      Actual: '%s'\n      Expected: '%s'\n  The filter to run this specific test is: --filter add/%s", err_msg, ht->table[1], s, test_name);

    free(ht->table);
    free(ht);
}

Test(add, testE) {
    htable_t *ht = table3();
    char *ht_string = table3_s();
    char *s = "ab";
    char *test_name = "testE";

    bool actual = add(*ht, s);
    bool expected = true;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);
    cr_assert_eq(strcmp(ht->table[1], s), 0, " %s\n  Checking ht.table[1]:\n      Actual: '%s'\n      Expected: '%s'\n  The filter to run this specific test is: --filter add/%s", err_msg, ht->table[1], s, test_name);

    free(ht->table);
    free(ht);
}

Test(add, testF) {
    htable_t *ht = table4();
    char *ht_string = table4_s();
    char *s = "a";
    char *test_name = "testF";

    bool actual = add(*ht, s);
    bool expected = false;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);

    free(ht->table);
    free(ht);
}

Test(add, testG) {
    htable_t *ht = table5();
    char *ht_string = table5_s();
    char *s = "a";
    char *test_name = "testG";

    bool actual = add(*ht, s);
    bool expected = false;
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
         ("\n  Hash table used in failed test: \n%s\n"
          "\n  Test failed: add(ht, '%s')\n"
          "\n      hash('%s'): %d\n"),
         ht_string, s, s, hash(*ht, s));
    
    cr_assert_eq(actual, expected, " %s\n  Checking return value:\n      Actual: %d\n      Expected: %d\n  The filter to run this specific test is: --filter add/%s", err_msg, actual, expected, test_name);

    free(ht->table);
    free(ht);
}