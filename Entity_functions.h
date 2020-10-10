#include <math.h>

#include "raylib.h"

#include "GameFrameWork.h"
#include "cstm_Ray.h"

void totemBehaviour(Vector3* position, int* behaviour_path)
{

    if(-5.f < position->x && *behaviour_path == 0)
    {
        position->x -= 0.1f / 2;
        return;
    }
    else
    {
        *behaviour_path = 1;
    }
    if(position->x < +5.f && *behaviour_path == 1)
    {
        position->x += 0.1f / 2;
        return;
    }
    else
    {
        *behaviour_path = 0;
    }
    
    



    return;
}

BoundingBox totemAttack(Player* ptr_player, Projectile* ptr_projectile)
{
    return ptr_player->hitbox;
}