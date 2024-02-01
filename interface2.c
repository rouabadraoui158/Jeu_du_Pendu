// interface2.c

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEXT_SIZE 28
#define TITLE_TEXT_COLOR 255, 255, 255, 255

static void renderText(const char* text, int x, int y, SDL_Color textColor, TTF_Font* font, SDL_Renderer* gRenderer);


static void renderText(const char* text, int x, int y, SDL_Color textColor, TTF_Font* font, SDL_Renderer* gRenderer) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (textSurface != NULL) {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (textTexture != NULL) {
            SDL_Rect renderRect = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(gRenderer, textTexture, NULL, &renderRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

