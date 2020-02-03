/// @file

#pragma once

#include "Entity.hpp"
#include "Inventory.hpp"

class CActor : public CEntity
{
	bool GiveInventoryItem(SbDict *apItem, uint32_t anFlags);
	void RemoveInventoryItem(SbDict *apItem);
	
	void UseEquippedItem();
	
	Item &GetEquippedItem() const {return mInventory.GetEquippedItem();}
	Item &GetEquippedBodyWear() const {return mInventory.GetEquippedBodyWear();}
	Item &GetEquippedHeadWear() const {return mInventory.GetEquippedHeadWear();}
	Item &GetEquippedHandWear() const {return mInventory.GetEquippedHandWear();}
private:
	Inventory mInventory;
};