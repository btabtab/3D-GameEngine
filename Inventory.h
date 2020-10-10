#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Item_functions.h"

#include "GameFrameWork.h"

#include "raylib.h"

#ifndef INVENTORY_H
#define INVENTORY_H

enum ItemTypes
{
	MAGIC = 000,
	SWORD = 001
};

typedef struct Item
{
	/* data */

	Texture2D frames[6];
	int current_frame;

	int use_cycle_left;

	int max_use_cycle;

	bool is_being_used;
	int current_use_frame;
	Texture2D use_frames[6];

	int item_type;

	void (*ptr_itemFunc)(Player *, Projectile *);

} Item;

void inititaliseItem(Item *ptr_item, char item_name[10], Vector2 *screen_dimensions, int item_type, void (*ptr_itemAction)(Player *, Projectile *))
{
	ptr_item->ptr_itemFunc = ptr_itemAction;

	char buffer[30] = "resources/";
	char extension_buffer[40];
	char use_extension_buffer[40];

	char extension_0[8] = "000.png";
	char extension_1[8] = "001.png";
	char extension_2[8] = "002.png";
	char extension_3[8] = "003.png";
	char extension_4[8] = "004.png";
	char extension_5[8] = "005.png";
	char extension_6[8] = "006.png";

	char *image_exts[7] = {
		&extension_0[8],
		&extension_1[8],
		&extension_2[8],
		&extension_3[8],
		&extension_4[8],
		&extension_5[8],
		&extension_6[8]};

	strcat(buffer, item_name);

	for (int str_index = 0; str_index != 6; str_index++)
	{
		strcpy(extension_buffer, buffer);
		strcpy(use_extension_buffer, extension_buffer);
		strcat(extension_buffer, image_exts[str_index]);
		strcat(use_extension_buffer, "use_");
		strcat(use_extension_buffer, image_exts[str_index]);

		ptr_item->frames[str_index] = LoadTexture(extension_buffer);
		ptr_item->use_frames[str_index] = LoadTexture(use_extension_buffer);
		strcpy(extension_buffer, buffer);

		ptr_item->use_frames[str_index].width = (ptr_item->frames[str_index].width / ptr_item->frames[str_index].width) * screen_dimensions->x;
		ptr_item->use_frames[str_index].height = (ptr_item->frames[str_index].height / ptr_item->frames[str_index].height) * screen_dimensions->y;

		ptr_item->frames[str_index].width = (ptr_item->frames[str_index].width / ptr_item->frames[str_index].width) * screen_dimensions->x;
		ptr_item->frames[str_index].height = (ptr_item->frames[str_index].height / ptr_item->frames[str_index].height) * screen_dimensions->y;

		for (int i = 0; i != 40; i++)
		{
			extension_buffer[i] = ' ';
		}
	}

	ptr_item->current_frame = 0;

	strcpy(buffer, item_name);
	strcat(buffer, "/");

	ptr_item->item_type = item_type;
}

void startUsingItem(Item *ptr_item, Player *ptr_player, Projectile *ptr_projectile)
{
	switch (ptr_item->item_type)
	{
	case (MAGIC):

		ptr_item->max_use_cycle = 60;

		ptr_item->current_frame = 0;
		ptr_item->current_use_frame = 0;
		ptr_item->is_being_used = true;
		ptr_item->use_cycle_left = ptr_item->max_use_cycle;

		ptr_player->attack_ticks_left = ptr_item->use_cycle_left;

		ptr_player->has_attacked = true;

		killProjectile(ptr_projectile);
		initialiseProjectile(ptr_projectile, ptr_player->ptr_camera, 600000);


		break;

	default:
		break;
	}
}

void updateUseCycle(Item *ptr_item, Player *ptr_player, Projectile *ptr_projectile)
{

	if (ptr_item->use_cycle_left <= 0)
	{
		return;
	}
	else
	{

		if (ptr_item->use_cycle_left >! 0)
		{

			switch (ptr_item->item_type)
			{
			case MAGIC:

				if (ptr_projectile->lifetime == 0 ||
					ptr_item->use_cycle_left == 0)
				{
					killProjectile(ptr_projectile);
					exit(0);
					ptr_player->has_attacked = false;
					return;
				}

				if(ptr_item->use_cycle_left == ptr_item->max_use_cycle)
				{
					ptr_item->ptr_itemFunc(ptr_player, ptr_projectile);
				}

				updateThrownProjectile(ptr_projectile, 0.0000);

				ptr_player->attack_ticks_left--;
				return;
				break;
			default:
				break;
			}
		}
	}
}

typedef struct Inventory
{
	/* data */
	Item items[10];

	int currently_held_item;

	int item_limit;

} Inventory;

void initialiseInventory(Inventory *ptr_inventory, Vector2 screen_dimensions)
{

	Texture2D *t_ref;

	for (int item_index = 0; item_index != 5; item_index++)
	{
		for (int item_texture_index = 0; item_texture_index != 5; item_texture_index++)
		{
			//stores the address of the target texture into a pointer for ease of readability.
			t_ref = &ptr_inventory->items[item_index].frames[item_texture_index];

			t_ref->width = (t_ref->width / t_ref->width) * screen_dimensions.x;
			t_ref->height = (t_ref->height / t_ref->height) * screen_dimensions.y;
		}
	}

	ptr_inventory->currently_held_item = 0;

	return;
}

void renderHeldItem(Item *ptr_item, Vector2 screen_dimensions)
{
	if (ptr_item->use_cycle_left == 0)
	{
		if (ptr_item->current_frame == 60)
		{
			ptr_item->current_frame = 0;
		}
		DrawTexture(ptr_item->frames[ptr_item->current_frame / 10], 0, 0, RAYWHITE);
		ptr_item->current_frame++;
	}
	else
	{
		if (ptr_item->current_use_frame == 60)
		{
			ptr_item->current_use_frame = 0;
		}
		DrawTexture(ptr_item->use_frames[ptr_item->current_use_frame / 10], 0, 0, RAYWHITE);
		ptr_item->current_use_frame++;
		ptr_item->use_cycle_left--;
	}
}

#endif