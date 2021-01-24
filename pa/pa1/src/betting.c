#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "util.h"
#include "betting.h"


/* bet_one_dollar: computes remaining cash after betting a dollar
   on coin flipping a specified number of times
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: amount of cash remaining
 */

double bet_one_dollar(double init_amount, int num_bets)
{
    int n;

    for (n = 1; n <= num_bets; n++) {
        if (flip_coin()) {
            init_amount++;

        } else {
              init_amount--;

              if (init_amount == 0) {
                  break;
              }
        }
    }
    return init_amount;
}

/* double_bet: computes remaining cash after either doubling bet each
 * round of heads or doubling bet each round of tails (depending on 
 * specified betting strategy)
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: amount of cash remaining
 */

double double_bet(enum betting_strategies strategy, double init_amount,
                  int num_bets)
{
    int n, bet_amount = 1;

    for (n = 1; n <= num_bets; n++) {
        if (flip_coin()) {
            if (strategy == DOUBLE_ON_WIN) {
                init_amount += bet_amount;
                bet_amount *= 2;

            } else {
                init_amount -= bet_amount;

                if (init_amount <= 0) {
                    return 0.00;
                }
            }
        } else {
            if (strategy == DOUBLE_ON_LOSS) {
                init_amount -= bet_amount;
                bet_amount *= 2;

                if (init_amount <= 0) {
                    return 0.00;
                }

            } else {
                init_amount += bet_amount;
            }
        }
    }
    return init_amount;
}

/* fibonacci_bet: computes remaining cash after altering bets according to
 * the fibonacci sequence (resetting to $1 for every round of heads)

 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: amount of cash remaining
 */

double fibonacci_bet(double init_amount, int num_bets)
{
    int n, bet_amount = 1;
    int x = 0, y = 1;

    for (n = 1; n <= num_bets; n++) {
        if (flip_coin()) {
            init_amount += bet_amount;
            bet_amount = 1;
            x = 0;
            y = 1;

        } else {
            init_amount -= bet_amount;
            bet_amount = x + y;
            x = y;
            y = bet_amount;
        }
    }
    return init_amount;
}

/* simulate_game: simulate a single game
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * unsigned int seed: used to initialize the random number generator
 *
 * Returns: the amount of cash on hand at the end of the game as a double.
 */
double simulate_game(enum betting_strategies strategy, double init_amount,
                     int num_bets, unsigned int seed)
{
    srand(seed);

    double remaining_cash;

    if (strategy == ONE_DOLLAR) {
        remaining_cash = bet_one_dollar(init_amount, num_bets);

    } else if (strategy == DOUBLE_ON_WIN || strategy == DOUBLE_ON_LOSS) {
          remaining_cash = double_bet(strategy, init_amount, num_bets);

    } else if (strategy == FIB_STRATEGY) {
          remaining_cash = fibonacci_bet(init_amount, num_bets);

    } else if (strategy == FLIP_ONLY) {
          remaining_cash = flip_only(init_amount, num_bets);

    } else {
          remaining_cash = 11.0;

    }
    return remaining_cash;
}


/* simulate_game: simulate multiple games
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * init_seed: the initial value used for the random number generator
 *   seed
 * num_games: the number of games to simulate
 *
 * Returns: average amount of cash on hand at the end of the simulated
 *    games as a double
 */
double simulate_multiple_games(enum betting_strategies strategy, double init_amount,
                               int num_bets, unsigned int init_seed, int num_games)
{
    // YOUR CODE HERE
    // Replace 0.0 with an appropriate return value
    return 0.0;
}
