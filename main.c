#include <stdio.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "functions.h"
#include "text.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

typedef enum Curve 
{
    MOD,
    ROSE
} Curve;

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

    SDL_Texture *mod_text, *timesTable_text, *n_text, *d_text, *k_text, *step_text;
    SDL_Color text_color = { 220, 220, 220 };

    int mod_number;
    double timesTable_number;
    char mod_str[24];
    char timesTable_str[24];
    
    int n_number;
    int d_number; 
    int step_number;
    double k_number;
    char n_str[24];
    char d_str[24];
    char k_str[24];
    char step_str[24];

    SDL_bool showText = SDL_TRUE;

    SDL_Rect modPosition_rect = { 5, 5, 120, 20};
    SDL_Rect timesTablePosition_rect = { 5, 25, 160, 24};

    SDL_Rect nPosition_rect = { 5, 5, 120, 20};
    SDL_Rect dPosition_rect = { 5, 25, 160, 24};
    SDL_Rect kPosition_rect = { 5, 50, 160, 24};
    SDL_Rect stepPosition_rect = { 5, 75, 160, 24};

    Data d = 
    {
        .mod = 720,
        .timesTable = 0,
        .Xcenter = SCREEN_WIDTH/2,        
        .Ycenter = SCREEN_HEIGHT/2,
        .radius = 300,
        .red = 255, .green = 0, .blue = 0        
    };

    RoseData rd =
    {
        .n = 2,
        .d = 1,
        .a = 39,
        .points = 720,
        .Xcenter = SCREEN_WIDTH/2,        
        .Ycenter = SCREEN_HEIGHT/2,
        .radius = 300,
        .red = 255, .green = 0, .blue = 0        
    };

    Curve curve = ROSE;

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

            if (curve == MOD)
            {
                showText = eventMod(event, &d, showText);
            }
            else if (curve == ROSE)
            {
                showText = eventRose(event, &rd, showText);
            }
        }

        SDL_SetRenderDrawColor(renderer, 8, 8, 8, 255);
        SDL_RenderClear(renderer);

        //d.timesTable += 0.05;
        
        if (curve == MOD)
        {
            hsvColoring(color, d.timesTable, 1, 1);
            d.red = color[0];
            d.green = color[1];
            d.blue = color[2];
        }
        else if (curve == ROSE)
        {
            hsvColoring(color, rd.a, 1, 1);
            rd.red = color[0];
            rd.green = color[1];
            rd.blue = color[2];
        }
        
        if (curve == MOD) renderModFunction(renderer, &d);
        else if (curve == ROSE) renderRoseFunction(renderer, &rd);

        mod_number = d.mod;
        timesTable_number = d.timesTable;

        n_number = rd.n;
        d_number = rd.d;
        step_number = rd.a;
        k_number = (double)rd.n / (double)rd.d;
        
        if (showText == SDL_TRUE)
        {
            TTF_Font* font = TTF_OpenFont("DejaVuMathTeXGyre.ttf", 64);
            
            if (curve == MOD)
            {
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

            else if (curve == ROSE)
            {
                char render_n[24] = "numerator: ";
                char render_d[24] = "denominator: ";
                char render_k[24] = "k = n/d: ";
                char render_step[24] = "degree step: ";

                sprintf(n_str, "%d", n_number);
                sprintf(d_str, "%d", d_number);
                sprintf(step_str, "%d", step_number);
                sprintf(k_str, "%lf", k_number);

                strncat(render_n, n_str, 24 - strlen(render_n) - 1);
                strncat(render_d, d_str, 24 - strlen(render_d) - 1);
                strncat(render_k, k_str, 24 - strlen(render_k) - 1);
                strncat(render_step, step_str, 24 - strlen(render_step) - 1);

                n_text = create_texture(renderer, font, render_n, text_color);
                d_text = create_texture(renderer, font, render_d, text_color);
                k_text = create_texture(renderer, font, render_k, text_color);
                step_text = create_texture(renderer, font, render_step, text_color);

                TTF_CloseFont(font);

                render_texture(renderer, n_text, nPosition_rect);
                render_texture(renderer, d_text, dPosition_rect);
                render_texture(renderer, k_text, kPosition_rect);
                render_texture(renderer, step_text, stepPosition_rect);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}



























