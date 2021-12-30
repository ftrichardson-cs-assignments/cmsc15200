#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "util.h"
#include "betting.h"

/* bet_one_or_double: computes remaining cash from betting $1 each
 * round, doubling bets after each successful coin flip, or doubling bets
 * bets after every unsuccessful coin flip (depending on the specified strategy)
 *
 * strategy: the betting strategy to use
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 *
 * Returns: amount of cash remaining as a double
 */
double bet_one_or_double(double init_amount, int num_bets, enum betting_strategies strategy) 
{
    double bet_amount = 1.0;
    
    for (int i = 0; i < num_bets; i++) {
        // Never bet more than we have on hand
        if (bet_amount > init_amount) {
            bet_amount = init_amount;
        }
        bool coin_flip_result = flip_coin();

        if (strategy == DOUBLE_ON_WIN) {
            if (coin_flip_result) {
                init_amount += bet_amount;
                bet_amount *= 2;

            } else {
                init_amount -= bet_amount;

                if (init_amount == 0) {
                    break;
                }
            }
        } else if (strategy == DOUBLE_ON_LOSS) {
            if (coin_flip_result) {
                init_amount += bet_amount;

            } else {
                init_amount -= bet_amount;

                if (init_amount == 0) {
                    break;
                }

                bet_amount *= 2;
            }
        } else { // Bet one dollar each round
            if (coin_flip_result) {

                init_amount += bet_amount;

            } else {
                init_amount -= bet_amount;

                if (init_amount == 0) {
                    break;
                }
            }
        }
    }
    return init_amount;
}

/* bet_fibonacci: computes remaining cash after betting
 * next number in fibonacci sequence for every
 * successful coin flip
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 *
 * Returns: amount of cash remaining as a double
 */
double bet_fibonacci(double init_amount, int num_bets) 
{
    double bet_amount = 1.0;

    int x = 0, y = 1; // Fibonacci trackers

    for (int i = 0; i < num_bets; i++) {
        if (bet_amount > init_amount) {
            bet_amount = init_amount;
        }

        bool coin_flip_result = flip_coin();
        if (coin_flip_result) {
            init_amount += bet_amount;

            x = 0;
            y = 1;
            bet_amount = 1.0;

        } else {
            init_amount -= bet_amount;
            if (init_amount == 0) {
                break;
            }

            bet_amount = x + y;
            x = y;
            y = bet_amount;
        }
    }
    return init_amount;
}

/* bet_series: computes remaining cash after placing bets
* in series, where the series total decreases by 1 for every
* unsuccessful coin flip, and the amount of a bet cannot exceed
* the series total + 1
* 
* init_amount: the initial amount of cash on hand
* num_bets: the maximum number of bets to make
* 
* Returns: amount of cash remaining as a double
*/
double bet_series(double init_amount, int num_bets) 
{
    double bet_amount = 1.0, series_total = 0.0;

    for (int i = 0; i < num_bets; i++) {
        // Adjust bet amount to accomodate series betting strategy FIRST
        if (bet_amount + series_total > 1.0) {
            bet_amount = 1.0 - series_total;
        }

        if (bet_amount > init_amount) {
            bet_amount = init_amount;
        }

        bool coin_flip_result = flip_coin();
        if (coin_flip_result) {
            init_amount += bet_amount;
            series_total += bet_amount;
            bet_amount += 1.0;

            // Reset series if series total becomes $1 or greater
            if (series_total >= 1.0) {
                series_total = 0.0;
            }

        } else {
            init_amount -= bet_amount;
            series_total -= bet_amount;

            if (init_amount == 0) {
                break;
            }
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
    // Do not remove or move this call to srand.  It initializes the
    // random number generator, which should be done exactly once per
    // game.
    srand(seed);

    double final_amount;
    
    if (strategy == FIB_STRATEGY) {
        final_amount = bet_fibonacci(init_amount, num_bets);
    } else if (strategy == SERIES_STRATEGY) {
        final_amount = bet_series(init_amount, num_bets);
    } else {
        final_amount = bet_one_or_double(init_amount, num_bets, strategy);
    }

    return final_amount;
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
    double total_cash = 0.0;

    for (int i = 0; i < num_games; i++) {
        total_cash += simulate_game(strategy, init_amount, num_bets, init_seed);
        init_seed++;
    }

    return total_cash / num_games;
}