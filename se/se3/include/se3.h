/* Exercise 1 - find_min_max
 *
 * Find the minimum value and the maximum value in an 
 * array of ints. Returns pointers to the minimum and maximum as out parameters.
 * 
 * a: array of postitive ints
 * a_len: number of elements (length) of array a
 * min_ptr: a pointer to the minimum value in array a (out parameter)
 * max_ptr: a pointer to the maximum value in array a (out parameter)
 * 
 * sample calls:
 *     Let a be the int array with elements {3, 2, 2, 4, 3, 5}.
 *     find_min_max(a, 6, min_ptr, max_ptr) yields:
 *         min_ptr points to: 2
 *         max_ptr points to: 5
 *     
 *     Let b be the int array with elements {4, 7, 4, 5, 4}.
 *     find_min_max(b, 5, min_ptr, max_ptr) yields: 
 *         min_ptr points to: 4
 *         max_ptr points to: 7 
 */
void find_min_max(int a[], int a_len, int *min_ptr, int *max_ptr);

/* Exercise 2 - make_star_string
 * 
 * Creates a heap allocated string of stars (*).
 * 
 * n: number of stars in the string (n >= 0)
 * 
 * Returns: a string
 * 
 * sample calls:
 *     make_star_string(3) yields "***"
 *     make_star_string(5) yields "*****"
 */
char* make_star_string(int n);

/* Exercise 3 - make_histogram
 * 
 * Creates a heap allocated histogram array from an int array.
 * 
 * a: array of postitive ints
 * a_len: number of elements (length) of array a
 * hist_len: a pointer to the length of the histogram array (out parameter)
 * 
 * Returns: an int array
 * 
 * sample calls:
 *     Let a be the int array with elements {3, 2, 2, 4, 3, 5}.
 *     make_histogram(a, 6, hist_len) yields:
 *         the int array {2, 2, 1, 1}
 *         hist_len points to: 4
 *     In this example, there are two 2's, two 3's, one 4, and one 5.
 *     
 *     Let b be the int array with elements {4, 7, 4, 5, 4, 8}.
 *     make_histogram(b, 5, hist_len) yields:
 *         the int array {3, 1, 0, 1, 1} 
 *         hist_len points to: 5
 *     In this example, there are three 4's, one 5, zero 6's, one 7, and one 8.
 */
int* make_histogram(int a[], int a_len, int *hist_len);

/* Exercise 4 - make_star_array
 * 
 * Creates a heap allocated array of strings where
 * each string is a string of stars. The number of stars
 * is the number in the input array.
 * 
 * a: array of nonnegative ints
 * a_len: number of elements (length) of array a
 * 
 * Returns: an array of strings
 * 
 * sample calls:
 *     Let a be the int array with elements {2, 2, 1, 1}.
 *     make_star_array(a, 4) yields the string array {"**", "**", "*", "*"}
 *     
 *     Let b be the int array with elements {3, 1, 0, 1} 
 *     make_star_array(b, 4) yields the string array {"***", "*", "", "*"}
 */
char** make_star_array(int a[], int a_len);

/* Exercise 5 - make_histogram_visualization
 *
 * Creates a heap allocated array of strings where
 * each string is a string of stars. The number of stars
 * is the number in the histogram of the input array.
 * 
 * a: array of postitive ints
 * a_len: number of elements (length) of array a
 * hist_len_ptr: number of elements (length) of histogram array (out paramter)
 * 
 * Returns: an array of string
 * 
 * sample calls:
 *     Let a be the int array with elements {3, 2, 2, 4, 3, 5}.
 *     make_histogram_visualization(a, 6, hist_len_ptr) yields:
 *         the string array {"**", "**", "*", "*"}
 *         hist_len_ptr points to: 4
 *     
 *     Let b be the int array with elements {4, 7, 4, 5, 4}.
 *     make_histogram_visualization(b, 5, hist_len_ptr) yields:
 *         the string array {"***", "*", "", "*"}
 *         hist_len_ptr points to: 4
 * 
 *     Let c be the int array with elements {5, 6, 6, 5, 6, 5, 6, 6}.
 *     make_histogram_visualization(c, 8, hist_len_ptr) yields:
 *         the string array {"***", "*****"}
 *         hist_len_ptr points to: 2
 */
char** make_histogram_visualization(int a[], int a_len, int *hist_len_ptr);