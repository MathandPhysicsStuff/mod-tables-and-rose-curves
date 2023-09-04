#include "functions.h"


void renderFunction(SDL_Renderer* renderer, Data* d)
{
    //number of points
    double t = 0;
    double tau = 6.2831852;
    double step = tau / (double)d->mod;

    SDL_Rect point;
    point.w = 1;
    point.h = 1;
    
    while (t < tau)
    {
        point.x = d->Xcenter + d->radius*cos(t); 
        point.y = d->Ycenter + d->radius*sin(t);

        SDL_SetRenderDrawColor(renderer, d->red, d->green, d->blue, 255);
        SDL_RenderDrawRect(renderer, &point);

        t += step;
    }
}


























