#include <stdio.h>

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "rendering.h"
#include "game_logic.h"
#include "input.h"
#include "constants.h"

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameState state;
} Game;

bool init_game(Game *game)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "Failed to init SDL: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow("Tic Tac Toe",
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    CELL_SIZE * 3, CELL_SIZE * 3,
                                    SDL_WINDOW_SHOWN);
    if (!game->window)
    {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer)
    {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    initialize_state(&game->state);
    return true;
}

void cleanup_game(Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

int main()
{
    Game game;
    if (!init_game(&game))
    {
        return 1;
    }

    while (game.state.is_running)
    {
        handle_events(&game.state);
        render_board(game.renderer, &game.state);
    }

    cleanup_game(&game);

    return 0;
}
