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
#include "Public.hpp"
#include "VaultException.hpp"

std::unordered_map<std::string, Public*> Public::publics;

Public::Public(ScriptFunc _public, const std::string& name, const std::string& def) : ScriptFunction(_public, def)
{
	publics.emplace(name, this);
}

Public::Public(ScriptFuncPAWN _public, AMX* amx, const std::string& name, const std::string& def) : ScriptFunction(_public, amx, def)
{
	publics.emplace(name, this);
}

Public::~Public()
{

}

unsigned long long Public::Call(const std::string& name, const std::vector<boost::any>& args)
{
	auto it = publics.find(name);

	if (it == publics.end())
		throw VaultException("Public with name %s does not exist", name.c_str()).stacktrace();

	return it->second->ScriptFunction::Call(args);
}

const std::string& Public::GetDefinition(const std::string& name)
{
	auto it = publics.find(name);

	if (it == publics.end())
		throw VaultException("Public with name %s does not exist", name.c_str()).stacktrace();

	return it->second->def;
}

bool Public::IsPAWN(const std::string& name)
{
	auto it = publics.find(name);

	if (it == publics.end())
		throw VaultException("Public with name %s does not exist", name.c_str()).stacktrace();

	return it->second->pawn;
}

void Public::DeleteAll()
{
	for (auto it = publics.begin(); it != publics.end(); publics.erase(it++))
	{
		Public* _public = it->second;
		delete _public;
	}
}
