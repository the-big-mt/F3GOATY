/// @file

#pragma once

class CActor;

class EquipType
{
public:
	///
	virtual void OnEqup(CActor &aActor){}
	
	///
	virtual void OnUnequip(CActor &aActor){}
};