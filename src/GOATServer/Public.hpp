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

#include <unordered_map>

#include "vaultserver.hpp"
#include "ScriptFunction.hpp"

/**
 * \brief Create publics to use across all scripts
 */

class Public : public ScriptFunction
{
	private:
		~Public();

		static std::unordered_map<std::string, Public*> publics;

		Public(ScriptFunc _public, const std::string& name, const std::string& def);
		Public(ScriptFuncPAWN _public, AMX* amx, const std::string& name, const std::string& def);

	public:
		template<typename... Args>
		static void MakePublic(Args&&... args) { new Public(std::forward<Args>(args)...); }

		/**
		 * \brief Calls a public
		 */
		static unsigned long long Call(const std::string& name, const std::vector<boost::any>& args);
		/**
		 * \brief Retrieves the definition of a public
		 */
		static const std::string& GetDefinition(const std::string& name);
		/**
		 * \brief Checks whether public function is a PAWN function
		 */
		static bool IsPAWN(const std::string& name);
		/**
		 * \brief Deletes all publics
		 */
		static void DeleteAll();
};