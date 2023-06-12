#ifndef GAME_H
#define GAME_H

#include <forge_base_types.h>
#include <forge_gfx.h>
#include <forge_vector2.h>

#include "level.h"

typedef enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_LOSE
} GameState;

typedef struct Game {
    GameState state;
    Level *levels;
    u64 level_count;
    u64 level_index;

    GFXState *gfx;
} Game;

void game_init(Game *game);
void game_destroy(Game *game);
void game_update(Game *game, f64 dt);
void game_draw(Game *game);

#endif // GAME_H
