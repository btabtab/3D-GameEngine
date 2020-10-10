#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "GameFrameWork.h"

#ifndef WALL_CODE_H
#define WALL_CODE_H

typedef struct Wall
{
	Texture2D frames[6];
	Vector3 position;

	Vector3 operated_position;
	Vector3 sizing;

	int current_frame;

	BoundingBox hitbox;

} Wall;

void initialiseWall(Wall *ptr_wall, char texture_name[10], Vector3 position)
{
	float adjust_amount = 8;

	ptr_wall->current_frame = 0;

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
		ptr_wall->frames[str_index] = LoadTexture(extension_buffer);
		strcpy(extension_buffer, buffer);
		for(int i = 0; i != 40; i++){extension_buffer[i] = ' ';}
	}

	strcpy(buffer, texture_name);
	strcat(buffer, "/");

	ptr_wall->position = position;

	ptr_wall->hitbox.max.x = position.x + ((ptr_wall->frames[0].width / ptr_wall->frames[0].width ) * adjust_amount / 2);
	ptr_wall->hitbox.max.y = position.y + ((ptr_wall->frames[0].height / ptr_wall->frames[0].height) * adjust_amount);

	ptr_wall->hitbox.min.x = position.x - ((ptr_wall->frames[0].width / ptr_wall->frames[0].width) * adjust_amount) / 2;
	ptr_wall->hitbox.min.y = 0;

	ptr_wall->hitbox.max.z = position.z + 0.1f;
	ptr_wall->hitbox.min.z = position.z - 0.1f;
}

void renderWallHitBox(Wall *ptr_wall)
{
	DrawBoundingBox(ptr_wall->hitbox, PINK);
}

void dealWithWallInfo(Wall* ptr_wall)
{
	float width, height, length;

	length = (ptr_wall->hitbox.max.x - ptr_wall->hitbox.min.x);
	height = (-(ptr_wall->hitbox.max.y - ptr_wall->hitbox.min.y));
	width = (ptr_wall->hitbox.max.z - ptr_wall->hitbox.min.z);
	
	float adjust_amount = 8;

	length = (length / length) * adjust_amount;
	height = (height / height) * adjust_amount;
	 width =  (width /  width) * 0.5;
	
	Vector3 fixed_pos = ptr_wall->position;
	fixed_pos.y += adjust_amount / 2;

}

void renderWall(Wall *ptr_wall)
{

	float width, height, length;

	length = (ptr_wall->hitbox.max.x - ptr_wall->hitbox.min.x);
	height = (-(ptr_wall->hitbox.max.y - ptr_wall->hitbox.min.y));
	width = (ptr_wall->hitbox.max.z - ptr_wall->hitbox.min.z);
	
	float adjust_amount = 8;

	length = (length / length) * adjust_amount;
	height = (height / height) * adjust_amount;
	 width =  (width /  width) * 0.5;
	
	ptr_wall->operated_position = ptr_wall->position;
	ptr_wall->operated_position.y += adjust_amount / 2;


	if(ptr_wall->current_frame == 60)
	{
		ptr_wall->current_frame = 0;
	}

	DrawCubeTexture(ptr_wall->frames[ptr_wall->current_frame / 10],
					ptr_wall->operated_position,
					-length, -height, width,
					RAYWHITE);
	ptr_wall->current_frame++;
}

bool isPlayerCollidingWithWall(Player *ptr_player, Wall *ptr_wall)
{
	if (CheckCollisionBoxes(ptr_player->hitbox, ptr_wall->hitbox))
	{
		return true;
	}
	return false;
}

bool hasProjectileHitWall(Projectile *ptr_projectile, Wall *ptr_wall)
{

	if (CheckCollisionBoxSphere(ptr_wall->hitbox,
								ptr_projectile->position,
								ptr_projectile->size))
	//if(CheckCollisionBoxes(ptr_projectile->hitbox, ptr_floor_to_check->hitbox))
	{
		//Vector3 temp_dir = ptr_projectile->direction;
		ptr_projectile->direction.x = 0;
		ptr_projectile->direction.y = 0;
		ptr_projectile->direction.z = 0;
		return true;
	}
	return false;
}
#endif
