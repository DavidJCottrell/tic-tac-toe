#include "rendering.h"

int roundUpToMultipleOfEight(int v) {
    return (v + (8 - 1)) & -8;
}

void draw_naught(SDL_Renderer *renderer, SDL_Point center, int radius) {
    const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
    SDL_Point points[arrSize];
    int drawCount = 0;

    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        // Each of the following renders an octant of the circle
        points[drawCount + 0] = (SDL_Point) {center.x + x, center.y - y};
        points[drawCount + 1] = (SDL_Point) {center.x + x, center.y + y};
        points[drawCount + 2] = (SDL_Point) {center.x - x, center.y - y};
        points[drawCount + 3] = (SDL_Point) {center.x - x, center.y + y};
        points[drawCount + 4] = (SDL_Point) {center.x + y, center.y - x};
        points[drawCount + 5] = (SDL_Point) {center.x + y, center.y + x};
        points[drawCount + 6] = (SDL_Point) {center.x - y, center.y - x};
        points[drawCount + 7] = (SDL_Point) {center.x - y, center.y + x};

        drawCount += 8;

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }

    SDL_RenderDrawPoints(renderer, points, drawCount);
}

void draw_cross(SDL_Renderer *renderer, int row, int column) {
    int padding = 20;
    SDL_RenderDrawLine(renderer,
                       (row * CELL_SIZE) + padding, (column * CELL_SIZE) + padding,
                       (row * CELL_SIZE + CELL_SIZE) - padding, (column * CELL_SIZE + CELL_SIZE) - padding);
    SDL_RenderDrawLine(renderer,
                       (row * CELL_SIZE) + padding, (column * CELL_SIZE + CELL_SIZE) - padding,
                       (row * CELL_SIZE + CELL_SIZE) - padding, (column * CELL_SIZE) + padding);
}

void draw_grid(SDL_Renderer *renderer) {
    SDL_RenderDrawLine(renderer,
                       CELL_SIZE, 0,
                       CELL_SIZE, CELL_SIZE * 3);
    SDL_RenderDrawLine(renderer,
                       CELL_SIZE * 2, 0,
                       CELL_SIZE * 2, CELL_SIZE * 3);
    SDL_RenderDrawLine(renderer,
                       0, CELL_SIZE,
                       CELL_SIZE * 3, CELL_SIZE);
    SDL_RenderDrawLine(renderer,
                       0, CELL_SIZE * 2,
                       CELL_SIZE * 3, CELL_SIZE * 2);
}

void draw_winning_line(SDL_Renderer *renderer, CellIndex winning_cells[3]) {
    // Calculate the center point of the first cell
    int x_center_start = winning_cells[0].col * CELL_SIZE + CELL_SIZE / 2;
    int y_center_start = winning_cells[0].row * CELL_SIZE + CELL_SIZE / 2;

    // Calculate the center point of the last cell
    int x_center_end = winning_cells[2].col * CELL_SIZE + CELL_SIZE / 2;
    int y_center_end = winning_cells[2].row * CELL_SIZE + CELL_SIZE / 2;

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_RenderDrawLine(renderer,
                       x_center_start, y_center_start,
                       x_center_end, y_center_end);
}

void render_board(SDL_Renderer *renderer, GameState *state) {
    const int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
        SDL_Delay(timeToWait);

    lastFrameTime = SDL_GetTicks();

    // Black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw grid
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    draw_grid(renderer);

    // Draw player choices
    for (int col = 0; col < 3; col++) {
        for (int row = 0; row < 3; row++) {
            if (state->grid[col][row] == PLAYER_X) {
                draw_cross(renderer, row, col);
            } else if (state->grid[col][row] == PLAYER_O) {
                SDL_Point center = {(row * CELL_SIZE) + (CELL_SIZE / 2), (col * CELL_SIZE) + (CELL_SIZE / 2)};
                draw_naught(renderer, center, CELL_SIZE / 3);
            }
        }
    }

    if (state->winning_player != EMPTY) {
        draw_winning_line(renderer, state->winning_cells);
    }

    // Render
    SDL_RenderPresent(renderer);
}
