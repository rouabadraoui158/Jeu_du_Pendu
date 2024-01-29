#include <SDL.h>
#include <SDL_ttf.h>

int main() {
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        printf("SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont(NULL, 36); // Use the default system font

    if (!font) {
        printf("Error: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "SDL_ttf test", (SDL_Color){255, 255, 255});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_Rect dstRect = {100, 100, textSurface->w, textSurface->h};

    // Your rendering logic here

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);

    TTF_Quit();
    SDL_Quit();
    return 0;
}

