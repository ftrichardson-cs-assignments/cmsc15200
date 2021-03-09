#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* filter_by_value: computes a new array that contains (in order
 *   of appearance) the values from data that 
 *   occur in vals_to_keep.
 *
 * data - array to filter
 * data_len - length of data
 * vals_of_interest - the values of interest
 * vals_len - the length of vals_of_interest
 * result_len_ptr - will hold the length of the result 
 *   (out parameter)
 *
 * Returns:
 *   - array of integers with the values from data that occur in
 *     vals of interest
 *   - NULL if none of the values match
 */
int *filter_by_value(int data[], int data_len, int vals_of_interest[], int vals_len, int *result_len_ptr) 
{
	*result_len_ptr = 0;

	for (int a = 0; a < vals_len; a++) 
	{
		for (int b = 0; b < data_len; b++) 
		{
			if (data[b] == vals_of_interest[a]) 
			{
				*result_len_ptr += 1;
			}
		}
	}

	if (*result_len_ptr == 0) 
	{
		return NULL;
	}

	int* array = (int*)malloc(*result_len_ptr * sizeof(int));
	int array_index = 0;

	for (int x = 0; x < data_len; x++) 
	{
		for (int y = 0; y < vals_len; y++) 
		{
			if (data[x] == vals_of_interest[y]) 
			{
				array[array_index] = data[x];
				array_index++;
			}
		}
	}
	return array;
}

int main()
{
	int p;
	int data[] = {1, 2, 3, 4, 5, 6, 4, 1};
	int data_len = 8;
	int vals_of_interest[] = {1, 6};
	int vals_len = 2;
	int* array = filter_by_value(data, data_len, vals_of_interest, vals_len, &p);
	printf("%d\n", p);
	for (int i = 0; i < p; i++) 
	{
		printf("%d", array[i]);
	}
}
