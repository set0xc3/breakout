#ifndef LEVEL_H
#define LEVEL_H

#include "entity.h"
#include "forge_vector2.h"
#include "forge_vector3.h"
#include "forge_vector4.h"

typedef struct Level {
    Entity *entities;
    u64 entity_count;
} Level;

void level_init(Level *level);
void level_add_entity(Level *level, Vector3 position, Vector2 size,
                      Vector4 color);
Entity *level_get_entities(Level *level);
u64 level_get_entity_count(Level *level);

#endif // LEVEL_H
