#include "image.h"


void apply_mask(Image *image, Image *mask)
{
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            if (!mask->pixels[x][y].r)
            {
                image->pixels[x][y].r = image->pixels[x][y].g
                    = image->pixels[x][y].b = 255;
            }
        }
    }
}