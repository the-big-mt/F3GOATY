/// @file

#pragma once

#include "Actor.hpp"

class CPlayerCharacter : public CActor
{
public:
	CPlayerCharacter();
	virtual ~CPlayerCharacter();
	
	void Spawn();
	void Think();
	
	void Kill(bool abDelayRespawn, bool abNoDamage);
	
	bool GiveInventoryItem(SbDict *apItem, uint32_t anFlags);
	void RemoveInventoryItem(SbDict *apItem);
};