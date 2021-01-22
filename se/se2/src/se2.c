#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

#include "se2.h"

// Constant needed for Exercises 3 and 4.
#define EPSILON 0.000001


/*
 * Exercise 1 - compute_payoff_amount 

 * Compute the amount left on a loan after days_since_loan_started
 * days. Payments of the specified payment amount are done every
 * payment_interval days.
 *
 * initial: initial loan amount (initial > 0)
 * payment: amount of each payment (payment > 0)
 * days_since_loan_started: the number of days since the loan started.
 *   This value may be negative, zero, or positive
 * payment_interval: payments are made every payment_interval number of days.  The first payment
 *  is made on day payment_interval.
 *
 * Returns: the amount left to payoff the loan as a double
 *
 * sample calls: 
 *    compute_payoff_amount(100.0, 2.0, 1, 1) yields 98.0
 *    compute_payoff_amount(100.0, 2.0, 5, 7) yields 100.0
 */
double compute_payoff_amount(double initial, double payment, int days_since_loan_started, int payment_interval)
{
    assert(initial > 0);
    assert(payment > 0);
    assert(payment_interval > 0);

    double payoff_amount;
    
    if (days_since_loan_started <= 0 || days_since_loan_started < payment_interval) {
        return initial;

    } else {
        payoff_amount = initial - ((days_since_loan_started / payment_interval) * payment);

        if (payoff_amount <= 0) {
            return 0;

        } else {
            return payoff_amount;
        }
        }
}
  
/*
 * Exercise 2
 * compute_leonardo - the Leonardo numbers are a sequence of numbers given by the recurrence:
 *   L(n) = 1  if n = 0
 *        = 1  if n = 1
 *        = L(n-1)+L(n-2)+1 if n > 1
 *  You must implement this function ITERATIVELY.
 *
 * The first few Leonardo Numbers are 1, 1, 3, 5, 9, 15, 25, 41, 67, 109, 177, 287, 465, 753, 1219, 1973
 *
 * Returns: nth leonardo number as an integer
 */
int compute_leonardo(int n)
{
    int i, x = 1, y = 1, z;

    if (n == 0 || n == 1) {
        return 1;

    } else {
        for (i = 2; i <= n; i++) {
            z = x + y + 1;
            x = y;
            y = z;
        }
        return y;
    }
}
/*
 * Exercise 3 -- computes the square root of S using the Bakhshali
 * method (as described in the writeup)
 *
 * This implementation must be ITERATIVE.
 *
 * S: the function computes the square root of S (S > 0)
 * guess: the initial guess for the square root of S
 *
 * Returns: an approximation to the square root of S.
 *
 * Sample calls:
 *  bakhshali_iterative(100, 20) yields 10.0
 *  bakhshali_iterative(2, -100) yields -1.414114 (approximately)
 */
double bakhshali_iterative(double S, double guess)
{
    assert(S > 0);

    double r, A;

    while (fabs((S - (guess * guess))) >= EPSILON) {
        r = (S - (guess * guess)) / (2 * guess);
        A = r + guess;
        guess = A - ((r * r) / (2 * A));
    }
    return guess;
}

/*
 * Exercise 4 -- computes the square root of S using the Bakhshali
 * method (as described in the writeup)
 *
 * This implementation must be RECURSIVE.
 *
 * S: the function computes the square root of S (S > 0)
 * guess: the current guess for the square root of S
 *
 * Returns: an approximation to the square root of S.
 *
 * Sample calls:
 *  bakhshali_recursive(100, 20) yields 10.0
 *  bakhshali_recursive(2, -100) yields -1.414114 (approximately)
 */
double bakhshali_recursive(double S, double guess)
{
    assert(S > 0);

    // YOUR CODE GOES HERE
    // REPLACE 0.0 WITH A SUITABLE RETURN VALUE
    
    return 0.0;
}
