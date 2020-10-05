#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "GameFrameWork.h"

#include "cstm_Ray.h"

#ifndef FLOOR_H
#define FLOOR_H

typedef struct Floor
{
	BoundingBox hitbox;

	//This checks if the player is inside of the space directly above the floor.
	BoundingBox room_space;
	Texture2D texture;
	Vector3 center_in_world;

	Vector3 position;

} Floor;

void loadFloor(Floor *ptr_floor, char texture_name[10], Vector3 center_pos)
{
	ptr_floor->texture = LoadTexture(texture_name);

	Texture2D *texture = &ptr_floor->texture;
	BoundingBox *box = &ptr_floor->hitbox;
	BoundingBox *space = &ptr_floor->room_space;
	Vector3 *center = &ptr_floor->center_in_world;

	*center = center_pos;

	box->max.x = (center->x + texture->width / 2);
	box->max.z = (center->z + texture->height / 2);
	box->min.x = (center->x - texture->width / 2);
	box->min.z = (center->z - texture->height / 2);

	space->max.x = box->max.x;
	space->max.z = box->max.z;
	space->min.x = box->min.x;
	space->min.z = box->min.z;

	box->max.y = center->y + 0.1f;
	box->min.y = center->y - 0.1f;
	space->max.y = center->y + 10.f;
	space->min.y = center->y - 0.1f;
}

void renderFloorWireFrame(Floor *ptr_floor)
{
	DrawBoundingBox(ptr_floor->hitbox, GREEN);
	DrawBoundingBox(ptr_floor->room_space, RED);
}
void renderFloor(Floor *ptr_floor)
{
	renderFloorWireFrame(ptr_floor);
	DrawCubeTexture(ptr_floor->texture, ptr_floor->center_in_world, 32, 0.1f, 32, RAYWHITE);
}

void checkCollisionWithFloor(Projectile *ptr_projectile, Floor *ptr_floor_to_check)
{
	if (CheckCollisionBoxSphere(ptr_floor_to_check->hitbox,
								ptr_projectile->position,
								ptr_projectile->size))
	//if(CheckCollisionBoxes(ptr_projectile->hitbox, ptr_floor_to_check->hitbox))
	{
		killProjectile(ptr_projectile);
	}
}

bool checkPlayerCollisionWithFloor(Player *ptr_player, Floor *ptr_floor)
{
	if ((int){ptr_player->hitbox.min.y * 100} == (int){ptr_floor->hitbox.max.y * 100} &&
		CheckCollisionBoxes(ptr_player->hitbox, ptr_floor->room_space))
	{
		return true;
	}
}

int checkWherePlayerIsStanding(Floor *ptr_to_floor_arr, int floors, Player *ptr_player)
{
	for (int i = 0; i != floors - 1; i++)
	{
		if (CheckCollisionBoxes(ptr_player->hitbox, ptr_to_floor_arr[i].hitbox))
		{
			return i;
		}
	}
}


#endif