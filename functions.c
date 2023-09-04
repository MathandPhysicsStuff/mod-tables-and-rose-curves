#include "functions.h"


void renderFunction(SDL_Renderer* renderer, Data* d)
{
    //number of points
    double t = 0;
    double tau = 6.2831852;
    double step = tau / (double)d->mod;
    double x0, y0, x1, y1, r;

    while (t < tau)
    {
        x0 = d->Xcenter + d->radius*cos(t); 
        y0 = d->Ycenter + d->radius*sin(t);

        x1 = d->Xcenter + d->radius*cos(t * d->timesTable); 
        y1 = d->Ycenter + d->radius*sin(t * d->timesTable);


        SDL_SetRenderDrawColor(renderer, d->red, d->green, d->blue, 255);
        SDL_RenderDrawLine(renderer, x0, y0, x1, y1);

        t += step;
    }
}


























