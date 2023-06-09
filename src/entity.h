#ifndef ENTITY_H
#define ENTITY_H

#include <forge_base_types.h>
#include <forge_vector2.h>

typedef struct Entity {
    u64 id;
    Vec2 position;
    Vec2 size;
} Entity;

#endif // ENTITY_H
