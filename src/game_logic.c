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
        for (int i = 0; i < 3; i++) {
            printf("Cell: (%d, %d)\n", state->winning_cells[i].col, state->winning_cells[i].row);
        }
    } else if (check_stalemate_condition(state)) {
        printf("Stalemate!\n");
    }
}

bool check_win_condition(GameState *state, Player player) {
    // Check for 3 connected vertically or horizontally
    for (int i = 0; i < 3; i++) {
        if (state->grid[i][0] == player && state->grid[i][1] == player && state->grid[i][2] == player) {
            state->winning_player = player;

            state->winning_cells[0] = (CellIndex) {i, 0};
            state->winning_cells[1] = (CellIndex) {i, 1};
            state->winning_cells[2] = (CellIndex) {i, 2};

            return true;
        }
        if (state->grid[0][i] == player && state->grid[1][i] == player && state->grid[2][i] == player) {
            state->winning_player = player;

            state->winning_cells[0] = (CellIndex) {0, i};
            state->winning_cells[1] = (CellIndex) {1, i};
            state->winning_cells[2] = (CellIndex) {2, i};

            return true;
        }
    }

    // Check for 3 connected diagonally
    if (state->grid[0][0] == player && state->grid[1][1] == player && state->grid[2][2] == player) {
        state->winning_player = player;

        state->winning_cells[0] = (CellIndex) {0, 0};
        state->winning_cells[1] = (CellIndex) {1, 1};
        state->winning_cells[2] = (CellIndex) {2, 2};

        return true;
    }
    if (state->grid[0][2] == player && state->grid[1][1] == player && state->grid[2][0] == player) {
        state->winning_player = player;

        state->winning_cells[0] = (CellIndex) {0, 2};
        state->winning_cells[1] = (CellIndex) {1, 1};
        state->winning_cells[2] = (CellIndex) {2, 0};

        return true;
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
