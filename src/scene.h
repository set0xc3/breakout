#ifndef SCENE_H
#define SCENE_H

#include <forge/forge_api.h>

#include "entity.h"

void    scene_init(void);
void    scene_destroy(void);
Entity *scene_create_entity(void);
void    scene_destroy_entity(Entity *entity);
u32     scene_entity_get_count(void);
Entity *scene_entity_get_by_index(u32 index);

#endif // SCENE_H
