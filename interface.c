#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEXT_SIZE 28
#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 50
#define VERTICAL_SPACING 20
#define TITLE_BG_COLOR 50, 150, 200, 255 // Couleur de fond du titre (bleu clair)
#define TITLE_TEXT_COLOR 255, 255, 255, 255 // Couleur du texte du titre (blanc)

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
SDL_Texture* gHangmanImage = NULL;

void closeSDL() {
    SDL_DestroyTexture(gHangmanImage);
    gHangmanImage = NULL;

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

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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

void renderHangmanImage() {
    SDL_Rect hangmanImageRect = {(SCREEN_WIDTH - TEXT_SIZE * 14) / 2 + TEXT_SIZE * 14 + 20, SCREEN_HEIGHT / 8, 100, 100}; // Ajustez les coordonnées selon votre préférence
    SDL_RenderCopy(gRenderer, gHangmanImage, NULL, &hangmanImageRect);
}

int main() {
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return 1;
    }

    gHangmanImage = IMG_LoadTexture(gRenderer, "/home/molka/Bureau/autoformation/man.png");
    if (gHangmanImage == NULL) {
        printf("Failed to load image! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    int quit = 0;
    int difficultySelected = 0;
    int showDifficultyLevels = 0;
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
                    difficultySelected = 1;
                    showDifficultyLevels = !showDifficultyLevels;
                } else if (mouseX >= SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 && mouseX <= SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2 &&
                           mouseY >= SCREEN_HEIGHT / 2 + BUTTON_HEIGHT + VERTICAL_SPACING * 2 && mouseY <= SCREEN_HEIGHT / 2 + BUTTON_HEIGHT * 2 + VERTICAL_SPACING * 2) {
                    quit = 1; // Quitter la boucle principale
                } else {
                    difficultySelected = 0;
                    showDifficultyLevels = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
        SDL_RenderClear(gRenderer);

        SDL_Rect titleRect = { 0, SCREEN_HEIGHT / 8 - TEXT_SIZE / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 4 };
        SDL_Rect playButtonRect = { 0, SCREEN_HEIGHT / 2 - TEXT_SIZE / 2, BUTTON_WIDTH, BUTTON_HEIGHT };
        SDL_Rect difficultyButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + VERTICAL_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT };
        SDL_Rect quitButtonRect = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT + VERTICAL_SPACING * 2, BUTTON_WIDTH, BUTTON_HEIGHT };

        SDL_SetRenderDrawColor(gRenderer, TITLE_BG_COLOR);
        SDL_RenderFillRect(gRenderer, &titleRect);

        renderText("Hangman", (SCREEN_WIDTH - TEXT_SIZE * 14) / 2, SCREEN_HEIGHT / 8, (SDL_Color){TITLE_TEXT_COLOR});

        renderHangmanImage();

        int textWidth, textHeight;
        TTF_SizeText(gFont, "Difficulty", &textWidth, &textHeight);
        renderText("Difficulty", SCREEN_WIDTH / 2 - textWidth / 2, SCREEN_HEIGHT / 2 + VERTICAL_SPACING + BUTTON_HEIGHT / 4, (SDL_Color){0, 0, 0});
       
        TTF_SizeText(gFont, "Exit", &textWidth, &textHeight);
        renderText("Exit", SCREEN_WIDTH / 2 - textWidth / 2, SCREEN_HEIGHT / 2 + BUTTON_HEIGHT + VERTICAL_SPACING * 2 + BUTTON_HEIGHT / 4, (SDL_Color){0, 0, 0});

        if (difficultySelected && showDifficultyLevels) {
            // Affichage des niveaux de difficulté
            renderText("Easy", SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2 + VERTICAL_SPACING, SCREEN_HEIGHT / 2 + VERTICAL_SPACING, (SDL_Color){0, 0, 0});
            renderText("Medium", SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2 + VERTICAL_SPACING, SCREEN_HEIGHT / 2 + VERTICAL_SPACING * 2 + BUTTON_HEIGHT, (SDL_Color){0, 0, 0});
            renderText("Difficult", SCREEN_WIDTH / 2 + BUTTON_WIDTH / 2 + VERTICAL_SPACING, SCREEN_HEIGHT / 2 + VERTICAL_SPACING * 3 + BUTTON_HEIGHT * 2, (SDL_Color){0, 0, 0});
        }

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();
    return 0;
}
