#include <forge.h>
#include <forge_audio.h>
#include <forge_input.h>
#include <forge_log.h>
#include <forge_string.h>
#include <forge_window.h>

#include <stdlib.h>
#include <string.h>

global_variable b32 is_quit;
global_variable InputState *input;
global_variable WindowState *root_window;

int main(int argc, char *argv[]) {
    log_info("Startup...\n");

    String8 file_path = str8("resources/audio/file.wav");

    String8 *file_dir = str8_alloc(file_path);
    str8_dir(file_dir, file_path);

    String8 *file_name = str8_alloc(file_path);
    str8_name(file_name, file_path);

    String8 *file_ext = str8_alloc(file_path);
    str8_ext(file_ext, file_path);

    String8 *file_name_no_ext = str8_alloc(file_path);
    str8_name_no_ext(file_name_no_ext, file_path);

    log_info("Strings:\n");
    log_info("  file_path: %s\n", str8_c(file_path));
    log_info("  file_dir: %s\n", str8_c(*file_dir));
    log_info("  file_name: %s\n", str8_c(*file_name));
    log_info("  file_ext: %s\n", str8_c(*file_ext));
    log_info("  file_name_no_ext: %s\n", str8_c(*file_name_no_ext));

    str8_free(file_dir);
    str8_free(file_name);
    str8_free(file_name_no_ext);

    input = malloc(sizeof(InputState));

    forge_init();

    root_window = window_open("[1] Engine: GameForge", 0, 0, 800, 600);

    audio_init();
    AudioState *audio_startup = audio_load("resources/audio/startup.wav");
    audio_play(audio_startup, false);

    while (!is_quit) {
        input_update(input);

        WindowEvent event = {0};
        window_poll_event(&event);

        switch (event.kind) {
        case WINDOW_EVENT_KIND_QUIT:
            is_quit = true;
            window_close(root_window);
            log_info("Shutdown...\n");
            break;
        case WINDOW_EVENT_KIND_WINDOW_CLOSED: {
        } break;
        case WINDOW_EVENT_KIND_MOUSE_BUTTON:
            input_button_callback(input, event.code, event.state);
            // log_info("Button: (%d, %d)\n", event.code, event.state);
            break;
        case WINDOW_EVENT_KIND_KEY:
            input_key_callback(input, event.code, event.state);
            // log_info("Key: (%d, %d)\n", event.code, event.state);
            break;
        case WINDOW_EVENT_KIND_MOUSE_MOTION:
            input_mouse_pos_callback(input, event.xpos, event.ypos);
            // log_info("Mouse: (%d, %d)\n", event.xpos, event.ypos);
            break;
        case WINDOW_EVENT_KIND_SCROLL_MOTION:
            input_scroll_callback(input, event.xwheel, event.ywheel);
            // log_info("Scroll: (%d, %d)\n", event.xwheel, event.ywheel);
            break;
        default:
            break;
        }

        i32 xpos, ypos = 0;
        input_mouse_get_pos(input, &xpos, &ypos);
        // log_info("Mouse: (%d, %d)\n", xpos, ypos);

        if (input_key_down(input, KEY_CODE_A)) {
            log_info("Key:A:Down\n");
        }
        if (input_key_up(input, KEY_CODE_A)) {
            log_info("Key:A:Up\n");
        }

        if (input_button_down(input, MOUSE_BUTTON_LEFT)) {
            log_info("MouseLeft:Down\n");
        }
        if (input_button_pressed(input, MOUSE_BUTTON_LEFT)) {
            // log_info("MouseLeft:pressed\n");
        }
        if (input_button_up(input, MOUSE_BUTTON_LEFT)) {
            log_info("MouseLeft:Up\n");
        }

        forge_sleep(1);
    }
    audio_unload(audio_startup);

    forge_destroy();

    return 0;
}
