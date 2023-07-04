#include "game.h"

#include "entity.h"
#include "scene.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

global_variable u32 tile_map[9][16] = {
    { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

global_variable Game *g_this;

void
game_init(void)
{
    g_this = calloc(sizeof(Game), 1);
    g_this->viewport.x = 0;
    g_this->viewport.y = 0;
    g_this->viewport.width = gfx_window_size_get().width;
    g_this->viewport.height = gfx_window_size_get().height;

    scene_init();

    V3F player_position = { 0 };
    V2F player_size = v2f(256.0f, 32.0f);
    player_position.x = (g_this->viewport.width / 2) - player_size.width / 2;
    player_position.y = g_this->viewport.height - player_size.height;

    g_this->player = scene_create_entity();
    g_this->player->position = player_position;
    g_this->player->size = player_size;
}

void
game_destroy(void)
{
    scene_destroy();
}

void
game_update(f64 dt)
{
    PROFILER_BEGIN(game_update);

    if (input_key_up(KEY_CODE_ESCAPE))
    {
        local_variable b32 is_pause = false;
        is_pause = !is_pause;
        g_this->state = is_pause ? GameState_Pause : GameState_Active;

        log_info("Key:ESC\n");
    }

    switch (g_this->state)
    {
    case GameState_Active:
    {
        const f32 speed = 400.0f;
        if (input_key_pressed(KEY_CODE_A))
        {
            g_this->player->position.x -= speed * dt;
        }
        if (input_key_pressed(KEY_CODE_D))
        {
            g_this->player->position.x += speed * dt;
        }
    }
    break;
    default:
        break;
    }

    PROFILER_END(game_update);
}

void
game_draw(void)
{
    PROFILER_BEGIN(game_draw);

    V2F viewport_position = v2f(0.0f, 0.0f);
    V2F viewport_padding = v2f(0.0f, 0.0f);
    V2F viewport_size
        = v2f_sub(gfx_window_size_get(), v2f_mulf(viewport_padding, 2));

    V3F player_position = v3f(viewport_size.x - 100, viewport_size.y - 100, 0);
    V2F player_size = v2f(100, 100);

    switch (g_this->state)
    {
    case GameState_Active:
    {
        for (u32 index = 0; index < scene_entity_get_count(); index += 1)
        {
            Entity *entity = scene_entity_get_by_index(index);
            gfx_draw_rect_fill(entity->position, entity->size, entity->color);
        }
    }
    break;
    default:
        break;
    }

    PROFILER_END(game_draw);
}
