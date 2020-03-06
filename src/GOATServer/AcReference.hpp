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
#include <tuple>
#include <unordered_map>

#include "vaultserver.hpp"
#include "Expected.hpp"

class sqlite3_stmt;

/**
 * \brief Represents a game creature reference
 */

namespace DB
{
	class AcReference
	{
		private:
			static std::unordered_map<unsigned int, AcReference*> refs;

			std::string editor;
			unsigned int refID;
			unsigned int baseID;
			unsigned int cell;
			std::tuple<float, float, float> pos, angle;
			unsigned int flags;

			AcReference(const AcReference&) = delete;
			AcReference& operator=(const AcReference&) = delete;

		public:
			static const std::unordered_map<unsigned int, AcReference*>& Get() { return refs; }
			static Expected<AcReference*> Lookup(unsigned int refID);

			const std::string& GetEditor() const;
			unsigned int GetReference() const;
			unsigned int GetBase() const;
			unsigned int GetCell() const;
			const std::tuple<float, float, float>& GetPos() const;
			const std::tuple<float, float, float>& GetAngle() const;
			unsigned int GetFlags() const;

			AcReference(const std::string& table, sqlite3_stmt* stmt);
			~AcReference() = default;
			// must never be called. only defined because vector requires it
			AcReference(AcReference&&) { std::terminate(); }
			AcReference& operator=(AcReference&&) = delete;
	};
}