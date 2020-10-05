#include <stdlib.h>
#include <stdio.h>

#include "raylib.h"

#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct Item
{
    /* data */

    Texture2D icon;
    Texture2D hud_sprite;

} Item;


typedef struct Inventory
{
    /* data */
    Item items[5];
    
    int currently_held_item;
    int item_limit;

} Inventory;

void initialiseInventory(Inventory* ptr_inventory)
{
}

void renderHeldItem(Inventory* ptr_inv);

#endif