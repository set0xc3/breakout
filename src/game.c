#include "framework_audio.h"
#include "framework_log.h"
#include "framework_string.h"

#include <string.h>

int main(int argc, char *argv[]) {

    log_info("%s:%d\n", "wav", strlen("wav"));

    String8 file_path = str8("resources/audio/file.wav");

    String8 file_dir = str8_alloc(&file_path);
    str8_dir(&file_dir, file_path);

    String8 file_name = str8_alloc(&file_path);
    str8_name(&file_name, file_path);

    String8 file_ext = str8_alloc(&file_path);
    str8_ext(&file_ext, file_path);

    String8 file_name_no_ext = str8_alloc(&file_path);
    str8_name_no_ext(&file_name_no_ext, file_path);

    log_info("file_path: %s\n", (char *)file_path.str);
    log_info("file_dir: %s\n", (char *)file_dir.str);
    log_info("file_name: %s\n", (char *)file_name.str);
    log_info("file_ext: %s\n", (char *)file_ext.str);
    log_info("file_name_no_ext: %s\n", (char *)file_name_no_ext.str);

    // str8_free(&file_dir);
    str8_free(&file_name);
    // str8_free(&file_name_no_ext);

    log_info("Text: %d, Float: %f, String: %s\n", 1, 3.14, "Hello");
    log_warning("Text: %d, Float: %f, String: %s\n", 1, 3.14, "Hello");
    log_error("Text: %d, Float: %f, String: %s\n", 1, 3.14, "Hello");

    Audio_State *audio_state = audio_load("resources/audio/test.wav");
    audio_unload(audio_state);

    start();
    update(0.0);
    stop();

    return 0;
}
