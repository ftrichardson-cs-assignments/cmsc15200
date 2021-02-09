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

    for (int i = 0; i < height; i++)
    {
        black_ppm->image[i] = (struct color*)malloc(width * sizeof(struct color));

        for (int j = 0; j < width; j++)
        {
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
    ppm_t* negative = new_ppm(input->height, input->width);
    
    for (int i = 0; i < negative->height; i++) 
    {
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
    ppm_t* greyscale = new_ppm(input->height, input->width);
    
    for (int i = 0; i < greyscale->height; i++)
    {
        for (int j = 0; j < greyscale->width; j++)
        {
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

void blur_pixel(ppm_t *input, ppm_t *blur, int size, int a[])
{
    int sum_red_pixels = 0, sum_green_pixels = 0, sum_blue_pixels = 0;
	int num_pixels = 0;
      
    for (int k = a[0] - (((size + 1) / 2) - 1); k < a[0] + (((size + 1) / 2) - 1) + 1; k++)
    {
        for (int l = a[1] - (((size + 1) / 2) - 1); l < a[1] + (((size + 1) / 2) - 1) + 1; l++)
        {
			/* This handles edge cases along rows */
          	if (k >= 0 && k < blur->height) 
          	{
				/* This handles edge cases along columns */
            	if (l >= 0 && l < blur->width) 
            	{
              		sum_red_pixels += input->image[k][l].red;
              		sum_green_pixels += input->image[k][l].green;
              		sum_blue_pixels += input->image[k][l].blue;
              		num_pixels++;
            	}
          	}
        }
    }
    blur->image[a[0]][a[1]].red = sum_red_pixels/num_pixels;
    blur->image[a[0]][a[1]].green = sum_green_pixels/num_pixels;
    blur->image[a[0]][a[1]].blue = sum_blue_pixels/num_pixels;
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
  	ppm_t* blur = new_ppm(input->height, input->width);
  
  	for (int i = 0; i < blur->height; i++)
  	{
    	for (int j = 0; j < blur->width; j++) 
    	{
            int pixel_location[] = {i, j};
      		blur_pixel(input, blur, size, pixel_location);
    	}
  	}
  	return blur;
}