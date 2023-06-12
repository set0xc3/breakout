#include "level.h"
#include "entity.h"
#include "forge_base_types.h"

#include <stdlib.h>

void level_init(Level *level) {
    level->entities = calloc(sizeof(Entity), 256);

    level_add_entity(level, v3(0.0f, 0.0f, 0.0f), v2(100.0f, 100.0f),
                     v4(255.0f, 0.0f, 0.0f, 255.0f));
}

void level_add_entity(Level *level, Vector3 position, Vector2 size,
                      Vector4 color) {
    Entity *entity = level->entities + level->entity_count;
    entity->position = position;
    entity->size = size;
    entity->color = color;
    level->entity_count += 1;
}

Entity *level_get_entities(Level *level) { return level->entities; }

u64 level_get_entity_count(Level *level) { return level->entity_count; }
