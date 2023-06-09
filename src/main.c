#include <forge.h>
#include <forge_audio.h>
#include <forge_gfx.h>
#include <forge_log.h>

#include "game.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

global_variable b32 is_quit;

int main(int argc, char *argv[]) {
    log_info("Startup...\n");

    forge_init();
    gfx_init();

    AudioState *audio_startup = audio_load("resources/audio/startup.wav");
    audio_play(audio_startup, false);

    game_start();

    while (!is_quit) {
        if (!gfx_update()) {
            is_quit = true;
        }

        game_update(0.0);

        forge_sleep(1);
    }

    game_stop();

    audio_unload(audio_startup);
    forge_destroy();

    return 0;
}
