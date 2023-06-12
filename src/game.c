#include <forge.h>
#include <forge_asset.h>
#include <forge_base_types.h>
#include <forge_input.h>

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "forge_gfx.h"
#include "game.h"
#include "level.h"

void game_init(Game *game) {
    game->levels = calloc(sizeof(Level), 1);

    for (u64 index = 0; index < 1; index += 1) {
        level_init(game->levels + index);
        game->level_count += 1;
    }
}

void game_destroy(Game *game) {}

void game_update(Game *game, f64 dt) {
    if (input_key_up(game->gfx->input, KEY_CODE_ESCAPE)) {
        game->state = game->state == GAME_ACTIVE ? GAME_MENU : GAME_ACTIVE;
    }
}

void game_draw(Game *game) {
    switch (game->state) {
    case GAME_ACTIVE:
        gfx_draw_fill_rect(
            game->gfx, v3(0.0f, 0.0f, 0.0f),
            v2(game->gfx->window->rect.width, game->gfx->window->rect.height),
            v4(128.0f, 128.0f, 128.0f, 255.0f));

        if (game->level_count) {
            Level *level = game->levels + game->level_index;
            Entity *entities = level_get_entities(level);
            for (u64 index = 0; index < level_get_entity_count(level);
                 index += 1) {
                Entity *entity = entities + index;
                gfx_draw_fill_rect(game->gfx, entity->position, entity->size,
                                   entity->color);
            }
        }
        break;
    case GAME_MENU:
        break;
    case GAME_WIN:
        break;
    case GAME_LOSE:
        break;
    }
}
