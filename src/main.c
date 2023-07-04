#include <forge/forge_api.h>

#include "game.h"

int
main(int argc, char *argv[])
{

    gfx_init();
    gfx_window_title_set("breakout");
    gfx_window_size_set(v2f(800, 600));

    debug_profiler_init();
    game_init();

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

            gfx_update();
            game_update(dt);

            // Renderer
            gfx_begin();
            game_draw();
            gfx_end();

            end_counter = begin_counter;
            time += dt;

            log_info("fps: %d\n", (u32)fps + 1);
        }

        debug_profiler_handle();

        f64 sleep_time_ms = period_max;
        forge_sleep((u64)sleep_time_ms * 1000);
    }

    game_destroy();
    debug_profiler_destroy();

    return 0;
}
