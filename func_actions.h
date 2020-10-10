#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "GameFrameWork.h"

#ifndef ACTIONS
#define ACTIONS

/*
TODO:
    Make some attack stuff, alright me?
*/

// This will return the hitbox of the attack.
BoundingBox attack(Player* ptr_player)
{
    
    //ptr_player->inventory.items;

    BoundingBox attack_box = ptr_player->hitbox;

    attack_box.max.x += +1.4f;
    attack_box.max.z += +1.4f;
    attack_box.max.y += -0.1f;

    attack_box.min.x += -1.4f;
    attack_box.min.z += -1.4f;

    attack_box.min.y += +0.4f;

    return attack_box;
}

#endif