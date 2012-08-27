#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "mandelbrot.h"

Mandelbrot brot_create(int pixelWidth, int pixelHeight, int repeats, double x1, double y1, double x2, double y2)
{
    Mandelbrot brot = (Mandelbrot) malloc(sizeof(Mandelbrot_Data));

    brot->x1 = x1;
    brot->y1 = y1;

    brot->x2 = x2;
    brot->y2 = y2;

    brot->pixelWidth = pixelWidth;
    brot->pixelHeight = pixelHeight;

    brot->pixels = (int**) malloc(sizeof(int*) * brot->pixelWidth);

    brot->repeats = repeats;

    // Assign the memory for the 2D array
    // Actually done as an array of pointers to arrays of ints
    int i;
    for (i = 0; i < brot->pixelWidth; i++) {
        brot->pixels[i] = (int*) malloc(sizeof(int*) * brot->pixelHeight);
    }

    return brot;
}

Mandelbrot brot_recreate(Mandelbrot brot, double x1, double y1, double x2, double y2)
{
    brot->x1 = x1;
    brot->y1 = y1;

    brot->x2 = x2;
    brot->y2 = y2;

    return brot;
}

Mandelbrot brot_calculate(Mandelbrot brot)
{
    int xPos, yPos;

    for (xPos = 0; xPos < brot->pixelWidth; xPos++) {
        for (yPos = 0; yPos < brot->pixelHeight; yPos++) {
            brot->pixels[xPos][yPos] = brot_pixel_coords(brot, xPos, yPos);
        }
    }

    return brot;
}

int brot_pixel_coords(Mandelbrot brot, int xPos, int yPos)
{
    double xVal, yVal;

    xVal = (((brot->x2 - brot->x1)/brot->pixelWidth) * xPos) + brot->x1;

    yVal = (((brot->y2 - brot->y1)/brot->pixelHeight) * yPos) + brot->y1;

    // Need to work out exactly how the limit should be calculated
    // Not using it until I have
    //float limit = (xVal * xVal) + (yVal * yVal);

    return brot_calc_escape(xVal, yVal, 0.0, brot->repeats);

}

int brot_calc_escape(double xPos, double yPos, double limit, int depth)
{
    double x = 0;
    double y = 0;

    double temp = 0;

    int iteration = 0;

    while ( ((x*x + y*y) < 4) && (iteration < depth) ) {

        temp = x*x - y*y + xPos;

        y = 2*x*y + yPos;

        x = temp;

        iteration++;
    }

    return iteration;

}

void brot_cleanup(Mandelbrot brot)
{
    int i;

    for (i = 0; i < brot->pixelWidth; i++) {
        free(brot->pixels[i]);
    }

    free(brot->pixels);

    free(brot);
}


