/// @file

#pragma once

class Item;

class Inventory
{
public:
	Item &GetEquippedItem() const;
	Item &GetEquippedBodyWear() const;
	Item &GetEquippedHeadWear() const;
	Item &GetEquippedHandWear() const;
};