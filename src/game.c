#include <forge.h>
#include <forge_asset.h>
#include <forge_base_types.h>
#include <forge_gfx.h>
#include <forge_input.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "forge_vector3.h"
#include "forge_vector4.h"
#include "game.h"

global_variable Vector4 colors[] = {
    0.0f, 0.0f,   0.0f, 255.0f, 255.0f, 0.0f, 0.0f,   255.0f,
    0.0f, 255.0f, 0.0f, 255.0f, 0.0f,   0.0f, 255.0f, 255.0f,
};

global_variable u32 map[4][4] = {
    1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

void game_init(Game *game, MemoryArena *memory) {
    game->memory = memory;
    game->bricks = arena_push_zero(game->memory, 256 * sizeof(Entity));
    game->player = arena_push_zero(game->memory, sizeof(Entity));

    Entity *player = game->player;
    player->position = v3(0.0f, 500.0f, 0.0f);
    player->size = v2(100.0f, 100.0f);
    player->color = v4(0.0f, 255.0f, 0.0f, 0.0f);

    for (u64 i = 0; i < ArrayCount(map); i += 1) {
        for (u64 j = 0; j < ArrayCount(map); j += 1) {
            if (map[i][j]) {
                u32 row = j * 100.0f;
                u32 colum = i * 100.0f;
                game_add_brick(game, v3(row, colum, 0.0f), v2(100.0f, 100.0f),
                               colors[map[i][j]]);
            }
        }
    }
}

void game_destroy(Game *game) {}

void game_update(Game *game, InputState *input, f64 dt) {
    if (input_key_up(input, KEY_CODE_ESCAPE)) {
        game->state = game->state == GAME_STATE_ACTIVE ? GAME_STATE_MENU
                                                       : GAME_STATE_ACTIVE;
    }
}

void game_draw(Game *game, GFXState *gfx) {
    switch (game->state) {
    case GAME_STATE_ACTIVE:
        gfx_draw_fill_rect(gfx, v3(0.0f, 0.0f, 0.0f), v2(800.0f, 600.0f),
                           v4(128.0f, 128.0f, 128.0f, 255.0f));

        Entity *entities = game->bricks;
        for (u64 index = 0; index < game->bricks_count; index += 1) {
            Entity *entity = entities + index;
            gfx_draw_fill_rect(gfx, entity->position, entity->size,
                               entity->color);
        }

        gfx_draw_fill_rect(gfx, game->player->position, game->player->size,
                           game->player->color);

        break;
    case GAME_STATE_MENU:
        break;
    case GAME_STATE_WIN:
        break;
    case GAME_STATE_LOSE:
        break;
    }
}

void game_add_brick(Game *game, Vector3 position, Vector2 size, Vector4 color) {
    Entity *entity = game->bricks + game->bricks_count;
    entity->position = position;
    entity->size = size;
    entity->color = color;
    game->bricks_count += 1;
}
