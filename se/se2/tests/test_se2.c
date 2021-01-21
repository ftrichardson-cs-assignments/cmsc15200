#include <stdbool.h>
#include <stdio.h>
#include <criterion/criterion.h>
#include <math.h>
#include "se2.h"


#define EPSILON (0.000001)
#define ERR_MSG_LEN (1000)

/**************** Exercise 1 ****************/
/* helper_compute_payoff: Do the work of testing compute_payoff_amount
 *
 * init_amount: initial amount of the loan (init_amount > 0)
 * payment: payment amount (payment > 0)
 * day_since_loan_started: the number of days since the loan started
 *   (may be zero or negative)
 * payment_cycle: a payment made every payment_cycle number of days.
 *  (payment_cycle > 0)
 * expected: the expected result
 * test_name - the test name to be used in error messages.
 */
void helper_compute_payoff(double init_amount, double payment, int days_since_loan,
			   int payment_cycle, double expected, char *test_name)
{
    double actual = compute_payoff_amount(init_amount, payment, days_since_loan, payment_cycle);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: compute_payoff_amount(%f, %f, %d, %d)\n"
	      "\n     Actual: %f"
	      "\n     Expected: %f"
	      "\n  The filter to run this specific test is: --filter compute_payoff_amount/%s"),
	     init_amount, payment, days_since_loan, payment_cycle,
	     actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_float_eq(actual, expected, EPSILON, " %s", err_msg);
}

Test(compute_payoff_amount, testA) {
    helper_compute_payoff(100.0, 2.0, 1, 1, 98.0, "testA");
}

Test(compute_payoff_amount, testB) {
  helper_compute_payoff(100.0, 2.0, 50, 1, 0, "testB");
}

Test(compute_payoff_amount, testC) {
    helper_compute_payoff(100.0, 2.0, 51, 1, 0, "testC");
}

Test(compute_payoff_amount, testD) {
    helper_compute_payoff(100.0, 2.0, 0, 1, 100.0, "testD");
}

Test(compute_payoff_amount, testE) {
    helper_compute_payoff(100.0, 2.0, -1, 1, 100.0, "testE");
}

Test(compute_payoff_amount, testF) {
    helper_compute_payoff(100.0, 2.0, 20, 7, 96.0, "testF");
}

Test(compute_payoff_amount, testG) {
    helper_compute_payoff(100.0, 2.0, 349, 7, 2.0, "testE");
}

Test(compute_payoff_amount, testH) {
    helper_compute_payoff(100.0, 2.0, 351, 7, 0.0, "testF");
}

Test(compute_payoff_amount, testI) {
    helper_compute_payoff(10.0, 3.0, 2, 3, 10.0, "testG");
}

Test(compute_payoff_amount, testJ) {
    helper_compute_payoff(10.0, 3.0, 9, 3, 1.0,  "testH");
}

Test(compute_payoff_amount, testK) {
    helper_compute_payoff(10.0, 3.0, 9, 3, 1.0,  "testK");
}


/**************** Exercise 2 ****************/
/* helper_compute_leonardo - do the work of testing compute_leonardo
 *
 * n: input to leonardo (n > 0)
 * expected: the expected result
 * test_name: the test name to be used in error messages.
 */

void helper_compute_leonardo(int n, int expected, char *test_name)
{
    int actual = compute_leonardo(n);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: compute_leonardo(%d)\n"
	      "\n     Actual: %d"
	      "\n     Expected: %d"
	      "\n  The filter to run this specific test is: --filter compute_leonardo/%s"),
	     n, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_eq(actual, expected, " %s", err_msg);
}

Test(compute_leonardo, testA) {
    helper_compute_leonardo(0, 1, "testA");
}

Test(compute_leonardo, testB) {
    helper_compute_leonardo(1, 1, "testB");
}

Test(compute_leonardo, testC) {
    helper_compute_leonardo(2, 3, "testC");
}

Test(compute_leonardo, testD) {
    helper_compute_leonardo(18, 8361, "testD");
}


/**************** Exercise 3 ****************/
/* helper_bakhshali_iterative: do the work of testing bakhshali_iterative
 *
 * S: the function computes the square root of S (S > 0)
 * guess: the current guess
 * expected: the expected result
 * test_name: the name of the tests for error messages
 */
void helper_bakhshali_iterative(double S, double guess, double expected, char *test_name)
{
    double actual = bakhshali_iterative(S, guess);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: bakhshali_iterative(%f, %f)\n"
	      "\n     Actual: %f"
	      "\n     Expected: %f"
	      "\n  The filter to run this specific test is: --filter bakhshali_iterative/%s"),
	     S, guess, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_float_eq(actual, expected, EPSILON, " %s", err_msg);
}

Test(bakhshali_iterative, testA) {
    helper_bakhshali_iterative(100, 10.5, 10.0, "testA");
}

Test(bakhshali_iterative, testB) {
    helper_bakhshali_iterative(2, -100, -1.414214, "testB");
}

Test(bakhshali_iterative, testC) {
    helper_bakhshali_iterative(4, 2, 2, "testC");
}

Test(bakhshali_iterative, testD) {
    // Example from the Wikipedia article on computing square roots.
    helper_bakhshali_iterative(125348, 600, 354.045195, "testD");
}


/**************** Exercise 4 ****************/
/* helper_bakhshali_recursive: do the work of testing bakhshali_recursive
 *
 * S: the value we are computing the square root of
 * guess: the current guess
 * expected: the expected result
 * test_name: the name of the tests for error messages
 */
void helper_bakhshali_recursive(double S, double guess, double expected, char *test_name)
{
    double actual = bakhshali_recursive(S, guess);
    char err_msg[ERR_MSG_LEN];

    snprintf(err_msg, ERR_MSG_LEN-1,
	     ("\n  Parameters used in failed test: bakhshali_recursive(%f, %f)\n"
	      "\n     Actual: %f"
	      "\n     Expected: %f"
	      "\n  The filter to run this specific test is: --filter bakhshali_recursive/%s"),
	     S, guess, actual, expected, test_name);
    
    // the format string starts with a space because the logging tool
    // seems to ignore a leading \n.
    cr_assert_float_eq(actual, expected, EPSILON, " %s", err_msg);
}

Test(bakhshali_recursive, testA) {
    helper_bakhshali_recursive(100, 10.5, 10.0, "testA");
}

Test(bakhshali_recursive, testB) {
    helper_bakhshali_recursive(2, -100, -1.414214, "testB");
}

Test(bakhshali_recursive, testC) {
    helper_bakhshali_recursive(4, 2, 2, "testC");
}

Test(bakhshali_recursive, testD) {
    // Example from the Wikipedia article on computing square roots.
    helper_bakhshali_recursive(125348, 600, 354.045195, "testD");
}


