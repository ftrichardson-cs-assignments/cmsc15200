#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*
 * most_generous_reviewer: find the most "generous" reviewer
 *     A reviewer is generous if they award high ratings
 *    
 * num_reviewers: number of reviewers
 * num_movies: number of movies
 * ratings: two-dimensional array of movie ratings
 *  rows are reviewers
 *  columns are movies
 *
 * Returns: the index of the most generous reviewer
*/
int most_generous_reviewer(int num_reviewers, int num_movies, double ratings[num_reviewers][num_movies]) 
{
	int winning_points = 0, winning_reviewer;
	
	for (int i = 0; i < num_reviewers; i++)
	{
		int num_points = 0;

		for (int j = 0; j < num_movies; j++) 
		{
			if (i == 0) 
			{
				num_points += ratings[i][j];
				winning_points = num_points;
				winning_reviewer = 0;

			} else
			{
				num_points += ratings[i][j];

				if (num_points > winning_points) 
				{
					winning_points = num_points;
					winning_reviewer = i;
				}
			}
		}
	}
	return winning_reviewer;
}


/*
 * most_controversial_movie: find the most "controversial" movie
 *     A movie is controversial if the difference between its 
 *.    highest and lowest rating is large.
 *    
 * num_reviewers: number of reviewers
 * num_movies: number of movies
 * ratings: two-dimensional array of movie ratings
 *   rows are reviewers
 *   columns are movies
 *
 * Returns: the index of the most controversial movie
*/
int most_controversial_movie(int num_reviewers, int num_movies, double ratings[num_reviewers][num_movies]) 
{
	double largest_difference;
	int controversial_movie;
	
	for (int i = 0; i < num_movies; i++) 
	{
		double min_review = ratings[0][i], max_review = ratings[0][i];
		
		for (int j = 0; j < num_reviewers; j++) 
		{
			if (ratings[j][i] < min_review) 
			{
				min_review = ratings[j][i];

			}

			if (ratings[j][i] > max_review) 
			{
				max_review = ratings[j][i];
			}
		}
		
		if (i == 0) 
		{
			largest_difference = max_review - min_review;
			controversial_movie = 0;
		}

		if (max_review - min_review > largest_difference) 
		{
			largest_difference = max_review - min_review;
			controversial_movie = i;
		}
	}
	return controversial_movie;
}

int main()
{
	double ratings[4][3] = {{2, 7, 5}, {4, 9, 4}, {6, 6, 8}, {3, 7, 8}};
	int controversial_movie = most_controversial_movie(4, 3, ratings);
	printf("%d", controversial_movie);
}
