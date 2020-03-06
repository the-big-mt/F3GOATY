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
#pragma once

#include "vaultserver/Database.hpp"
#include "vaultserver/Record.hpp"
#include "vaultserver/Reference.hpp"
#include "vaultserver/Exterior.hpp"
#include "vaultserver/Weapon.hpp"
#include "vaultserver/Race.hpp"
#include "vaultserver/NPC.hpp"
#include "vaultserver/BaseContainer.hpp"
#include "vaultserver/Item.hpp"
#include "vaultserver/Terminal.hpp"
#include "vaultserver/Interior.hpp"
#include "vaultserver/AcReference.hpp"

class ObjectFactory
{
    public:
        static void Initialize();
    private:
        static Database<DB::Record> dbRecords;
	static Database<DB::Reference> dbReferences;
	static Database<DB::Exterior> dbExteriors;
	static Database<DB::Weapon> dbWeapons;
	static Database<DB::Race> dbRaces;
	static Database<DB::NPC> dbNpcs;
	static Database<DB::BaseContainer> dbContainers;
	static Database<DB::Item> dbItems;
	static Database<DB::Terminal> dbTerminals;
	static Database<DB::Interior> dbInteriors;
	static Database<DB::AcReference> dbAcReferences;
};