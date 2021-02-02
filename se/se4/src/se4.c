#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "se4.h"

// Constants for Exercise 1
#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

/* Exercise 1 - find_amount_of_denomination
 *
 * Find the maximum number of coins whose value is less than or equal to
 * a total amount of cents 
 * 
 * cents: total amount of cents
 * denomination: value of a coin in cents
 * num_denomination_ptr: the number of coins whose value is less than or equal 
 *     to cents (out parameter)
 * 
 * Returns: the total value of the coins
 * 
 * sample calls:
 *     find_amount_of_denomination(117, 25, num_denomination) yields:
 *         100, num_denomination points to 4
 *     find_amount_of_denomination(88, 10, num_denomination) yields:
 *         80, num_denomination points to 8
 */
int find_amount_of_denomination(int cents, int denomination, 
                                int *num_denomination_ptr)
{
    int coins_value;

    *num_denomination_ptr = cents / denomination;
    coins_value = denomination * *num_denomination_ptr;
    
    return coins_value;
}

/* Exercise 1 - make_change
 *
 * Find the minimum number of coins whose value is a total amount of cents
 * 
 * cents: total amount of cents
 * 
 * Returns: a struct coins
 * 
 * sample calls:
 *     make_change(117) yields a struct coins with:
 *         quarters: 4
 *         dimes: 1
 *         nickels: 1
 *         pennies: 2
 *     make_change(88) yields a struct coins with:
 *         quarters: 2
 *         dimes: 3
 *         nickels: 1
 *         pennies: 3
 */
struct coins make_change(int cents)
{
    struct coins c;

    // YOUR CODE HERE

    return c;
}

/* Exercise 2 - repeat
 *
 * Create a new struct tagged_array with the array in the data field repeated
 * 
 * t_arr: a tagged array to repeat
 * 
 * Returns: a pointer to a struct tagged_array
 * 
 * sample calls:
 *     Let t_arr be the following struct tagged_array with fields:
 *         tag:     STRING
 *         arr_len: 5
 *         data.s:  "hello"
 *     repeat(t_arr) yields a pointer to the struct tagged_array with fields:
 *         tag:     STRING
 *         arr_len: 10
 *         data.s:  "hellohello"
 * 
 *     Let t_arr be the following struct tagged_array with fields:
 *         tag:     INT_ARRAY
 *         arr_len: 4
 *         data.a:  {9, 8, 7, 6}
 *     repeat(t_arr) yields a pointer to the struct tagged_array with fields:
 *         tag:     INT_ARRAY
 *         arr_len: 8
 *         data.a:  {9, 8, 7, 6, 9, 8, 7, 6}        
 */
struct tagged_array *repeat(struct tagged_array t_arr){

    // YOUR CODE HERE
    // REPLACE NULL WITH YOUR RETURN VALUE

    return NULL;
}

/* Exercise 3 - create_negative
 *
 * Create the negative of a black and white square image
 * 
 * image: a 2D array of bools
 * len: the length of one side of the image
 * 
 * Returns: a 2D array of bools
 * 
 * sample calls:
 *     create_negative({{1, 0}, {0, 1}}, 2) yields:
 *         the array {{0, 1}, {1, 0}}
 *     create_negative({{1, 1, 0}, {0, 1, 0}}, 3) yields:
 *         the array {{0, 0, 1}, {1, 0, 1}}
 */
bool **create_negative(bool** image, int len){

    // YOUR CODE HERE
    // REPLACE NULL WITH YOUR RETURN VALUE

    return NULL;
}
