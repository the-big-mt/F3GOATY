/*
*******************************************************************************

Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.
Copyright (C) 2022 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************
*/

/// @file

//*****************************************************************************

#include "GameShell.hpp"

#include "CoreLibs/SbSystem/SbSystem.hpp"

#include "CoreLibs/SbSound/SbSoundWorld.hpp"

//*****************************************************************************

namespace f3goaty
{

void CGameShell::CreateMenu(bool abInGame)
{
};

void CGameShell::Cleanup()
{
};

void CGameShell::Show(bool abShow)
{
};

void CGameShell::SyncWithSession()
{
	if(mpShellHandler == nullptr)
		return;
	
	switch(mpSession->GetState())
	{
	};
};

}; // namespace f3goaty