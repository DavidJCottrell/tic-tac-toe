#include "game_logic.h"

void initialize_state(GameState *state)
{
    for (int col = 0; col < 3; col++)
        for (int row = 0; row < 3; row++)
            state->grid[col][row] = EMPTY;

    state->current_player = PLAYER_X;
    state->winning_player = EMPTY;
    state->is_running = true;
}

void check_game_state(GameState *state)
{
    if (check_win_condition(state, state->current_player))
    {
        printf("Player: %c has won!\n", state->winning_player == PLAYER_X ? 'X' : 'O');
    }
    else if (check_stalemate_condition(state))
    {
        printf("Stalemate!\n");
    }
}

bool check_win_condition(GameState *state, Player player)
{
    // Check for 3 connected vertically or horizontally
    for (int col = 0; col < 3; col++)
    {
        if (state->grid[col][0] == player && state->grid[col][1] == player && state->grid[col][2] == player)
        {
            state->winning_player = player;

            state->winning_cells[0] = (CellIndex){col, 0};
            state->winning_cells[1] = (CellIndex){col, 1};
            state->winning_cells[2] = (CellIndex){col, 2};

            return true;
        }
        if (state->grid[0][col] == player && state->grid[1][col] == player && state->grid[2][col] == player)
        {
            state->winning_player = player;

            state->winning_cells[0] = (CellIndex){0, col};
            state->winning_cells[1] = (CellIndex){1, col};
            state->winning_cells[2] = (CellIndex){2, col};

            return true;
        }
    }

    // Check for 3 connected diagonally
    if (state->grid[0][0] == player && state->grid[1][1] == player && state->grid[2][2] == player)
    {
        state->winning_player = player;

        state->winning_cells[0] = (CellIndex){0, 0};
        state->winning_cells[1] = (CellIndex){1, 1};
        state->winning_cells[2] = (CellIndex){2, 2};

        return true;
    }
    if (state->grid[0][2] == player && state->grid[1][1] == player && state->grid[2][0] == player)
    {
        state->winning_player = player;

        state->winning_cells[0] = (CellIndex){0, 2};
        state->winning_cells[1] = (CellIndex){1, 1};
        state->winning_cells[2] = (CellIndex){2, 0};

        return true;
    }

    return false;
}

bool check_stalemate_condition(GameState *state)
{
    int count = 0;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (state->grid[col][row] != EMPTY)
                count++;
    return count == 9 && state->winning_player == EMPTY;
}
