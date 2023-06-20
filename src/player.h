#ifndef PLAYER_H

#include "entity.h"

typedef struct Player {
    Entity base;
} Player;

void player_update(Player *player, f64 dt);

#endif // PLAYER_H
