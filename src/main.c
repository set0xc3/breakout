#include <forge/forge_api.h>

#include "game.h"

int
thread_logic_update(void *data)
{
    printf("thread_logic_update:\n");

    const f64 fps_max = 60.0;
    const f64 period_max = 1.0 / fps_max;
    const f64 perf_frequency = (f64)forge_perf_frequency();

    f64 time = 0.0;
    f64 begin_counter = 0.0;
    f64 end_counter = 0.0;
    while (!gfx_quit_is())
    {
        begin_counter = (f64)forge_perf_counter();

        f64 counter_elapsed = (f64)(begin_counter - end_counter);
        f64 dt = (f64)(counter_elapsed / perf_frequency);
        f64 fps = (f64)(perf_frequency / counter_elapsed);

        if (dt > period_max)
        {
            if (dt > 1.0)
            {
                dt = period_max;
            }

            gfx_update();
            game_update(dt);

            end_counter = begin_counter;
            time += dt;
        }

        forge_sleep((u32)dt);
    }

    return 0;
}

int
thread_draw_update(void *data)
{
    printf("thread_draw_update:\n");
    while (!gfx_quit_is())
    {
        forge_sleep(1);
    }

    return 0;
}

int
main(int argc, char *argv[])
{
    gfx_init();
    gfx_window_title_set("breakout");
    // gfx_window_set_size(v2(800, 600));

    game_init();

    {
        SDL_Thread *logic
            = SDL_CreateThread(thread_logic_update, "logic", NULL);
    }

    const f64 fps_max = 60.0;
    const f64 period_max = 1.0 / fps_max;
    const f64 perf_frequency = (f64)forge_perf_frequency();

    f64 time = 0.0;
    f64 begin_counter = 0.0;
    f64 end_counter = 0.0;
    while (!gfx_quit_is())
    {
        begin_counter = (f64)forge_perf_counter();

        f64 counter_elapsed = (f64)(begin_counter - end_counter);
        f64 dt = (f64)(counter_elapsed / perf_frequency);
        f64 fps = (f64)(perf_frequency / counter_elapsed);

        if (dt >= period_max)
        {
            if (dt >= 1.0)
            {
                dt = period_max;
            }

            // Renderer
            gfx_begin();
            game_draw();
            gfx_end();

            end_counter = begin_counter;
            time += dt;
        }

        forge_sleep((u32)dt);
    }

    game_destroy();

    return 0;
}
