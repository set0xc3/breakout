#include "scene.h"

#define ENTITY_CAPACITY 256

typedef struct
{
    Entity *entity_list;
    u32     entity_count;
} Scene;

global_variable Scene *g_this;

void
scene_init(void)
{
    g_this = calloc(sizeof(Entity), 1);
    g_this->entity_list = calloc(sizeof(Entity), ENTITY_CAPACITY);
}

void
scene_destroy(void)
{
    free(g_this->entity_list);
    free(g_this);
}

Entity *
scene_create_entity(void)
{
    if (g_this->entity_count + 1 > ENTITY_CAPACITY)
    {
        log_error("Failed create entity\n");
        return NULL;
    }

    Entity *result = g_this->entity_list + g_this->entity_count;
    result->id = g_this->entity_count + 1;
    result->color = v4f(255.0f, 0.0f, 255.0f, 255.0f);
    result->size = v2f(100.0f, 100.0f);
    g_this->entity_count++;

    return result;
}

void
scene_destroy_entity(Entity *entity)
{
    if (g_this->entity_count - 1 < 0)
    {
        log_error("Failed destroy entity\n");
    }

    memset(entity, 0, sizeof(Entity));
    g_this->entity_count--;
}

u32
scene_entity_get_count(void)
{
    return g_this->entity_count;
}

Entity *
scene_entity_get_by_index(u32 index)
{
    return g_this->entity_list + index;
}
