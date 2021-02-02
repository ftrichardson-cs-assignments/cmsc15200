#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "se4.h"

/** Add your test functions (if any) here **/

/* 
 * Helper function for create_negative. 
 * Creates an image of a smiley face.
 * 
 * Returns: a 2D array of bools
 */
bool **make_smiley_face()
{

    // create smiley face to test create_negative
    int len = 10;
    bool** image = (bool**)malloc(sizeof(bool*) * len);
    for (int i = 0; i < len; i++){
        image[i] = (bool*)malloc(sizeof(bool) * len);
    }
    for (int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            image[i][j] = 0;
        }
    }
    // smile
    image[5][2] = 1;
    image[6][3] = 1;
    image[7][4] = 1;
    image[7][5] = 1;
    image[6][6] = 1;
    image[5][7] = 1;
    // eyes
    image[2][3] = 1;
    image[2][6] = 1;

    return image;
}

/* 
 * Helper function for create_negative. 
 * Prints an image in PBM format.
 * 
 * image: image to print
 * len: length of one side of square image
 */
void print_image(bool **image, int len)
{

    // print header
    printf("P1\n");
    printf("%d %d\n", len, len);

    // print image
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            printf("%d ", image[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    bool** smiley_face = make_smiley_face(); // smiley_face is 10 x 10
    
    /** Add calls to your functions here **/

    print_image(smiley_face, 10);
}
