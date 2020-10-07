#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	Texture2D textures[6];
	int current_texture_frame;
	Vector3 center_in_world;

	Vector3 position;

} Floor;

void loadFloor(Floor *ptr_floor, char texture_name[10], Vector3 center_pos)
{

	char buffer[30] = "resources/";
	char extension_buffer[40];
	
	char extension_0[8] = "000.png";
	char extension_1[8] = "001.png";
	char extension_2[8] = "002.png";
	char extension_3[8] = "003.png";
	char extension_4[8] = "004.png";
	char extension_5[8] = "005.png";
	char extension_6[8] = "006.png";


	char* image_exts[7] = {	
		&extension_0[8],
		&extension_1[8],
		&extension_2[8],
		&extension_3[8],
		&extension_4[8],
		&extension_5[8],
		&extension_6[8]
	};

	strcat(buffer, texture_name);

	for(int str_index = 0; str_index != 6; str_index++)
	{
		strcpy(extension_buffer, buffer);
		strcat(extension_buffer, image_exts[str_index]);
		ptr_floor->textures[str_index] = LoadTexture(extension_buffer);
		strcpy(extension_buffer, buffer);
		for(int i = 0; i != 40; i++){extension_buffer[i] = ' ';}
	}

	ptr_floor->current_texture_frame = 0;

	strcpy(buffer, texture_name);
	strcat(buffer, "/");

	Texture2D *texture = &ptr_floor->textures[0];
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

	if(ptr_floor->current_texture_frame == 60)
	{
		ptr_floor->current_texture_frame = 0;
	}
	DrawCubeTexture(ptr_floor->textures[ptr_floor->current_texture_frame / 10], ptr_floor->center_in_world, 32, 0.1f, 32, RAYWHITE);
	ptr_floor->current_texture_frame++;
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
	return false;
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
	return 0;
}


#endif