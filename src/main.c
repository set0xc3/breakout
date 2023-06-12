#include <forge.h>
#include <forge_audio.h>
#include <forge_gfx.h>
#include <forge_log.h>
#include <forge_vector2.h>
#include <forge_vector3.h>
#include <forge_vector4.h>

#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

global_variable b32 is_quit;
global_variable GLXState *gfx_state;

int main(int argc, char *argv[]) {
    gfx_state = malloc(sizeof(GLXState));

    log_info("Startup...\n");

    forge_init();
    gfx_init(gfx_state);

    AudioState *audio_startup = audio_load("resources/audio/startup.wav");
    audio_play(audio_startup, false);

    game_start();

    while (!is_quit) {
        if (!gfx_update(gfx_state)) {
            is_quit = true;
        }

        gfx_begin(gfx_state);
        gfx_draw_fill_rect(gfx_state, v3(0.0f, 0.0f, 0.0f),
                           v3(10.0f, 10.0f, 0.0f),
                           v4(255.0f, 255.0f, 255.0f, 255.0f));
        game_update(0.0);
        gfx_end(gfx_state);

        forge_sleep(1);
    }

    game_stop();

    audio_unload(audio_startup);
    forge_destroy();

    return 0;
}
