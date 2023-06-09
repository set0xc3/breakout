#ifndef SCENE_H
#define SCENE_H

#include "entity.h"
#include <forge_base_types.h>

#define ENTITY_CAPASITY 256

typedef struct SceneState {
    Entity entity_list[ENTITY_CAPASITY];
    u64 entity_count;
} SceneState;

void scene_init(void);
void scene_destroy(void);
void scene_update(f64 dt);

void scene_add_entity(void);
void scene_remove_entity(void);
void scene_get_entity(void);
void scene_get_entity_list(void);

#endif // SCENE_H
