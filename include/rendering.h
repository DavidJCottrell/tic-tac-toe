#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include "game_logic.h"
#include "constants.h"

int roundUpToMultipleOfEight(int v);

void draw_naught(SDL_Renderer *renderer, SDL_Point center, int radius);

void draw_cross(SDL_Renderer *renderer, int row, int column);

void draw_grid(SDL_Renderer *renderer);

void render_board(SDL_Renderer *renderer, GameState *state);

void draw_winning_line(SDL_Renderer *renderer, CellIndex winning_cells[3]);

#endif // RENDERING_H
