/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
/*
game_worldspawn.cpp

Worldspawn class.  Each map has one worldspawn which handles global spawnargs.

*/

#include "precompiled.h"
#pragma hdrstop

/*
#include <cstddef>

#include "../d3xp/WorldSpawn.h"
#include "../d3xp/gamesys/Class.h"
#include "../d3xp/gamesys/SysCvar.h"
#include "../d3xp/script/Script_Program.h"
#include "../d3xp/script/Script_Thread.h"
#include "../framework/CVarSystem.h"
#include "../framework/FileSystem.h"
#include "../idlib/Dict.h"
#include "../idlib/Str.h"
#include "../idlib/sys/sys_assert.h"
*/
#include "Game_local.h"

//namespace BFG
//{

//class idRestoreGame;
//class idSaveGame;

/*
================
idWorldspawn

Every map should have exactly one worldspawn.
================
*/
CLASS_DECLARATION( idEntity, idWorldspawn )
EVENT( EV_Remove,				idWorldspawn::Event_Remove )
EVENT( EV_SafeRemove,			idWorldspawn::Event_Remove )
END_CLASS

/*
================
idWorldspawn::Spawn
================
*/
void idWorldspawn::Spawn()
{
	idStr				scriptname;
	idThread*			thread;
	const function_t*	func;
	const idKeyValue*	kv;
	
	assert( gameLocal.world == nullptr );
	gameLocal.world = this;
	
	g_gravity.SetFloat( spawnArgs.GetFloat( "gravity", va( "%f", DEFAULT_GRAVITY ) ) );
	
	// disable stamina on hell levels
	if( spawnArgs.GetBool( "no_stamina" ) )
	{
		pm_stamina.SetFloat( 0.0f );
	}
	
	// load script
	scriptname = gameLocal.GetMapName();
	scriptname.SetFileExtension( ".script" );
	if( fileSystem->ReadFile( scriptname, nullptr, nullptr ) > 0 )
	{
		gameLocal.program.CompileFile( scriptname );
		
		// call the main function by default
		func = gameLocal.program.FindFunction( "main" );
		if( func != nullptr )
		{
			thread = new idThread( func );
			thread->DelayedStart( 0 );
		}
	}
	
	// call any functions specified in worldspawn
	kv = spawnArgs.MatchPrefix( "call" );
	while( kv != nullptr )
	{
		func = gameLocal.program.FindFunction( kv->GetValue() );
		if( func == nullptr )
		{
			gameLocal.Error( "Function '%s' not found in script for '%s' key on worldspawn", kv->GetValue().c_str(), kv->GetKey().c_str() );
		}
		
		thread = new idThread( func );
		thread->DelayedStart( 0 );
		kv = spawnArgs.MatchPrefix( "call", kv );
	}
}

/*
=================
idWorldspawn::Save
=================
*/
void idWorldspawn::Save( idSaveGame* savefile )
{
}

/*
=================
idWorldspawn::Restore
=================
*/
void idWorldspawn::Restore( idRestoreGame* savefile )
{
	assert( gameLocal.world == this );
	
	g_gravity.SetFloat( spawnArgs.GetFloat( "gravity", va( "%f", DEFAULT_GRAVITY ) ) );
	
	// disable stamina on hell levels
	if( spawnArgs.GetBool( "no_stamina" ) )
	{
		pm_stamina.SetFloat( 0.0f );
	}
}

/*
================
idWorldspawn::~idWorldspawn
================
*/
idWorldspawn::~idWorldspawn()
{
	if( gameLocal.world == this )
	{
		gameLocal.world = nullptr;
	}
}

/*
================
idWorldspawn::Event_Remove
================
*/
void idWorldspawn::Event_Remove()
{
	gameLocal.Error( "Tried to remove world" );
}

//} // namespace BFG
