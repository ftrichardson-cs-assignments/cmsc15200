#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * add_array: adds up all the values in a array.
 *  
 *  data - an array of integers
 *  data_len - length of the data array 
 *    (greater than zero)
 *
 * Returns: the sum of all the numbers in array as an int
*/
int add_array(int data[], int data_len) 
{
	int sum_array = 0;

	for (int i = 0; i < data_len; i++) 
	{
		sum_array += data[i];
	}
	return sum_array;
}

int main()
{
    int x[] = {25};
	printf("%d", add_array(x, 1));
}
