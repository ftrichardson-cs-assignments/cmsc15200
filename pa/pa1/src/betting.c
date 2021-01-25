/* CS 152: A Game of Chance
 * FLYNN RICHARDSON
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "util.h"
#include "betting.h"


/* bet_one_dollar: computes remaining cash from betting $1
   on coin flipping a specified number of times
 *
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: amount of cash remaining as a double
 */

double one_dollar(double init_amount, int num_bets)
{
    int n;

    /* Perform coin flip num_bets number of times */
    for (n = 1; n <= num_bets; n++) 
    {
        if (flip_coin()) 
        {
            /* Increase init_amount by 1 for every successful coin flip */
            init_amount++;
        } else 
        {
            /* Decrease init_amount by 1 for every unsuccessful coin flip */
            init_amount--;

            /* Break out of loop if init_amount equals 0 */
            if (init_amount == 0) 
            {
                break;
            }
        }
    }
    return init_amount;
}

/* double_on_win: computes remaining cash after doubling bets
 * for every successful coin flip
 * 
 * init_amount: the initial amount of cash on hand
 * num_bets: the maximum number of bets to make
 * 
 * Returns: amount of cash remaining as a double
 */

double double_on_win(double init_amount, int num_bets)
{
    int n, bet_amount = 1;
  
    /* Perform coin flip num_bets number of times */
    for (n = 1; n <= num_bets; n++) 
    {
        /* Lower bet_amount to init_amount if bet_amount is greater
        (Cannot bet more money than we have!) */
        if (bet_amount > init_amount) 
        {
            bet_amount = init_amount;
      
            /* Increase init_amount by bet_amount and double bet_amount for
            next round if coin flip is successful */
            if (flip_coin()) 
            {
                init_amount += bet_amount;
                bet_amount *= 2;
        
            /* Otherwise, decrease init_amount by bet_amount */
            } else 
            {
                init_amount -= bet_amount;
        
                /* Break out of loop if init_amount equals 0 */
                if (init_amount == 0) 
                {
                    break;
                }
            }
      
        /* Otherwise, do not change bet_amount */
        } else 
        {
            /* For lines 84-97, refer to 65-78 (same code) */
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
  /* Initialize bet_amount as $1 */
  int n, bet_amount = 1;
  
  /* The following code is the same as the double_on_win function,
  except for lines 120-134 and lines 140-152. Refer to the former section for
  new code commentary */
  for (n = 1; n <= num_bets; n++) 
  {
      
      if (bet_amount > init_amount) 
      {
          bet_amount = init_amount;
      
          /* Increase init_amount by bet_amount if coin flip is successful */
          if (flip_coin()) 
          {
              init_amount += bet_amount;
        
          /* Otherwise, increase init_amount by bet_amount and double 
          bet_amount for the next round */
          } else 
          {
              init_amount -= bet_amount;
              bet_amount *= 2;
        
              if (init_amount == 0) {
                  break;
              }
          }
      
      } else 
      {

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
    /* Initialize bet_amount as $1, and initialize variables to
    represent the first two numbers in the fibonacci sequence */
    int n, bet_amount = 1;
    int x = 0, y = 1;
  
    
    for (n = 1; n <= num_bets; n++) 
    {
        if (bet_amount > init_amount) 
        {
            bet_amount = init_amount;
      
            /* Increase init_amount by bet_amount and re-initialize variables 
            if coin flip is successful */
            if (flip_coin()) 
            {
                init_amount += bet_amount;
                bet_amount = 1;
                x = 0;
                y = 1;
        
            /* However, if coin flip is unsuccessful (tails), decrease
            init_amount by bet_amount, and set bet_amount equal to
            the next number in the fibonacci sequence */
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
      
        } else 
        {
            if (flip_coin()) 
            {
                init_amount += bet_amount;
                bet_amount = 1;
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
    /* Note: A lot of code in this function is repetitive */
    /* Initialize bet_amount to $1 and series_total to $0 */
    int n, bet_amount = 1, series_total = 0;
  
    for (n = 1; n <= num_bets; n++) 
    {
        /* Set bet_amount equal to 1 - series_total if the sum of
        series_total and bet_amount yields a number greater than 1 */
        if (series_total + bet_amount > 1) 
        {
            bet_amount = 1 - series_total;
      
            if (bet_amount > init_amount) 
            {
                bet_amount = init_amount;
        
                /* Increase both init_amount and series_total by bet_amount
                and increase bet_amount by 1 if coin flip successful */
                if (flip_coin()) 
                {
                    init_amount += bet_amount;
                    series_total += bet_amount;
                    bet_amount += 1;
          
                    /* If series_total reaches number greater than 1, set
                    series_total equal to 0 (restarting series) */
                    if (series_total >= 1) 
                    {
                        series_total = 0;
            
                    }
                
                /* Decrease init_amount and series_total by bet_amount if
                coin flip unsuccessful */
                } else 
                {
                    init_amount -= bet_amount;
                    series_total -= bet_amount;
          
                    if (init_amount == 0) 
                    {
                        break;
                    }
                }
            } else 
            {
                if (flip_coin()) 
                {
                    init_amount += bet_amount;
                    series_total += bet_amount;
                    bet_amount += 1;
          
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
        } else 
        {
            if (bet_amount > init_amount) 
            {
                bet_amount = init_amount;
        
                if (flip_coin()) 
                {
                    init_amount += bet_amount;
                    series_total += bet_amount;
                    bet_amount += 1;
          
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
            } else 
            {
                if (flip_coin()) 
                {
                    init_amount += bet_amount;
                    series_total += bet_amount;
                    bet_amount += 1;
          
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
    /* Use seed to initialize random number generator */
    srand(seed);
  
    double remaining_cash;
  
    /* Execute strategy depending on strategy input */
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
    
    } else if (strategy == SERIES_STRATEGY) 
    {
        remaining_cash = series_strategy(init_amount, num_bets);
    
    } else 
    {
        remaining_cash = flip_only(init_amount, num_bets);
    
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
    double remaining_cash = 0;
  
    /* Simulate an individual game num_games number of times */
    for (k = 1; k <= num_games; k++) 
    {
        remaining_cash += simulate_game(strategy, init_amount, num_bets, init_seed);

        /* Before executing next iteration of loop, add 1 to seed */
        init_seed++;
    }
    /* Return the average cash at the end of simulation */
    return remaining_cash/num_games;
}