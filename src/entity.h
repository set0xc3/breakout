#ifndef ENTITY_H
#define ENTITY_H

#include <forge_base_types.h>
#include <forge_vector2.h>
#include <forge_vector3.h>
#include <forge_vector4.h>

typedef struct Entity {
    Vector3 position;
    Vector2 size;
    Vector3 velocity;
    Vector4 color;
    void *texture;
} Entity;

#endif // ENTITY_H
