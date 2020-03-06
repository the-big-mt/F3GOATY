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

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "vaultserver.hpp"
#include "Expected.hpp"

class sqlite3_stmt;

/**
 * \brief Represents a game record
 */

namespace DB
{
	class Record
	{
		private:
			static std::unordered_map<unsigned int, Record*> data;

			unsigned int baseID;
			std::string name;
			std::string description;
			std::string type;

			Record(const Record&) = delete;
			Record& operator=(const Record&) = delete;

		public:
			static const std::unordered_map<unsigned int, Record*>& Get() { return data; }
			static Expected<Record*> Lookup(unsigned int baseID);
			static Expected<Record*> Lookup(unsigned int baseID, const std::string& type);
			static Expected<Record*> Lookup(unsigned int baseID, const std::vector<std::string>& type);

			static bool IsValidCell(unsigned int baseID) noexcept;
			static bool IsValidWeather(unsigned int baseID) noexcept;
			static bool IsValidSound(unsigned int baseID) noexcept;
			static bool IsValidCoordinate(unsigned int baseID, float X, float Y, float Z) noexcept;

			unsigned int GetBase() const;
			const std::string& GetName() const;
			const std::string& GetDescription() const;
			const std::string& GetType() const;

			void SetDescription(const std::string& description);

			Record(const std::string& table, sqlite3_stmt* stmt);
			~Record() = default;
			// must never be called. only defined because vector requires it
			Record(Record&&) { std::terminate(); }
			Record& operator=(Record&&) = delete;
	};
}