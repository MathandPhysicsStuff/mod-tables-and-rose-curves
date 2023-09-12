#include "functions.h"


void renderModFunction(SDL_Renderer* renderer, Data* d)
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


void renderRoseFunction(SDL_Renderer* renderer, RoseData* d)
{
    int i;
    int loop = 360 * d->d;
    double k = (double)d->n / (double)d->d;
    double x0, y0, x1, y1, r0, r1, t0, t1;
    double map = 3.1415926 / 180.0;


    for (i = 0; i < 361; i++)
    {
        t0 = map * (double)i * d->a;
        t1 = map * (double)(i+1) * d->a;

        r0 = d->radius*sin(k * t0);
        r1 = d->radius*sin(k * t1);

        x0 = d->Xcenter + r0*cos(t0);
        y0 = d->Ycenter + r0*sin(t0);

        x1 = d->Xcenter + r1*cos(t1);
        y1 = d->Ycenter + r1*sin(t1);
 
        SDL_SetRenderDrawColor(renderer, d->red, d->green, d->blue, 255);
        SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
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

SDL_bool eventMod(SDL_Event event, Data* d, SDL_bool show)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:
                d->timesTable -= 1;
                break;

            case SDLK_RIGHT:
                d->timesTable += 1;
                break;

            case SDLK_UP:
                d->mod += 1;
                break;

            case SDLK_DOWN:
                if (d->mod >= 1) d->mod -= 1;
                break;

            case SDLK_s:
                if (show == SDL_FALSE) show = SDL_TRUE;
                else show = SDL_FALSE;
                break;
        }
    }
    return show;
}

SDL_bool eventRose(SDL_Event event, RoseData* d, SDL_bool show)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:
                if (d->d > 1) d->d -= 1;
                break;

            case SDLK_RIGHT:
                d->d += 1;
                break;

            case SDLK_UP:
                d->n += 1;
                break;

            case SDLK_DOWN:
                if (d->n > 1) d->n -= 1;
                break;

            case SDLK_s:
                if (show == SDL_FALSE) show = SDL_TRUE;
                else show = SDL_FALSE;
                break;

            case SDLK_a:
                if (d->a > 1) d->a -= 1;
                break;

            case SDLK_d:
                d->a += 1;
                break;
        }
    }
    return show;
}



















