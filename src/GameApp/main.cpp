/*
*******************************************************************************

Copyright (C) 2008-2018 OpenMW Developers
Copyright (C) 2019-2020, 2022 SugarBombEngine Developers

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

#include <cstdlib>

#include "GameApp.hpp"
#include "GameConfig.hpp"
//#include "SbGameExternal.hpp"
#include "SbGameFrameworkExternal.hpp"

#ifdef _WIN32
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
	// makes __argc and __argv available on windows
//#	include <cstdlib>
#endif

//*****************************************************************************

// TODO: delete mpFramework; mpFramework = nullptr;

sbe::IGameFramework *CreateGameFramework()
{
#ifndef SBE_GAMEFRAMEWORK_HARD_LINKED
	static sbe::SbGameFrameworkExternal SbGameFrameworkModule;
	return SbGameFrameworkModule.GetGameFramework();
#else
	return new sbe::SbGameFramework::SbGameFramework();
#endif
};

/*
sbe::IGame *CreateGame()
{
#ifndef SBE_GAME_HARD_LINKED
	static sbe::SbGameExternal SbGameModule();
	return SbGameModule.GetGame();
#else
	return new sbe::SbGame::SbGame();
#endif
};
*/

#ifdef ANDROID
extern "C" int SDL_main(int argc, char **argv)
#else
int sbe::SbApplication::Main(int argc, char **argv)
#endif
{
	//return wrapApplication(&runApplication, argc, argv, "OpenMW");

	//sbe::IGame &Game = *CreateGame();
	sbe::IGameFramework &GameFramework = *CreateGameFramework();
	
	
	

	f3goaty::CGameApp App(sbe::GAME_TITLE, sbe::GAME_CONFIG_PREFIX, pGameFramework.get(), argc, argv);
	App.Run();
	return EXIT_SUCCESS;
};

// Platform specific for Windows when there is no console built into the executable
// Windows will call the WinMain function instead of main in this case, the normal
// main function is then called with the __argc and __argv parameters
#if defined(_WIN32) && !defined(_CONSOLE)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return main(__argc, __argv);
};
#endif