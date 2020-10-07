#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "raylib.h"

#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct Item
{
    /* data */

    Texture2D frames[6];
    int current_frame;

} Item;

void inititaliseItem(Item* ptr_item, char item_name[10], Vector2* screen_dimensions)
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

	strcat(buffer, item_name);

	for(int str_index = 0; str_index != 6; str_index++)
	{
		strcpy(extension_buffer, buffer);
		strcat(extension_buffer, image_exts[str_index]);
		ptr_item->frames[str_index] = LoadTexture(extension_buffer);
		strcpy(extension_buffer, buffer);
		for(int i = 0; i != 40; i++){extension_buffer[i] = ' ';}
	}

	ptr_item->current_frame = 0;

	strcpy(buffer, item_name);
	strcat(buffer, "/");


}


typedef struct Inventory
{
    /* data */
    Item items[5];
    
    int currently_held_item;
    int item_limit;

} Inventory;

void initialiseInventory(Inventory* ptr_inventory, Vector2 screen_dimensions)
{
    inititaliseItem(&ptr_inventory->items[0], "sword/", &screen_dimensions);
    inititaliseItem(&ptr_inventory->items[1], "null/", &screen_dimensions);
    inititaliseItem(&ptr_inventory->items[2], "null/", &screen_dimensions);
    inititaliseItem(&ptr_inventory->items[3], "null/", &screen_dimensions);
    inititaliseItem(&ptr_inventory->items[4], "null/", &screen_dimensions);

    Texture2D* t_ref;

    for (int item_index = 0; item_index != 5; item_index++)
    {
        for(int item_texture_index = 0; item_texture_index != 5; item_texture_index++)
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

void renderHeldItem(Inventory* ptr_inv)
{
    Item* t_ptr_item = &ptr_inv->items[ptr_inv->currently_held_item];

	if(t_ptr_item->current_frame == 50)
	{
		t_ptr_item->current_frame = 0;
	}
    
	DrawTexture(t_ptr_item->frames[t_ptr_item->current_frame / 10], 0, 0, RAYWHITE);
    t_ptr_item->current_frame++;
}

#endif