#include <stdlib.h>
#include <stdio.h>

#include "util.h"
#include "images.h"

/*Constant for create_negative()*/
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

    for (int i = 0; i < height; i++) {
        black_ppm->image[i] = (struct color*)malloc(width * sizeof(struct color));

        for (int j = 0; j < width; j++) {
			/* Every value is zero for each pixel in black PPM */
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
    for (int i = 0; i < input->height; i++) {
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
    ppm_t* negative = new_ppm(input->height, input->width);
    
    for (int i = 0; i < negative->height; i++) {
        for (int j = 0; j < negative->width; j++) {
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
    ppm_t* greyscale = new_ppm(input->height, input->width);
    
    for (int i = 0; i < greyscale->height; i++) {
        for (int j = 0; j < greyscale->width; j++) {
            int avg_RGB = ((77 * input->image[i][j].red) + 
                          (150 * input->image[i][j].green) + 
                          (29 * input->image[i][j].blue))/256;
        
            greyscale->image[i][j].red = avg_RGB;
            greyscale->image[i][j].green = avg_RGB;
            greyscale->image[i][j].blue = avg_RGB;
        }
    }
    return greyscale;
}

/* blur_pixel: blurs individual pixel according to size parameter
 * (helper to blur function)
 * 
 * input: comparison ppm to set RGB values for blur
 * blur: ppm to blur
 * size: size of area around a pixel to blur (an odd integer
 * pixel: array representing location of individual pixel
 *
 */
void blur_pixel(ppm_t *input, ppm_t *blurred_ppm, int size, int pixel[])
{
    int sum_red_pixels = 0;
    int sum_green_pixels = 0;
    int sum_blue_pixels = 0;

    int num_pixels = 0;
  
    for (int k = pixel[0] - (((size + 1) / 2) - 1); k < pixel[0] + (((size + 1) / 2) - 1) + 1; k++) {
        for (int l = pixel[1] - (((size + 1) / 2) - 1); l < pixel[1] + (((size + 1) / 2) - 1) + 1; l++) {
        /* This handles edge cases along rows */
            if (k >= 0 && k < blurred_ppm->height) {
                /* This handles edge cases along columns */
                if (l >= 0 && l < blurred_ppm->width) {
                    sum_red_pixels += input->image[k][l].red;
                    sum_green_pixels += input->image[k][l].green;
                    sum_blue_pixels += input->image[k][l].blue;
                    num_pixels++;
                }
            }
        }
    }
    blurred_ppm->image[pixel[0]][pixel[1]].red = sum_red_pixels/num_pixels;
    blurred_ppm->image[pixel[0]][pixel[1]].green = sum_green_pixels/num_pixels;
    blurred_ppm->image[pixel[0]][pixel[1]].blue = sum_blue_pixels/num_pixels;
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
  	ppm_t* blurred_ppm = new_ppm(input->height, input->width);
  
  	for (int i = 0; i < blurred_ppm->height; i++) {
    	for (int j = 0; j < blurred_ppm->width; j++) {
            int pixel[] = {i, j};
      		blur_pixel(input, blurred_ppm, size, pixel);
    	}
  	}
  	return blurred_ppm;
}