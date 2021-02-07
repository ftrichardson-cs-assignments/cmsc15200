#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "images.h"

//Constant for Task 2
#define MAX_INTENSITY 255

/* new_ppm: create new black ppm
 *
 * height: height of image
 * width: width of image
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *new_ppm(int height, int width)
{
    ppm_t* black_ppm = (ppm_t*)malloc(height * width * sizeof(ppm_t));

    black_ppm->height = height;
    black_ppm->width = width;
    black_ppm->image = (struct color**)malloc(height * sizeof(struct color*));

    for (int i = 0; i < height; i++) 
    {
        black_ppm->image[i] = (struct color*)malloc(width * sizeof(struct color));

        for (int j = 0; j < width; j++) 
        {
            black_ppm->image[i][j].red = 0;
            black_ppm->image[i][j].green = 0;
            black_ppm->image[i][j].blue = 0;
        }
    }
    return black_ppm;
}

/* free_ppm: free a ppm struct
 *
 * input: ppm to free
 */
void free_ppm(ppm_t *input)
{
    for (int i = 0; i < input->height; i++) 
    {
        free(input->image[i]);
    }
    free(input->image);
    free(input);
}

/* create_negative: create new negative ppm 
 *
 * input: ppm to negate
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *create_negative(ppm_t *input)
{
    ppm_t* negative = (ppm_t*)malloc(input->height * input->width * sizeof(ppm_t));
    negative->height = input->height;
    negative->width = input->width;
    negative->image = (struct color**)malloc(negative->height * sizeof(struct color*));

    for (int i = 0; i < negative->height; i++) 
    {
        negative->image[i] = (struct color*)malloc(negative->width * sizeof(struct color));

        for (int j = 0; j < negative->width; j++) 
        {
            negative->image[i][j].red = MAX_INTENSITY - input->image[i][j].red;
            negative->image[i][j].green = MAX_INTENSITY - input->image[i][j].green;
            negative->image[i][j].blue = MAX_INTENSITY - input->image[i][j].blue; 
        }
    }
    return negative;
}

/* create_greyscale: create new greyscale ppm 
 *
 * input: ppm to make grey
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *create_greyscale(ppm_t *input)
{
    ppm_t* greyscale = (ppm_t*)malloc(input->height * input->width * sizeof(ppm_t));
    greyscale->height = input->height;
    greyscale->width = input->width;
    
    greyscale->image = (struct color**)malloc(greyscale->height * sizeof(struct color*));

    for (int i = 0; i < greyscale->height; i++) 
    {
        greyscale->image[i] = (struct color*)malloc(greyscale->width * sizeof(struct color));

        for (int j = 0; j < greyscale->width; j++)
        {
            int average_RGB = ((77 * input->image[i][j].red) + (150 * input->image[i][j].green) + (29 * input->image[i][j].blue))/256;
            greyscale->image[i][j].red = average_RGB;
            greyscale->image[i][j].green = average_RGB;
            greyscale->image[i][j].blue = average_RGB; 
        }
    }
    return greyscale;
}


int max(int num1, int num2) 
{
    return (num1 > num2 ) ? num1 : num2;
}

int min(int num1, int num2) 
{
    return (num1 > num2 ) ? num2 : num1;
}

/* blur: create new blurred ppm 
 *
 * input: ppm to blur
 * size: size of area around a pixel to blur (an odd integer)
 *
 * Returns: a ppm_t (a pointer to a ppm struct)
 */
ppm_t *blur(ppm_t *input, int size)
{
    ppm_t* blur = (ppm_t*)malloc(input->height * input->width * sizeof(ppm_t));
    blur->height = input->height;
    blur->width = input->width;

    blur->image = (struct color**)malloc(blur->height * sizeof(struct color*));

    for (int i = 0; i < blur->height; i++)
    {
        blur->image[i] = (struct color*)malloc(blur->width * sizeof(struct color));

        for (int j = 0; j < blur->width; j++) 
        {
            int average_red_pixel = 0;
            int average_green_pixel = 0;
            int average_blue_pixel = 0;

            for (int k = max(0, i - size); k < min(blur->height, i + size + 1); k++) 
            {
                for (int l = max(0, j - size); l < min(blur->width, j + size + 1); l++) 
                {
                    average_red_pixel += input->image[i][j].red;
                    average_green_pixel += input->image[i][j].green;
                    average_blue_pixel += input->image[i][j].blue;

                    blur->image[i][j].red = average_red_pixel;
                    blur->image[i][j].green = average_green_pixel;
                    blur->image[i][j].blue = average_blue_pixel;
                }
            }
        }
    }
    return blur;
}
