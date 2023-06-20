#ifndef GAME_H
#define GAME_H

#include <forge_base_types.h>
#include <forge_gfx.h>
#include <forge_vector2.h>
#include <forge_vector3.h>
#include <forge_vector4.h>

#include "entity.h"
#include "forge_input.h"
#include "forge_memory_arena.h"

typedef enum GameState {
    GAME_STATE_ACTIVE,
    GAME_STATE_MENU,
    GAME_STATE_WIN,
    GAME_STATE_LOSE
} GameState;

typedef struct Game {
    MemoryArena *memory;
    GameState state;

    Entity *bricks;
    u64 bricks_count;

    Entity *player;
} Game;

void game_init(Game *game, MemoryArena *memory);
void game_destroy(Game *game);
void game_update(Game *game, InputState *input, f64 dt);
void game_draw(Game *game, GFXState *gfx);
void game_add_brick(Game *game, Vector3 position, Vector2 size, Vector4 color);

#endif // GAME_H
