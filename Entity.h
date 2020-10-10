#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include "raylib.h"

#include "GameFrameWork.h"

#include "func_actions.h"

#include "cstm_Ray.h"

#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity
{
	/* data */

	int health;
	int maxhealth;

	Vector3 position;
	Texture2D frames[6];
	int current_frame;

	char name[12];

	// This is a function pointer to the entities behaviour/what they should do.

	BoundingBox hitbox;

	Projectile* attack_projectile;

	void (*ptr_behaviourfunc)(Vector3*, int*);
	BoundingBox (*ptr_behaviourattack)(Player* , Projectile*);

	int behaviour_path;

}Entity;

typedef struct MemoryManager
{
	/* data */

	Entity* entities[10];
	short int entity_count;
	short int entity_limit;

	Projectile* projectiles[10];
	short int projectile_count;
	short int projectile_limit;

}MemoryManager;

void initialiseMemoryManager(MemoryManager* ptr_mem_mngr)
{
	ptr_mem_mngr->entity_count = 0;
	ptr_mem_mngr->entity_limit = 10;
	ptr_mem_mngr->projectile_count = 0;
	ptr_mem_mngr->projectile_limit = 10;
}

/*
This doesn't do anything yet!!
*/
void newEntityIntoMEMMNGR(MemoryManager* ptr_mem_mngr)
{

}

/*
This will write a new projectile into memory.
*/
void newProjectileIntoMEMMNGR(MemoryManager* ptr_mem_mngr)
{
	ptr_mem_mngr->projectile_count++;

	ptr_mem_mngr->projectiles[ptr_mem_mngr->projectile_count] = (Projectile*) malloc(sizeof(Projectile));
}
/*
This will remove a projectile from memory.
*/
void removeProjectileFromMEMMNGR(MemoryManager* ptr_mem_mngr)
{
	free(ptr_mem_mngr->projectiles[ptr_mem_mngr->projectile_count]);

	ptr_mem_mngr->projectile_count--;
}

void initialiseEntity(Entity* ptr_entity, char entity_name[10], Vector3 position)
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

	strcat(buffer, entity_name);

	for(int str_index = 0; str_index != 6; str_index++)
	{
		strcpy(extension_buffer, buffer);
		strcat(extension_buffer, image_exts[str_index]);
		ptr_entity->frames[str_index] = LoadTexture(extension_buffer);
		strcpy(extension_buffer, buffer);
		for(int i = 0; i != 40; i++){extension_buffer[i] = ' ';}
	}

	ptr_entity->current_frame = 0;

	strcpy(buffer, entity_name);
	strcat(buffer, "/");

	*ptr_entity->name = *entity_name;

	ptr_entity->position = position;


	ptr_entity->hitbox.max.x = ptr_entity->position.x + 0.50f;
	ptr_entity->hitbox.max.y = ptr_entity->position.y + 1.f;
	ptr_entity->hitbox.max.z = ptr_entity->position.z + 0.50f;
	ptr_entity->hitbox.min.x = ptr_entity->position.x - 0.50f;
	ptr_entity->hitbox.min.z = ptr_entity->position.z - 0.50f;



	// ptr_entity->hitbox.max.x = ptr_entity->position.x , ptr_entity->frames[0].width;
	// ptr_entity->hitbox.max.y = ptr_entity->position.y , ptr_entity->frames[0].height;
	// ptr_entity->hitbox.max.z = ptr_entity->position.z , ptr_entity->frames[0].width;
// 
	// ptr_entity->hitbox.min.x = ptr_entity->position.x , -ptr_entity->frames[0].width;
	// ptr_entity->hitbox.min.y = ptr_entity->position.y , -ptr_entity->frames[0].height;
	// ptr_entity->hitbox.min.z = ptr_entity->position.z , -ptr_entity->frames[0].width;


}

void updateEntityHitbox(Entity* ptr_entity)
{
	ptr_entity->hitbox.max.x = ptr_entity->position.x + 0.50f;
	ptr_entity->hitbox.max.y = ptr_entity->position.y + 1.f;
	ptr_entity->hitbox.max.z = ptr_entity->position.z + 0.50f;
	ptr_entity->hitbox.min.x = ptr_entity->position.x - 0.50f;
	ptr_entity->hitbox.min.z = ptr_entity->position.z - 0.50f;

}

void renderEntity(Entity* ptr_entity, Camera* ptr_camera)
{

	if(ptr_entity->current_frame == 60)
	{
		ptr_entity->current_frame = 0;
	}
	DrawBillboard(*ptr_camera, ptr_entity->frames[ptr_entity->current_frame / 10], ptr_entity->position, 1, RAYWHITE);
	ptr_entity->current_frame++;

	DrawBoundingBox(ptr_entity->hitbox, ORANGE);
	
	ptr_entity->ptr_behaviourfunc(&ptr_entity->position, &ptr_entity->behaviour_path);

}

bool isEntityCollidingWithHitbox(Entity* ptr_entity, BoundingBox hitbox)
{
	if(CheckCollisionBoxes(ptr_entity->hitbox, hitbox))
	{
		return true;
	}
	return false;
}

#endif