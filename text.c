#include "text.h"


SDL_Texture* create_texture(SDL_Renderer* renderer, TTF_Font* font, char text[], SDL_Color text_color)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, text_color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_FreeSurface(text_surface);

	return text_texture;
}

void render_texture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect button_rect)
{
	SDL_Rect text_rect = 
						{
							.x = button_rect.x + 2,	
							.y = button_rect.y + 2,	
							.w = button_rect.w - 4,	
							.h = button_rect.h - 4,	
						};
	SDL_RenderCopy(renderer, texture, NULL, &text_rect);
}

















