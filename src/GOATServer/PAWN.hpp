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

#include "vaultserver.hpp"
#include "amx/amx.h"
#include "boost/any.hpp"

/**
 * \brief Contains the PAWN scripting function wrappers
 */

class PAWN
{
	private:
		PAWN() = delete;

		// thanks to http://fuch.si/eg

		template<std::size_t... Is> struct indices {};
		template<std::size_t N, std::size_t... Is> struct build_indices : build_indices<N-1, N-1, Is...> {};
		template<std::size_t... Is> struct build_indices<0, Is...> : indices<Is...> {};
		template<std::size_t N> using IndicesFor = build_indices<N>;

		template<std::size_t... Indices>
		static AMX_NATIVE_INFO* functions(indices<Indices...>);

	public:
		static cell CreateTimer(AMX* amx, const cell* params) noexcept;
		static cell CreateTimerEx(AMX* amx, const cell* params) noexcept;
		static cell MakePublic(AMX* amx, const cell* params) noexcept;
		static cell CallPublic(AMX* amx, const cell* params) noexcept;

		static int LoadProgram(AMX* amx, const char* filename, void* memblock);
		static int Init(AMX* amx);
		static int Exec(AMX* amx, cell* retval, int index);
		static int FreeProgram(AMX* amx);
		static bool IsCallbackPresent(AMX* amx, const char* name);
		static cell Call(AMX* amx, const char* name, const char* argl, int buf, ...);
		static cell Call(AMX* amx, const char* name, const char* argl, const std::vector<boost::any>& args);
};