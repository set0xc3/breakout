#ifndef GAME_H
#define GAME_H

#include <forge/debug/debug.h>
#include <forge/forge_api.h>

#include "entity.h"

typedef enum
{
    GameState_Active,
    GameState_Menu,
    GameState_Win,
    GameState_Lose,
    GameState_Pause
} GameState;

typedef struct
{
    Entity *base;
    f32     radius;
    b32     stuck;
} Ball;

typedef struct
{
    MemoryArena *permanent_memory;
    MemoryArena *temporary_memory;

    GameState state;
    V4F       viewport;
    Entity   *player;
    Ball     *ball;
} Game;

void game_init(void);
void game_destroy(void);
void game_update(f64 dt);
void game_draw(void);

void game_ball_move(f32 dt, V4F viewport);
void game_reset(void);

#endif // GAME_H
