#define SDL_MAIN_HANDLED

#include <stdio.h> // printf

#include "game_window.h"

int main(int argc, char* argv[]) {
    printf("Das Demo-Programm wird geladen...\n");
    printf("Arguments: %i : %s", argc, argv[0]);
    for (int i = 1; i < argc; ++i)
        printf(" %s", argv[i]);
    printf("\n");

    GameWindow *game_window = new GameWindow(800, 600, false);
    delete game_window;
    game_window = nullptr;

    // Shutdown SDL
    SDL_Quit();
    return 0;
}
