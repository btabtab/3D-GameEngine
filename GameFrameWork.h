#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#ifndef GAMEFRAMEWORK
#define GAMEFRAMEWORK

typedef struct Player
{
	Vector3 position;

	BoundingBox hitbox;

	Camera* ptr_camera;

	//Flags
	bool has_attacked;
	int attack_ticks_left;

} Player;


void updatePlayerPosFromCam(Player* ptr_player)
{
	ptr_player->position = ptr_player->ptr_camera->position;
}

void updatePlayerHitbox(Player* ptr_player)
{
	ptr_player->hitbox.max.x = ptr_player->ptr_camera->position.x + 0.50f;
	ptr_player->hitbox.max.y = ptr_player->ptr_camera->position.y + 1.f;
	ptr_player->hitbox.max.z = ptr_player->ptr_camera->position.z + 0.50f;
	ptr_player->hitbox.min.x = ptr_player->ptr_camera->position.x - 0.50f;
	ptr_player->hitbox.min.z = ptr_player->ptr_camera->position.z - 0.50f;
	return;
}

void initialisePlayer(Player* ptr_player, Camera* ptr_camera)
{
	ptr_player->ptr_camera = ptr_camera;
	updatePlayerHitbox(ptr_player);
	ptr_player->hitbox.min.y = 0.1f;
}

void fallPlayer(Player* ptr_player)
{
	ptr_player->ptr_camera->position.y -= 0.1f;
	ptr_player->ptr_camera->position.y -= 0.1f;
}

void drawPlayerHitbox(Player* ptr_player)
{
	DrawBoundingBox(ptr_player->hitbox, ORANGE);
	return;
}

typedef struct Framework
{
	Vector3 player_pos;

	

} Framework;

#endif