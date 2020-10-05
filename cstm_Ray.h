#include <stdlib.h>
#include <stdio.h>

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
}Projectile;

Vector3 fixDumbGeometryBug(Vector3* ptr_camera_target, Vector3* ptr_camera_pos)
{
    Vector3 fixed_vector3 = {0, 0, 0};
    fixed_vector3.x = ptr_camera_target->x - ptr_camera_pos->x;
    fixed_vector3.y = ptr_camera_target->y - ptr_camera_pos->y;
    fixed_vector3.z = ptr_camera_target->z - ptr_camera_pos->z;

    return fixed_vector3;
}

void initialiseProjectile(Projectile* ptr_projectile, Camera3D* ptr_camera, int n_lifetime)
{

    ptr_projectile->amount_fallen = 0.f;

    ptr_projectile->size = 0.1f;

    ptr_projectile->lifetime = n_lifetime;

    ptr_projectile->position = ptr_camera->position;

    ptr_projectile->direction = fixDumbGeometryBug(&ptr_camera->target, &ptr_camera->position);
    
    //ptr_projectile->direction.y = 4;

    printf("%i", ptr_projectile->direction.x, "/n" );
    printf("%i", ptr_projectile->direction.z);

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

}

void renderProjectile(Projectile* ptr_projectile)
{
    if(ptr_projectile->lifetime == 0)
    {
        return;
    }
    ptr_projectile->lifetime--;
    DrawSphere(ptr_projectile->position, ptr_projectile->size, ((Color){255, 255, 255, 128}));
    DrawBoundingBox(ptr_projectile->hitbox, RED);
}
void renderProjectileAsSprite(Projectile* ptr_projectile, Texture2D* texture, Camera* ptr_camera)
{
    if(ptr_projectile->lifetime == 0)
    {
        return;
    }
    ptr_projectile->lifetime--;
    DrawBillboard(*ptr_camera, *texture, ptr_projectile->position, ptr_projectile->size, RAYWHITE);
    DrawBoundingBox(ptr_projectile->hitbox, RED);

}
#endif