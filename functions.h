#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

typedef struct Data 
{
    
    int mod;
    double timesTable;

    double Xcenter;
    double Ycenter;

    double radius;

    int red, green, blue;

} Data;

void renderFunction(SDL_Renderer* renderer, Data* d);

void hsvColoring(int* color, double h, double s, double v);

#endif
