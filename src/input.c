#include "input.h"

int get_grid_position(int coord)
{
    if (coord < CELL_SIZE)
        return 0;
    else if (coord < CELL_SIZE * 2)
        return 1;
    else if (coord < CELL_SIZE * 3)
        return 2;
    return 0;
}

void handle_events(GameState *state)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        if (sdlEvent.type == SDL_QUIT)
        {
            state->is_running = false;
            return;
        }
        else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            int mouse_x = sdlEvent.button.x;
            int mouse_y = sdlEvent.button.y;

            const clicked_row = get_grid_position(mouse_y);
            const clicked_col = get_grid_position(mouse_x);

            if (state->grid[clicked_row][clicked_col] == EMPTY)
            {
                state->grid[clicked_row][clicked_col] = state->current_player;

                check_game_state(state);

                // Switch player
                state->current_player = state->current_player == PLAYER_X ? PLAYER_O : PLAYER_X;
            }
            else
            {
                printf("Invalid move!\n");
            }
        }
    }
}