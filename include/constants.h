#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdint.h>

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
#define CELL_SIZE 100

extern uint32_t lastFrameTime;

#endif // CONSTANTS_H