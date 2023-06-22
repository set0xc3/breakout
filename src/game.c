#include <forge.h>
#include <forge_asset.h>
#include <forge_base_types.h>
#include <forge_gfx.h>
#include <forge_input.h>
#include <forge_log.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "game.h"

global_variable u32 tile_map[9][16] = {
    {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void game_init(Game *game, MemoryArena *memory) {
    game->memory = memory;
    game->bricks = arena_push_zero(game->memory, 256 * sizeof(Entity));
}

void game_destroy(Game *game) {}

void game_update(Game *game, f64 dt) {
    if (input_key_up(KEY_CODE_ESCAPE)) {
        game->state = game->state == GAME_STATE_ACTIVE ? GAME_STATE_MENU
                                                       : GAME_STATE_ACTIVE;
    }
}

void game_draw(Game *game) {
    switch (game->state) {
    case GAME_STATE_ACTIVE: {
        Vector2 viewport_position = v2(0.0f, 0.0f);
        Vector2 viewport_padding = v2(100.0f, 100.0f);
        Vector2 viewport_size = sub_v2(gfx_window_get_size(), mul_v2f(viewport_padding, 2));

        // gfx_draw_fill_rect(v3(viewport_padding.x, viewport_padding.y, 0.0f),
        //                    viewport_size, v4(255.0f, 255.0f, 0.0f, 255.0f));

        // Entity *entities = game->bricks;
        // for (u64 index = 0; index < game->bricks_count; index += 1) {
        //     Entity *entity = entities + index;
        //     gfx_draw_fill_rect(entity->position, entity->size,
        //     entity->color);
        // }

        Vector2 tile_scale = v2(1.0f, 1.0f);
        Vector2 tile_gaps = v2(1.0f, 1.0f);

        Vector2 scale_factor;
        scale_factor.x = viewport_size.x / (tile_scale.x * 16);
        scale_factor.y = viewport_size.y / (tile_scale.y * 9);

        Vector2 scaled_tile_size;
        scaled_tile_size.x = (f32)tile_scale.x * scale_factor.x;
        scaled_tile_size.y = (f32)tile_scale.y * scale_factor.y;

        for (u32 row = 0; row < 9; row += 1) {
            for (u32 column = 0; column < 16; column += 1) {
                Vector3 min;
                min.x =
                    ((f32)column * (scaled_tile_size.x) + viewport_padding.x);
                min.y = ((f32)row * (scaled_tile_size.y) + viewport_padding.y);
                min.z = 0.0f;
                Vector2 max;
                max.x = scaled_tile_size.x + 1.0f;
                max.y = scaled_tile_size.y + 1.0f;

                u32 tile_id = tile_map[row][column];
                if (tile_id) {
                    gfx_draw_fill_rect(min, max, v4(255, 255, 255, 255));
                } else {
                    gfx_draw_fill_rect(min, max, v4(0, 0, 125, 255));
                }
            }
        }
    } break;
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
