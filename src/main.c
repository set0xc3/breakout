#include <forge.h>
#include <forge_base_types.h>
#include <forge_gfx.h>
#include <forge_memory_arena.h>
#include <stdlib.h>

#include "game.h"

int main(int argc, char *argv[]) {
    b32 is_quit = false;
    gfx_init();
    gfx_window_set_title("breakout");
    // gfx_window_set_size(v2(800, 600));

    MemoryArena *game_memory = arena_create(Megabytes(64));
    Game *game = arena_push_zero(game_memory, sizeof(Game));
    game_init(game, game_memory);

    while (!is_quit) {
        if (!gfx_update()) {
            is_quit = true;
        }

        // Update logic
        game_update(game, 0.0);

        // Renderer
        gfx_begin();
        game_draw(game);
        gfx_end();

        forge_sleep(1);
    }

    game_destroy(game);

    return 0;
}
