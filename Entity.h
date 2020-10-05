#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "GameFrameWork.h"

#include "func_actions.h"

#include "cstm_Ray.h"

#ifndef ENTITY_H
#define ENTITY_H

typedef struct Entity
{
	/* data */

	Vector3 position;
	Texture2D Texture;

	char name[12];

	// This is a function pointer to the entities behaviour/what they should do.
	void (*behaviourFunc)(Vector3);


} Entity;

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

void updateMemManagerContents(MemoryManager* ptr_mem_mngr)
{

	for (int i = 0; i < ptr_mem_mngr->entity_count; i++)
	{
		ptr_mem_mngr->entities[i]->behaviourFunc(ptr_mem_mngr->entities[i]->position);
	}
	for (int i = 0; i < ptr_mem_mngr->projectile_count; i++)
	{
		updateProjectile(ptr_mem_mngr->projectiles[i - 1]);
		renderProjectile(ptr_mem_mngr->projectiles[i - 1]);
	}
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

void initialiseEntity(Entity* ptr_entity, char name[10], Vector3 position)
{
	*ptr_entity->name = *name;
	ptr_entity->Texture = LoadTexture(name);

	ptr_entity->position = position;
}

#endif