#ifndef GAME_H
#define GAME_H

#include <forge/forge_api.h>

#include "entity.h"

typedef enum GameState
{
    GAME_STATE_ACTIVE,
    GAME_STATE_MENU,
    GAME_STATE_WIN,
    GAME_STATE_LOSE,
    GAME_STATE_PAUSE
} GameState;

typedef struct Game
{
    MemoryArena *permanent_memory;
    MemoryArena *temporary_memory;
    GameState    state;
    V4F          viewport;
    Entity      *player;
} Game;

void game_init(void);
void game_destroy(void);
void game_update(f64 dt);
void game_draw(void);

#endif // GAME_H
