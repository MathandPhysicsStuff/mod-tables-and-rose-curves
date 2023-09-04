#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "functions.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;


int main()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL2 video failed to initialize: \n", SDL_GetError());
    else printf("System is ready to go!\n");

    window = SDL_CreateWindow("Hello SDL",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED);

    Data d = 
    {
        .mod = 360,
        .timesTable = 1,
        .Xcenter = SCREEN_WIDTH/2,        
        .Ycenter = SCREEN_HEIGHT/2,
        .radius = 300,
        .red = 255, .green = 0, .blue = 0        
    };

    SDL_bool running = SDL_TRUE;
    while (running == SDL_TRUE)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = SDL_FALSE;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_LEFT:
                        d.timesTable -= 1;
                        break;

                    case SDLK_RIGHT:
                        d.timesTable += 1;
                        break;

                    case SDLK_UP:
                        d.mod += 1;
                        break;

                    case SDLK_DOWN:
                        if (d.mod >= 1)
                        {
                            d.mod -= 1;
                        }
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 8, 8, 8, 255);
        SDL_RenderClear(renderer);

        renderFunction(renderer, &d);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



























