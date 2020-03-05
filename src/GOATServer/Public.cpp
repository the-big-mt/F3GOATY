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
