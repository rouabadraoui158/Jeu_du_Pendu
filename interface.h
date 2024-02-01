#ifndef INTERFACE_H
#define INTERFACE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

void renderText(const char* text, int x, int y, SDL_Color textColor);
void renderOption(SDL_Renderer* gRenderer, TTF_Font* gFont, const char* optionText, int optionNumber, int isSelected);


#endif

