#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

#include "GameFrameWork.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H

typedef struct Projectile
{
    Vector3 position;
    Vector3 direction;
    int lifetime;
    BoundingBox hitbox;
    float size;
    float amount_fallen;

    Texture2D frames[6];
    int current_frame;
}Projectile;

Vector3 fixDumbGeometryBug(Vector3* ptr_camera_target, Vector3* ptr_camera_pos)
{
    Vector3 fixed_vector3 = {0, 0, 0};
    fixed_vector3.x = ptr_camera_target->x - ptr_camera_pos->x;
    fixed_vector3.y = ptr_camera_target->y - ptr_camera_pos->y;
    fixed_vector3.z = ptr_camera_target->z - ptr_camera_pos->z;

    return fixed_vector3;
}

void loadProjectileFrames(Projectile* ptr_projectile, char texture_name[10])
{

    ptr_projectile->current_frame = 0;

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
		ptr_projectile->frames[str_index] = LoadTexture(extension_buffer);
		strcpy(extension_buffer, buffer);
		for(int i = 0; i != 40; i++){extension_buffer[i] = ' ';}
	}

	strcpy(buffer, texture_name);
	strcat(buffer, "/");

}

void initialiseProjectile(Projectile* ptr_projectile, Camera3D* ptr_camera, int n_lifetime)
{
    ptr_projectile->current_frame = 0;

    ptr_projectile->amount_fallen = 0.f;

    ptr_projectile->size = 0.1f;

    ptr_projectile->lifetime = n_lifetime;

    ptr_projectile->position = ptr_camera->position;

    ptr_projectile->direction = fixDumbGeometryBug(&ptr_camera->target, &ptr_camera->position);
    
    //ptr_projectile->direction.y = 4;

    ptr_projectile->direction.x /= 3;
    ptr_projectile->direction.y /= 3;
    ptr_projectile->direction.z /= 3;

    ptr_projectile->hitbox.max.x = ptr_projectile->position.x + ptr_projectile->size;
    ptr_projectile->hitbox.max.y = ptr_projectile->position.y + ptr_projectile->size;
    ptr_projectile->hitbox.max.z = ptr_projectile->position.z + ptr_projectile->size;

    ptr_projectile->hitbox.min.x = ptr_projectile->position.x - ptr_projectile->size;
    ptr_projectile->hitbox.min.y = ptr_projectile->position.y - ptr_projectile->size;
    ptr_projectile->hitbox.min.z = ptr_projectile->position.z - ptr_projectile->size;

}

void killProjectile(Projectile* ptr_projectile)
{
    ptr_projectile->position = (Vector3){0, 0, 0};
    ptr_projectile->hitbox = (BoundingBox){
        {0, 0, 0},
        {0, 0, 0}
    };
    ptr_projectile->lifetime = 0;
}

void updateProjectile(Projectile* ptr_projectile)
{
    ptr_projectile->position.x += ptr_projectile->direction.x;
    ptr_projectile->position.y += ptr_projectile->direction.y;
    ptr_projectile->position.z += ptr_projectile->direction.z;

    ptr_projectile->hitbox.max.x = ptr_projectile->position.x + ptr_projectile->size / 2;
    ptr_projectile->hitbox.max.y = ptr_projectile->position.y + ptr_projectile->size / 2;
    ptr_projectile->hitbox.max.z = ptr_projectile->position.z + ptr_projectile->size / 2;

    ptr_projectile->hitbox.min.x = ptr_projectile->position.x - ptr_projectile->size / 2;
    ptr_projectile->hitbox.min.y = ptr_projectile->position.y - ptr_projectile->size / 2;
    ptr_projectile->hitbox.min.z = ptr_projectile->position.z - ptr_projectile->size / 2;

    ptr_projectile->lifetime--;

}

void updateThrownProjectile(Projectile* ptr_projectile, float fall_amount)
{
    ptr_projectile->position.x += ptr_projectile->direction.x;
    ptr_projectile->position.y += ptr_projectile->direction.y;
    ptr_projectile->position.z += ptr_projectile->direction.z;

    ptr_projectile->amount_fallen += fall_amount;

    ptr_projectile->direction.y -= (ptr_projectile->amount_fallen);

    ptr_projectile->hitbox.max.x = ptr_projectile->position.x + ptr_projectile->size / 2;
    ptr_projectile->hitbox.max.y = ptr_projectile->position.y + ptr_projectile->size / 2;
    ptr_projectile->hitbox.max.z = ptr_projectile->position.z + ptr_projectile->size / 2;

    ptr_projectile->hitbox.min.x = ptr_projectile->position.x - ptr_projectile->size / 2;
    ptr_projectile->hitbox.min.y = ptr_projectile->position.y - ptr_projectile->size / 2;
    ptr_projectile->hitbox.min.z = ptr_projectile->position.z - ptr_projectile->size / 2;

    ptr_projectile->current_frame++;


}

void renderProjectileAsSprite(Projectile* ptr_projectile, Player* ptr_player)
{
    //if(ptr_projectile->lifetime == 0)
    //{
    //    return;
    //}
    if(ptr_projectile->current_frame == 6)
    {
        ptr_projectile->current_frame = 0;
    }
    DrawBillboard(*ptr_player->ptr_camera, ptr_projectile->frames[ptr_projectile->current_frame], ptr_projectile->position, ptr_projectile->size, RAYWHITE);
    DrawBoundingBox(ptr_projectile->hitbox, RED);

}
#endif