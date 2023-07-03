#ifndef ENTITY_H
#define ENTITY_H

#include <forge/forge_api.h>

typedef struct Entity
{
    u64 id;
    V3F position;
    V2F size;
    V3F velocity;
    V4F color;
    void   *texture;
} Entity;

#endif // ENTITY_H
