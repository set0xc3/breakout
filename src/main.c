#include <forge.h>
#include <forge_base_types.h>
#include <forge_gfx.h>

#include "game.h"

global_variable b32 is_quit;
global_variable GFXState *gfx;
global_variable Game *game;

int main(int argc, char *argv[]) {
    gfx = calloc(sizeof(GFXState), 1);
    game = calloc(sizeof(Game), 1);
    game->gfx = gfx;

    forge_init();
    gfx_init(gfx);
    game_init(game);

    while (!is_quit) {
        if (!gfx_update(gfx)) {
            is_quit = true;
        }

        // Update logic
        game_update(game, 0.0);

        // Renderer
        gfx_begin(gfx);
        game_draw(game);
        gfx_end(gfx);

        forge_sleep(1);
    }

    game_destroy(game);

    forge_destroy();

    return 0;
}
