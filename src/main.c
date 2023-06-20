#include <forge.h>
#include <forge_base_types.h>
#include <forge_gfx.h>
#include <forge_memory_arena.h>
#include <stdlib.h>

#include "forge_input.h"
#include "game.h"

int main(int argc, char *argv[]) {
    b32 is_quit = false;
    GFXState *gfx = gfx_init();
    InputState *input = gfx_get_input(gfx);

    MemoryArena *game_memory = arena_create(Megabytes(64));
    Game *game = arena_push_zero(game_memory, sizeof(Game));
    game_init(game, game_memory);

    while (!is_quit) {
        if (!gfx_update(gfx)) {
            is_quit = true;
        }

        // Update logic
        game_update(game, input, 0.0);

        // Renderer
        gfx_begin(gfx);
        game_draw(game, gfx);
        gfx_end(gfx);

        forge_sleep(1);
    }

    game_destroy(game);

    return 0;
}
