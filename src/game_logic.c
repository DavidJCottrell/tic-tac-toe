#include "game_logic.h"

void initialize_state(GameState *state) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            state->grid[i][j] = EMPTY;

    state->current_player = PLAYER_X;
    state->winning_player = EMPTY;
    state->is_running = true;
}

void check_game_state(GameState *state) {
    if (check_win_condition(state, state->current_player)) {
        printf("Player: %c has won!\n", state->winning_player == PLAYER_X ? 'X' : 'O');
    } else if (check_stalemate_condition(state)) {
        printf("Stalemate!\n");
    }
}

bool check_win_condition(GameState *state, Player player) {
    int count = 0;

    // Check for 3 in the same row
    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 3; row++) {
            if (state->grid[col][row] == player)
                count++;
            if (count == 3) {
                state->winning_player = player;
                return true;
            }
        }
        count = 0;
    }

    // Check for 3 in the same column
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (state->grid[col][row] == player)
                count++;
            if (count == 3) {
                state->winning_player = player;
                return true;
            }
        }
        count = 0;
    }

    // Check for horizontal win
    if (state->grid[1][1] == player) {
        if (state->grid[0][0] == player && state->grid[2][2] == player) {
            state->winning_player = player;
            return true;
        }
        if (state->grid[0][2] == player && state->grid[2][0] == player) {
            state->winning_player = player;
            return true;
        }
    }

    return false;
}

bool check_stalemate_condition(GameState *state) {
    int count = 0;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (state->grid[col][row] != EMPTY)
                count++;
    return count == 9 && state->winning_player == EMPTY;
}
