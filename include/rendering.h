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

#endif // RENDERING_H