#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#include "Item_functions.h"

#include "GameFrameWork.h"

#include "Entity.h"

#include "func_actions.h"

#include "cstm_Ray.h"

#include "Floor.h"

#include "Wall_Code.h"

#include "Inventory.h"

#include "Entity_functions.h"

#ifndef GAMEFUNCS
#define GAMEFUNCS

/*
This initialises the Camera,
makes the mainloop cleaner.
*/
void initializeGame(Camera *ptr_camera)
{
	InitAudioDevice();

	ptr_camera->position = (Vector3){4.0f, 2.0f, 4.0f};
	ptr_camera->target = (Vector3){0.0f, 1.8f, 0.0f};
	ptr_camera->up = (Vector3){0.0f, 1.0f, 0.0f};
	ptr_camera->fovy = 60.0f;
	ptr_camera->type = CAMERA_PERSPECTIVE;
}

void mainLoop(Framework *ptr_framwork)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1024;
	const int screenHeight = 480;

	InitWindow(screenWidth, screenHeight, "3Dengine");

	// Define the camera to look into our 3d world (position, target, up vector)
	Camera camera = {0};
	initializeGame(&camera);

	Player player;
	initialisePlayer(&player, &camera);

	SetCameraMode(camera, CAMERA_FIRST_PERSON); // Set a first person camera mode
	//SetCameraMode(camera, CAMERA_THIRD_PERSON);

	SetTargetFPS(60); // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	Projectile projectile;
	//initialiseRay(&projectile, &camera, 100);
	killProjectile(&projectile);

	MemoryManager mem_mngr;
	initialiseMemoryManager(&mem_mngr);

	//Map test;
	//loadMap(&test);

	Texture2D test_sprite_stand = LoadTexture("test_sprite_.png");
	Texture2D test_sprite_jump = LoadTexture("t_jump.png");

	Floor test_floor;
	loadFloor(&test_floor, "pond/", (Vector3){0, 0, 0});

	Floor new_floor;
	loadFloor(&new_floor, "beach/", (Vector3){0, 0, 32});

	int floors = 2;
	Floor *floor_array[floors];

	floor_array[0] = &test_floor;
	floor_array[1] = &new_floor;

	int walls = 4;
	Wall *wall_ptr_arr[walls];

	Wall wall_a;
	Wall wall_b;
	Wall wall_c;
	Wall wall_d;

	wall_ptr_arr[0] = &wall_a;
	wall_ptr_arr[1] = &wall_b;
	wall_ptr_arr[2] = &wall_c;
	wall_ptr_arr[3] = &wall_d;

	for (int i = 0; i != walls; i++)
	{
		initialiseWall(wall_ptr_arr[i], "trchstn/", (Vector3){(i - 2) * 10, 0, (i - 10) * 2});
	}

	Camera prev_frame_cam_data = camera;
	Camera prev_frame_cam_data2 = prev_frame_cam_data;

	Item t_item; Vector2 screen_dimensions = (Vector2){screenWidth, screenHeight};
	inititaliseItem(&t_item, "magic/", &screen_dimensions, MAGIC, &itemLaunchProjectile);

	Entity random_dude;
	initialiseEntity(&random_dude, "totem/", (Vector3){-1, 2, -1});
	random_dude.ptr_behaviourfunc = totemBehaviour;

	loadProjectileFrames(&projectile, "projectile/");

	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		UpdateCamera(&camera); // Update camera

// Start drawing stuff.
		BeginDrawing();
		{

			ClearBackground(BLUE);

			BeginMode3D(camera);
			{

				drawPlayerHitbox(&player);

				if (checkPlayerCollisionWithFloor(&player,
												  floor_array[checkWherePlayerIsStanding(*floor_array,
																						 floors,
																						 &player)]))
				{
					//fallPlayer(&player, &camera);
					//camera.position.y = floor_array[checkWherePlayerIsStanding(*floor_array, floors, &player)]->hitbox.max.y;
				}

				for (int i = 0; i != floors; i++)
				{
					renderFloor(floor_array[i]);
				}

				for (int i = 0; i != walls; i++)
				{

					if (isPlayerCollidingWithWall(&player, wall_ptr_arr[i]))
					{
						camera = prev_frame_cam_data;
						player.position = prev_frame_cam_data.position;
						updatePlayerHitbox(&player);
					}
					else
					{
						prev_frame_cam_data = prev_frame_cam_data2;
					}

					renderWallHitBox(wall_ptr_arr[i]);
					renderWall(wall_ptr_arr[i]);
					hasProjectileHitWall(&projectile, wall_ptr_arr[i]);
				}
				prev_frame_cam_data2.position = player.position;

				updatePlayerPosFromCam(&player);
				updatePlayerHitbox(&player);

				//drawWall(&test_w);
				//drawWall(&sphere_w);

				//drawEntity(&test_animal);

				//updateProjectile(&projectile);

				//checkCollisionWithFloor(&projectile, &test_floor);

				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					killProjectile(&projectile);
					startUsingItem(&t_item, &player, &projectile);
				}
				else
				{
					// renderProjectile(&projectile);
				}

				renderProjectileAsSprite(&projectile, &player);
				renderEntity(&random_dude, &camera);
				updateEntityHitbox(&random_dude);

				if(isEntityCollidingWithHitbox(&random_dude, attack(&player)))
				{
					
				}

				//renderMap(&test);

				
				if(IsKeyDown(KEY_SPACE))
				{
					DrawBillboard(camera, test_sprite_jump, (Vector3){0, 2, 0}, 1.3, RAYWHITE);
				}
				else
				{
					DrawBillboard(camera, test_sprite_stand, (Vector3){0, 1.3, 0}, 1, RAYWHITE);
				}

				//updatePlayerHitbox(&player, &camera);

				if(IsKeyDown(KEY_F))
				{
					DrawBoundingBox(attack(&player), RED);
				}

				if(IsKeyPressed(KEY_R))
				{
				}
				if(IsKeyPressed(KEY_T))
				{
				}

				if(player.has_attacked == true)
				{
					isEntityCollidingWithHitbox(&random_dude, attack(&player));
				}

			}
			EndMode3D();

			//DrawTexture(texture, screenWidth - texture.width - 20, 20, WHITE);
			//DrawRectangleLines(screenWidth - texture.width - 20, 20, texture.width, texture.height, GREEN);
			DrawFPS(10, 10);

			renderHeldItem(&t_item, screen_dimensions);
			updateUseCycle(&t_item, &player, &projectile);
			
			DrawCircle(screenWidth / 2, screenHeight / 2, 1, RED);

		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow(); // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return;
}

#endif
