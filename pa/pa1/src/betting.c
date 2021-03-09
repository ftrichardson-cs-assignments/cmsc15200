/* CS 152: A Game of Chance
 * FLYNN RICHARDSON */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "util.h"
#include "betting.h"


/* BET_AMOUNT HELPER FUNCTIONS */


/* set_bet: lowers bet amount to the amount of cash on hand
* if bet amount is ever greater (cannot bet more money than we have!)
*
* bet_amount: the amount the player is betting
* cash: the amount of cash player has on hand
*
* Returns: the adjusted (or unadjusted) bet amount
*/
double set_bet(double bet_amount, double cash)
{
  if (bet_amount > cash) 
  {
    bet_amount = cash;
  }
  return bet_amount;
}

/* set_bet_series: limits bet amount to not exceed 1 + series total and 
* reinitializes bet amount to $1.00 once series restarts (only applicable
* for series_strategy function)
* 
* series_total = number to limit bet amount
* bet_amount = the amount the player is betting
*
* Returns: the adjusted (or unadjusted) bet amount
*/ 
double set_bet_series(int series_total, double bet_amount)
{
  if (series_total + bet_amount > 1.00) 
  {
    bet_amount = 1.00 - series_total;
  }
  return bet_amount;
}


/* FIVE STRATEGIES */


/* bet_one_dollar: computes remaining cash from betting $1.00
on coin flipping a specified number of rounds
*
* init_amount: the initial amount of cash on hand
* num_bets: the maximum number of bets to make
* 
* Returns: amount of cash remaining as a double
*/
double one_dollar(double init_amount, int num_bets)
{
  int n;
  
  for (n = 1; n <= num_bets; n++) 
  {
    if (flip_coin()) 
    {
      init_amount += 1.00;
      
    } else 
    {
      init_amount -= 1.00;
      
      /* Break out of loop if init_amount equals 0 (run out of cash) */
      if (init_amount == 0) 
      {
        break;
      }
    }
  }
  return init_amount;
}

/* double_on_win: computes remaining cash after doubling bets
* for every successful coin flip for a specified number of rounds
* 
* init_amount: the initial amount of cash on hand
* num_bets: the maximum number of bets to make
* 
* Returns: amount of cash remaining as a double
*/
double double_on_win(double init_amount, int num_bets)
{
  /* Bet_amount starts at $1.00 */
  int n;
  double bet_amount = 1.00;
  
  for (n = 1; n <= num_bets; n++) 
  {
    bet_amount = set_bet(bet_amount, init_amount);
    
    if (flip_coin()) 
    {
      init_amount += bet_amount;
      bet_amount *= 2;
      
    } else 
    {
      init_amount -= bet_amount;
      
      if (init_amount == 0) 
      {
        break;
      }
    }
  }
  return init_amount;
}

/* double_on_loss: computes remaining cash after doubling bets
* for every unsuccessful coin flip
* 
* init_amount: the initial amount of cash on hand
* num_bets: the maximum number of bets to make
* 
* Returns: amount of cash remaining as a double
*/
double double_on_loss(double init_amount, int num_bets)
{
  int n; 
  double bet_amount = 1.00;
  
  for (n = 1; n <= num_bets; n++) 
  {
    bet_amount = set_bet(bet_amount, init_amount);
    
    if (flip_coin()) 
    {
      init_amount += bet_amount;
      
    } else 
    {
      init_amount -= bet_amount;
      bet_amount *= 2;
      
      if (init_amount == 0) 
      {
        break;
      }
    }
    
  }
  return init_amount;
}

/* fibonacci_strategy: computes remaining cash after betting
* next number in fibonacci sequence for every
* successful coin flip
* 
* init_amount: the initial amount of cash on hand
* num_bets: the maximum number of bets to make
* 
* Returns: amount of cash remaining as a double
*/
double fibonacci_strategy(double init_amount, int num_bets)
{
  /* Initialize bet_amount as $1.00, and initialize variables to
  represent the first two numbers in the fibonacci sequence */
  int n;
  double bet_amount = 1.00; 
  int x = 0, y = 1;
  
  for (n = 1; n <= num_bets; n++) 
  {
    bet_amount = set_bet(bet_amount, init_amount);
    
    if (flip_coin()) 
    {
      init_amount += bet_amount;
      bet_amount = 1.00;
      x = 0;
      y = 1;
      
    } else 
    {
      init_amount -= bet_amount;
      bet_amount = x + y;
      x = y;
      y = bet_amount;
      
      if (init_amount == 0) 
      {
        break;
      }  
    }
  }
  return init_amount;
}

/* series_strategy: computes remaining cash after placing bets
* in series, where the series total decreases by 1 for every
* unsuccessful coin flip, and the amount of a bet cannot exceed
* the series total + 1
* 
* init_amount: the initial amount of cash on hand
* num_bets: the maximum number of bets to make
* 
* Returns: amount of cash remaining as a double
*/
double series_strategy(double init_amount, int num_bets)
{
  int n, series_total = 0;
  double bet_amount = 1.00;
  
  for (n = 1; n <= num_bets; n++) 
  {
    /* These two functions ensure that bet_amount cannot exceed
    the amount of cash on hand, and that bet_amount is always $1.00 
    once a series restarts */
    bet_amount = set_bet(bet_amount, init_amount);
    bet_amount = set_bet_series(series_total, bet_amount);

    
    if (flip_coin()) 
    {
      init_amount += bet_amount;
      series_total += bet_amount;
      bet_amount += 1.00;
      
      /* If series_total reaches number greater than 1, set
      series_total equal to 0 for next iteration of loop */
      if (series_total >= 1) 
      {
        series_total = 0;
        
      }      
    } else 
    {
      init_amount -= bet_amount;
      series_total -= bet_amount;
      
      if (init_amount == 0) 
      {
        break;
      }
    }
  }
  return init_amount;
}


/* SIMULATIONS */


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
  /* Use seed to initialize random number generator */
  srand(seed);
  
  double remaining_cash;
  
  if (strategy == DOUBLE_ON_WIN) 
  {
    remaining_cash = double_on_win(init_amount, num_bets);
    
  } else if (strategy == ONE_DOLLAR) 
  {
    remaining_cash = one_dollar(init_amount, num_bets);
    
  } else if (strategy == DOUBLE_ON_LOSS) 
  {
    remaining_cash = double_on_loss(init_amount, num_bets);
    
  } else if (strategy == FIB_STRATEGY) 
  {
    remaining_cash = fibonacci_strategy(init_amount, num_bets);
    
  } else
  {
    remaining_cash = series_strategy(init_amount, num_bets);
    
  }
  return remaining_cash;
}

/* simulate_multiple_games: simulates multiple games
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
  int k;
  double remaining_cash = 0, average_cash;
  
  for (k = 1; k <= num_games; k++) 
  {
    remaining_cash += simulate_game(strategy, init_amount, num_bets, init_seed);
    
    /* Vary flip_coin() results by adding 1 to seed for each loop iteration */
    init_seed++;
  }
  average_cash = remaining_cash/num_games;
  return average_cash;
}