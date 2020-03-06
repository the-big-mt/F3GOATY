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

#include <string>
#include <vector>

#include "vaultserver.hpp"

#ifdef VAULTMP_DEBUG
#include "Debug.hpp"
#endif

/**
 * \brief Used to access vaultmp SQLite3 databases
 */

template<typename T>
class Database
{
		friend class ObjectFactory;

	private:
#ifdef VAULTMP_DEBUG
		static DebugInput<Database<T>> debug;
#endif

		std::vector<T> data;

		Database() = default;
		~Database() = default;

		unsigned int initialize(const std::string& file, const std::vector<std::string>& tables);
};