#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
    EMPTY,
    PLAYER_X,
    PLAYER_O
} Player;

typedef struct {
    Player grid[3][3];
    Player current_player;
    Player winning_player;
    bool is_running;
} GameState;

void initialize_state(GameState *state);

void check_game_state(GameState *state);

bool check_win_condition(GameState *state, Player player);

bool check_stalemate_condition(GameState *state);

#endif // GAME_LOGIC_H
