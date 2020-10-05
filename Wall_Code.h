#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib.h"

#include "GameFrameWork.h"

#ifndef WALL_CODE_H
#define WALL_CODE_H

typedef struct Wall
{
	Texture2D* texture;
	Vector3 position;

	BoundingBox hitbox;

} Wall;

void initialiseWall(Wall *ptr_wall, Texture2D* ptr_texture, Vector3 position)
{
	float adjust_amount = 8;

	ptr_wall->texture = ptr_texture;
	ptr_wall->position = position;

	ptr_wall->hitbox.max.x = position.x + ((ptr_wall->texture->width / ptr_wall->texture->width ) * adjust_amount / 2);
	ptr_wall->hitbox.max.y = position.y + ((ptr_wall->texture->height / ptr_wall->texture->height) * adjust_amount);

	ptr_wall->hitbox.min.x = position.x - ((ptr_wall->texture->width / ptr_wall->texture->width) * adjust_amount) / 2;
	ptr_wall->hitbox.min.y = 0;

	ptr_wall->hitbox.max.z = position.z + 0.1f;
	ptr_wall->hitbox.min.z = position.z - 0.1f;
}

void renderWallHitBox(Wall *ptr_wall)
{
	DrawBoundingBox(ptr_wall->hitbox, PINK);
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
	
	Vector3 fixed_pos = ptr_wall->position;
	fixed_pos.y += adjust_amount / 2;

	DrawCubeTexture(*ptr_wall->texture,
					fixed_pos,
					length, height, width,
					RAYWHITE);
}

bool isPlayerCollidingWithWall(Player *ptr_player, Wall *ptr_wall)
{
	if (CheckCollisionBoxes(ptr_player->hitbox, ptr_wall->hitbox))
	{
		return true;
	}
}

bool hasProjectileHitWall(Projectile *ptr_projectile, Wall *ptr_wall)
{

	if (CheckCollisionBoxSphere(ptr_wall->hitbox,
								ptr_projectile->position,
								ptr_projectile->size))
	//if(CheckCollisionBoxes(ptr_projectile->hitbox, ptr_floor_to_check->hitbox))
	{
		Vector3 temp_dir = ptr_projectile->direction;
		ptr_projectile->direction.x = 0;
		ptr_projectile->direction.y = 0;
		ptr_projectile->direction.z = 0;
	}
}
#endif
