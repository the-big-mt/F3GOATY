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
#include "AcReference.hpp"
#include "sqlite/sqlite3.h"

#include <cmath>

using namespace DB;

std::unordered_map<unsigned int, AcReference*> AcReference::refs;

AcReference::AcReference(const std::string& table, sqlite3_stmt* stmt)
{
	if (sqlite3_column_count(stmt) != 12)
		throw VaultException("Malformed input database (actor / creature references): %s", table.c_str()).stacktrace();

	unsigned int dlc = static_cast<unsigned int>(sqlite3_column_int(stmt, 11));
	// if DLC enabled

	dlc <<= 24;

	constexpr double degrees = 180.0 / M_PI;

	editor = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
	refID = static_cast<unsigned int>(sqlite3_column_int(stmt, 1));
	baseID = static_cast<unsigned int>(sqlite3_column_int(stmt, 2));
	cell = static_cast<unsigned int>(sqlite3_column_int(stmt, 3));
	pos = std::make_tuple(sqlite3_column_double(stmt, 4), sqlite3_column_double(stmt, 5), sqlite3_column_double(stmt, 6));
	angle = std::make_tuple(sqlite3_column_double(stmt, 7) * degrees, sqlite3_column_double(stmt, 8) * degrees, sqlite3_column_double(stmt, 9) * degrees);
	flags = static_cast<unsigned int>(sqlite3_column_int(stmt, 10));

	if (refID & 0xFF000000)
	{
		refID &= 0x00FFFFFF;
		refID |= dlc;
	}
	else
		refs.erase(refID);

	if (baseID & 0xFF000000)
	{
		baseID &= 0x00FFFFFF;
		baseID |= dlc;
	}

	if (cell & 0xFF000000)
	{
		cell &= 0x00FFFFFF;
		cell |= dlc;
	}

	refs.emplace(refID, this);
}

Expected<AcReference*> AcReference::Lookup(unsigned int refID)
{
	auto it = refs.find(refID);

	if (it != refs.end())
		return it->second;

	return VaultException("No actor / creature reference with refID %08X found", refID);
}

const std::string& AcReference::GetEditor() const
{
	return editor;
}

unsigned int AcReference::GetReference() const
{
	return refID;
}

unsigned int AcReference::GetBase() const
{
	return baseID;
}

unsigned int AcReference::GetCell() const
{
	return cell;
}

const std::tuple<float, float, float>& AcReference::GetPos() const
{
	return pos;
}

const std::tuple<float, float, float>& AcReference::GetAngle() const
{
	return angle;
}

unsigned int AcReference::GetFlags() const
{
	return flags;
}
