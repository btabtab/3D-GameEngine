#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "cstm_Ray.h"

#include "GameFrameWork.h"

#ifndef BLOCK_H
#define BLOCK_H

typedef struct Block
{
    /* data */

    Texture2D* ptr_texture;
    Vector3 Position;

    BoundingBox hitbox;

    bool is_present;

} Block;

typedef struct Map
{
    /* data */

    Texture2D grass_texture;
    Texture2D dirt_texture;
    Texture2D water_texture;

    Block blocks[10][10][10];

    int block_count;

} Map;

void initialiseBlock(Block* ptr_block, Texture2D* ptr_texture, Vector3 position)
{
    ptr_block->is_present = true;

    ptr_block->Position = position;

    ptr_block->hitbox.max.x = position.x + 1.f;
    ptr_block->hitbox.max.y = position.y + 1.f;
    ptr_block->hitbox.max.z = position.z + 1.f;

    ptr_block->hitbox.min.x = position.x - 1.f;
    ptr_block->hitbox.min.y = position.y - 1.f;
    ptr_block->hitbox.min.z = position.z - 1.f;

    ptr_block->ptr_texture = ptr_texture;
}

bool isCollidingWithBlock(Block* ptr_block_to_check, Projectile* ptr_projectile)
{
    return CheckCollisionBoxes(ptr_block_to_check->hitbox, ptr_projectile->hitbox);
}

void checkForCollisionWithEveryBlock(Map* ptr_map, Projectile* ptr_projectile)
{
    for(int y = 0; y != 10; y++)
    {
        for(int x = 0; x != 10; x++)
        {
            for(int z = 0; z != 10; z++)
            {

                if(isCollidingWithBlock(&ptr_map->blocks[x][y][z], ptr_projectile)
                &&
                ptr_map->blocks[x][y][z].is_present)
                    {
                        //ptr_map->blocks[x][y][z].ptr_texture = &ptr_map->dirt_texture;
                        ptr_map->blocks[x][y][z].is_present = false;
                        killProjectile(ptr_projectile);

                    }
            }
        }
    }
}

void loadMap(Map* ptr_map)
{
    ptr_map->grass_texture = LoadTexture("resources/grass.png");
    ptr_map->dirt_texture = LoadTexture("resources/dirt.png");

    for(int y = 0; y != 10; y++)
    {
        for(int x = 0; x != 10; x++)
        {
            for(int z = 0; z != 10; z++)
            {

                initialiseBlock(
                    &ptr_map->blocks[x][y][z],
                    &ptr_map->grass_texture,
                    (Vector3){x, (10 - y) - 10, z});
            }
        }
    }

}

void renderMap(Map* ptr_map)
{
    for(int y = 0; y != 10; y++)
    {
        for(int x = 0; x != 10; x++)
        {
            for(int z = 0; z != 10; z++)
            {
                //DrawCubeTexture(
                //    *ptr_map->blocks[x][y][z].ptr_texture,
                //    (Vector3){x, (10 - y) - 10, z},
                //    1.f, 1.f, 1.f,
                //    RAYWHITE
                //);

                //DrawBoundingBox(ptr_map->blocks[x][y][z].hitbox, RED);

                if(!ptr_map->blocks[x][y][z].is_present)
                {
                    break;
                }

                Block* temp = &ptr_map->blocks[x][y][z];

                DrawCubeTexture(*temp->ptr_texture, temp->Position, 1, 1, 1, RAYWHITE);
            }
        }
    }
}

#endif