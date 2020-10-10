#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "GameFrameWork.h"

#include "Entity.h"

#include "func_actions.h"

#include "cstm_Ray.h"

#include "Floor.h"

#include "Wall_Code.h"

#ifndef ITEM_FUNCS_H
#define ITEM_FUNCS_H

/*
This is the item funciton template
void func_name(Player* ptr_player, Projectile* ptr_projectile);
*/

void itemLaunchProjectile(Player* ptr_player, Projectile* ptr_projectile)
{
    initialiseProjectile(ptr_projectile, ptr_player->ptr_camera, 100);
}


#endif   