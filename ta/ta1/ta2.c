#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* For these questions, I am assuming that we are allowed to use the
mk_forward_backward function in our implementation of is_forward_backward_copy */

/* I also included the <string.h> header in my implementation */
char *mk_forward_backward(char *orig) 
{
	char* forward_backward = (char*)malloc((2 * strlen(orig) + 1) * sizeof(char));

	for (int i = 0; i < 2; i++) 
	{
		for (int j = 0; j < strlen(orig); j++) 
		{
			if (i == 0) 
			{
				forward_backward[(i * strlen(orig)) + j] = orig[j];

			} else 
			{
				forward_backward[(i * strlen(orig)) + j] = orig[(strlen(orig) - 1) - j];

			}
		}
	}	
	return forward_backward;
}

/* For these questions, I am assuming that we are allowed to use the
mk_forward_backward function in our implementation of is_forward_backward_copy */

/* I also included the <string.h> header in my implementation */
bool is_forward_backward_copy(char *orig, char *possible)
{
	char* forward_backward = mk_forward_backward(orig);

	if (strlen(forward_backward) != strlen(possible)) 
	{
		return false;
	}

	for (int n = 0; n < strlen(forward_backward); n++) 
	{
		if (forward_backward[n] != possible[n]) 
		{
			return false;
		}
	}
	return true;
}

int main()
{
  char* orig = "aaa";
  char* possible = "aaaaa";
  bool forward_backward = is_forward_backward_copy(orig, possible);
  printf("%d\n", forward_backward);
}
