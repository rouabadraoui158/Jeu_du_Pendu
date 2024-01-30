#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEXT_SIZE 28
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define VERTICAL_SPACING 20
#define TITLE_BG_COLOR 50, 150, 200, 255 // Title background color (light blue)
#define TITLE_TEXT_COLOR 255, 255, 255, 255 // Title text color (white)
#define BUTTON_BORDER_COLOR 0, 0, 0, 255 // Button border color (black)

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;

void closeSDL() {
    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    TTF_Quit();
    SDL_Quit();
}

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    gFont = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", TEXT_SIZE);
    if (gFont == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

void renderText(const char* text, int x, int y, SDL_Color textColor) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    } else {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (textTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        } else {
            SDL_Rect renderRect = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(gRenderer, textTexture, NULL, &renderRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

void renderButtonWithBorder(const char* text, int x, int y, int width, int height, SDL_Color bgColor, SDL_Color textColor, SDL_Color borderColor) {
    // Render button background
    SDL_Rect buttonRect = { x, y, width, height };
    SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(gRenderer, &buttonRect);

    // Render button border
    SDL_SetRenderDrawColor(gRenderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(gRenderer, &buttonRect);

    // Render button text
    int textWidth, textHeight;
    TTF_SizeText(gFont, text, &textWidth, &textHeight);
    renderText(text, x + (width - textWidth) / 2, y + (height - textHeight) / 2, textColor);
}

int main() {
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return 1;
    }

    int quit = 0;
    int startClicked = 0;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 && mouseX <= SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2 &&
                    mouseY >= SCREEN_HEIGHT / 2 + VERTICAL_SPACING && mouseY <= SCREEN_HEIGHT / 2 + VERTICAL_SPACING + BUTTON_HEIGHT) {
                    startClicked = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        SDL_Rect titleRect = { 0, SCREEN_HEIGHT / 8 - TEXT_SIZE / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 4 };
        SDL_Rect startButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + VERTICAL_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT };
        SDL_Rect quitButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT + VERTICAL_SPACING * 2, BUTTON_WIDTH, BUTTON_HEIGHT };

        SDL_SetRenderDrawColor(gRenderer, TITLE_BG_COLOR);
        SDL_RenderFillRect(gRenderer, &titleRect);

        renderText("Welcome to Hangman!", (SCREEN_WIDTH - TEXT_SIZE * 14) / 2, SCREEN_HEIGHT / 8, (SDL_Color){TITLE_TEXT_COLOR});

        renderButtonWithBorder("Start", SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + VERTICAL_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT,
                               (SDL_Color){TITLE_BG_COLOR}, (SDL_Color){0, 0, 0}, (SDL_Color){BUTTON_BORDER_COLOR});

        renderButtonWithBorder("Exit", SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT + VERTICAL_SPACING * 2, BUTTON_WIDTH, BUTTON_HEIGHT,
                               (SDL_Color){TITLE_BG_COLOR}, (SDL_Color){0, 0, 0}, (SDL_Color){BUTTON_BORDER_COLOR});

        if (startClicked) {
            printf("Start button clicked! Implement code to move to another page.\n");
            // Add code to move to another page
        }

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();
    return 0;
}

