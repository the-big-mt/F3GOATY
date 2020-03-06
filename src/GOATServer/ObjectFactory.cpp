/*
*******************************************************************************

Copyright (C) 2019-2020 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

This file incorporates work originally covered by the MIT License. See
LICENSE-vaultmp file for details.

*******************************************************************************
*/
#include "ObjectFactory.hpp"

Database<DB::Record> ObjectFactory::dbRecords;
Database<DB::Reference> ObjectFactory::dbReferences;
Database<DB::Exterior> ObjectFactory::dbExteriors;
Database<DB::Weapon> ObjectFactory::dbWeapons;
Database<DB::Race> ObjectFactory::dbRaces;
Database<DB::NPC> ObjectFactory::dbNpcs;
Database<DB::BaseContainer> ObjectFactory::dbContainers;
Database<DB::Item> ObjectFactory::dbItems;
Database<DB::Terminal> ObjectFactory::dbTerminals;
Database<DB::Interior> ObjectFactory::dbInteriors;
Database<DB::AcReference> ObjectFactory::dbAcReferences;

void ObjectFactory::Initialize()
{
	dbRecords.initialize(DB_FALLOUT3, {"CONT", "NPC_", "CREA", "LVLI", "ALCH", "AMMO", "ARMA", "ARMO", "BOOK", "ENCH", "KEYM", "MISC", "NOTE", "WEAP", "CELL", "IDLE", "WTHR", "STAT", "MSTT", "RACE", "LIGH", "DOOR", "TERM", "EXPL", "PROJ", "STAT", "SOUN"});
	dbExteriors.initialize(DB_FALLOUT3, {"exteriors"});
	dbWeapons.initialize(DB_FALLOUT3, {"weapons"});
	dbRaces.initialize(DB_FALLOUT3, {"races"});
	dbNpcs.initialize(DB_FALLOUT3, {"npcs"});
	dbContainers.initialize(DB_FALLOUT3, {"npcitems", "contitems"});
	dbItems.initialize(DB_FALLOUT3, {"items"});
	dbTerminals.initialize(DB_FALLOUT3, {"terminals"});
	dbInteriors.initialize(DB_FALLOUT3, {"interiors"});
	dbAcReferences.initialize(DB_FALLOUT3, {"arefs", "crefs"});
	dbReferences.initialize(DB_FALLOUT3, {"refs_CONT", "refs_DOOR", "refs_TERM", "refs_STAT"});
}
