#include "functions.h"


void renderFunction(SDL_Renderer* renderer, Data* d)
{
    //number of points
    double t = 0;
    double tau = 6.2831852;
    double step = tau / (double)d->mod;
    double x0, y0, x1, y1;

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


void hsvColoring(int* color, double h, double s, double v)
{

    double r, g, b; //red green blue
    double c, x, m;

    h = (int)h % 359;

    c = s*v;
    x = c*(1 - fabs(fmod(h/60, 2) - 1));
    m = v - c;

    if (0 <= h && h < 60){r = c, g = x, b = 0;}
    else if (60 <= h && h < 120){r = x, g = c, b = 0;}
    else if (120 <= h && h < 180){r = 0, g = c, b = x;}
    else if (180 <= h && h < 240){r = 0, g = x, b = c;}
    else if (240 <= h && h < 300){r = x, g = 0, b = c;}
    else if (300 <= h && h < 360){r = c, g = 0, b = x;}

    color[0] = (r+m)*(255*v);
    color[1] = (g+m)*(255*v);
    color[2] = (b+m)*(255*v);

}























