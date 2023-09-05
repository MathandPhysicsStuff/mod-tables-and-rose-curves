#include <stdio.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "functions.h"
#include "text.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 760;
const int SCREEN_HEIGHT = 720;


int main()
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL2 video failed to initialize: \n", SDL_GetError());
    else printf("System is ready to go!\n");
    if (TTF_Init() == -1) printf("Could not initalize SDL2_ttf, error:\n", TTF_GetError());

    window = SDL_CreateWindow("Hello SDL",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED);

    SDL_Texture *mod_text, *timesTable_text;
    SDL_Color text_color = { 220, 220, 220 };

    int mod_number;
    double timesTable_number;
    char mod_str[24];
    char timesTable_str[24];
    SDL_bool showText = SDL_TRUE;

    SDL_Rect modPosition_rect = { 5, 5, 120, 20};
    SDL_Rect timesTablePosition_rect = { 5, 25, 160, 24};

    Data d = 
    {
        .mod = 720,
        .timesTable = 0,
        .Xcenter = SCREEN_WIDTH/2,        
        .Ycenter = SCREEN_HEIGHT/2,
        .radius = 360,
        .red = 255, .green = 0, .blue = 0        
    };

    int color[3];

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

                    case SDLK_s:
                        if (showText == SDL_TRUE) showText = SDL_FALSE;
                        else showText = SDL_TRUE;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 8, 8, 8, 255);
        SDL_RenderClear(renderer);

        //d.timesTable += 0.05;

        hsvColoring(color, d.timesTable, 1, 1);
        d.red = color[0];
        d.green = color[1];
        d.blue = color[2];

        renderFunction(renderer, &d);

        mod_number = d.mod;
        timesTable_number = d.timesTable;
        
        if (showText == SDL_TRUE)
        {
            TTF_Font* font = TTF_OpenFont("DejaVuMathTeXGyre.ttf", 64);

            char render_mod[24] = "mod: ";
            char render_timesTable[24] = "times table: ";

            sprintf(mod_str, "%d", mod_number);
            sprintf(timesTable_str, "%lf", timesTable_number);

            strncat(render_mod, mod_str, 24 - strlen(render_mod) - 1);
            strncat(render_timesTable, timesTable_str, 24 - strlen(render_timesTable) - 1);

            mod_text = create_texture(renderer, font, render_mod, text_color);
            timesTable_text = create_texture(renderer, font, render_timesTable, text_color);

            TTF_CloseFont(font);

            render_texture(renderer, mod_text, modPosition_rect);
            render_texture(renderer, timesTable_text, timesTablePosition_rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



























