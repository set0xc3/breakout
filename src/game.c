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

    g_this->player = scene_entity_create();
    g_this->player->position = player_position;
    g_this->player->size = player_size;

    V3F ball_position = { 0 };
    V2F ball_size = v2f(24.0f, 24.0f);
    ball_position.x = (g_this->viewport.width / 2) - ball_size.width / 2;
    ball_position.y = g_this->viewport.height - player_size.y * 2;

    g_this->ball = calloc(sizeof(Ball), 1);
    g_this->ball->base = scene_entity_create();
    g_this->ball->base->position = ball_position;
    g_this->ball->base->size = ball_size;
    g_this->ball->base->velocity = v3f(0.0f, -350.0f, 0.0f);
    g_this->ball->stuck = true;
}

void
game_destroy(void)
{
    scene_destroy();
}

void
game_update(f64 dt)
{
    g_this->viewport.width = gfx_window_size_get().width;
    g_this->viewport.height = gfx_window_size_get().height;

    if (input_key_up(KeyCode_Escape))
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
        const f32 velocity = 400.0f * dt;
        if (input_key_pressed(KeyCode_A))
        {
            if (g_this->player->position.x >= 0.0f)
            {
                g_this->player->position.x -= velocity;
                if (g_this->ball->stuck)
                {
                    g_this->ball->base->position.x -= velocity;
                    g_this->ball->base->velocity.x = -400.0f;
                }
            }
        }
        if (input_key_pressed(KeyCode_D))
        {
            if (g_this->player->position.x
                <= g_this->viewport.width - g_this->player->size.width)
            {
                g_this->player->position.x += velocity;
                if (g_this->ball->stuck)
                {
                    g_this->ball->base->position.x += velocity;
                    g_this->ball->base->velocity.x = 400.0f;
                }
            }
        }

        if (input_key_pressed(KeyCode_Q))
        {
            game_reset();
        }
        if (input_key_pressed(KeyCode_E))
        {
            g_this->ball->stuck = false;
        }

        game_ball_move(dt, g_this->viewport);
    }
    break;
    default:
        break;
    }
}

void
game_draw(void)
{
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
}

void
game_ball_move(f32 dt, V4F viewport)
{
    if (!g_this->ball->stuck)
    {
        // move the ball
        g_this->ball->base->position
            = v3f_add(g_this->ball->base->position,
                      v3f_mulf(g_this->ball->base->velocity, dt));

        // check if outside window bounds; if so, reverse velocity and restore
        // at correct position
        if (g_this->ball->base->position.x <= 0.0f)
        {
            g_this->ball->base->velocity.x = -g_this->ball->base->velocity.x;
            g_this->ball->base->position.x = 0.0f;
        }
        else if (g_this->ball->base->position.x + g_this->ball->base->size.x
                 >= viewport.width)
        {
            g_this->ball->base->velocity.x = -g_this->ball->base->velocity.x;
            g_this->ball->base->position.x
                = viewport.width - g_this->ball->base->size.x;
        }
        if (g_this->ball->base->position.y <= 0.0f)
        {
            g_this->ball->base->velocity.y = -g_this->ball->base->velocity.y;
            g_this->ball->base->position.y = 0.0f;
        }
        else if (g_this->ball->base->position.y >= viewport.height)
        {
            game_reset();
        }
    }
}

void
game_reset(void)
{
    V3F player_position = { 0 };
    V2F player_size = v2f(256.0f, 32.0f);
    player_position.x = (g_this->viewport.width / 2) - player_size.width / 2;
    player_position.y = g_this->viewport.height - player_size.height;
    g_this->player->position = player_position;
    g_this->player->size = player_size;

    V3F ball_position = { 0 };
    V2F ball_size = v2f(24.0f, 24.0f);
    ball_position.x = (g_this->viewport.width / 2) - ball_size.width / 2;
    ball_position.y = g_this->viewport.height - player_size.y * 2;
    g_this->ball->base->position = ball_position;
    g_this->ball->base->size = ball_size;
    g_this->ball->base->velocity = v3f(0.0f, -350.0f, 0.0f);
    g_this->ball->stuck = true;
}
