/*
*******************************************************************************

Copyright (C) 2019-2020 SugarBombEngine Developers

This file is part of SugarBombEngine

SugarBombEngine is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

SugarBombEngine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SugarBombEngine. If not, see <http://www.gnu.org/licenses/>.

This file incorporates work originally covered by the MIT License. See LICENSE-vaultmp file for details.

*******************************************************************************
*/

/// @file

//*****************************************************************************

#include "ServerApp.hpp"

#include "SbGameFramework/IGameFramework.hpp"

#include "CoreLibs/SbSystem/ISystem.hpp"

#include "CoreLibs/SbSound/ISoundSystem.hpp"

//*****************************************************************************

namespace f3goaty
{

CGameApp::CGameApp(sbe::IGameFramework *apGameFramework, int argc, char **argv)
	: SbApplication(argc, argv), mpFramework(apGameFramework)
{
	mpFramework->Init();
	//if(!mpFramework->Init())
		//throw std::runtime_error("Couldn't initialize the game framework!");
};

CGameApp::~CGameApp()
{
	mpFramework->Shutdown();
};

void CServerApp::Run()
{
	#ifdef VAULTMP_DEBUG
#ifdef __WIN32__

	if (LoadLibrary("exchndl.dll") == nullptr)
		return EXIT_FAILURE;

#else
	system("ulimit -c unlimited");
#endif
#endif

#ifdef __WIN32__
	printf("Vault-Tec dedicated server %s (Windows)\n----------------------------------------------------------\n", DEDICATED_VERSION);
#else
	printf("Vault-Tec dedicated server %s (Linux)\n----------------------------------------------------------\n", DEDICATED_VERSION);
#endif

	signal(SIGINT, SignalHandler);
	signal(SIGTERM, SignalHandler);

	std::unordered_map<std::string, const char*> args;
	unsigned int arg_ = 1;

	while (argv[arg_])
	{
		if (*argv[arg_] == '-' && *(argv[arg_] + 1) && argv[arg_ + 1])
		{
			args.emplace(argv[arg_] + 1, argv[arg_ + 1]);
			++arg_;
		}

		++arg_;
	}

	unsigned int port;
	const char* host;
	unsigned int players;
	unsigned int fileslots;
	bool query;
	bool files;
	const char* announce;
	const char* scripts;
	const char* mods;
	unsigned int cell;
	bool keep;

	dictionary* config = iniparser_load(args.count("ini") ? args["ini"] : "vaultserver.ini");

	auto iniparser_getstring_ex = [&args, config](const char* param, const char* alt) -> const char* { return args.count(param) ? args[param] : iniparser_getstring(config, param, alt); };
	auto iniparser_getint_ex = [&args, config](const char* param, int alt) -> int { return args.count(param) ? strtol(args[param], nullptr, 0) : iniparser_getint(config, param, alt); };
	auto iniparser_getboolean_ex = [&args, config](const char* param, bool alt) -> bool { return args.count(param) ? strtol(args[param], nullptr, 0) : iniparser_getboolean(config, param, alt); };

	port = iniparser_getint_ex("general:port", RAKNET_STANDARD_PORT);
	host = iniparser_getstring_ex("general:host", nullptr);
	players = iniparser_getint_ex("general:players", RAKNET_STANDARD_CONNECTIONS);
	query = iniparser_getboolean_ex("general:query", true);
	files = iniparser_getboolean_ex("general:fileserve", false);
	fileslots = iniparser_getint_ex("general:fileslots", 8);
	announce = iniparser_getstring_ex("general:master", "vaultmp.com");
	cell = iniparser_getint_ex("general:spawn", 0x000010C1); // Vault101Exterior
	keep = iniparser_getboolean_ex("general:keepalive", false);
	scripts = iniparser_getstring_ex("scripts:scripts", "");
	mods = iniparser_getstring_ex("mods:mods", "");

	std::thread hInputThread = std::thread(InputThread);

	do
	{
		ServerEntry self;
		self.SetServerRule("version", DEDICATED_VERSION);
		Dedicated::SetServerEntry(&self);

		char base[MAX_PATH];
		_getcwd(base, sizeof(base));

		try
		{
#ifdef __WIN32__
			putenv(PWNFILES_PATH);
#else
			setenv(PWNFILES_KEY, PWNFILES_VAL, 1);
#endif
			std::vector<char> _scripts(scripts, scripts + strlen(scripts) + 1);
			Script::LoadScripts(&_scripts[0], base);
		}
		catch (std::exception& e)
		{
			try
			{
				VaultException& vaulterror = dynamic_cast<VaultException&>(e);
				vaulterror.Console();
			}
			catch (std::bad_cast& no_vaulterror)
			{
				VaultException vaulterror(e.what());
				vaulterror.Console();
			}
		}

		try
		{
			Dedicated::SetSpawnCell(cell);

			std::vector<char> buf(mods, mods + strlen(mods) + 1);
			char* token = strtok(&buf[0], ",");
			ModList modfiles;
			char file[MAX_PATH];
			unsigned int crc;

			while (token != nullptr)
			{
				snprintf(file, sizeof(file), "%s/%s/%s", base, MODFILES_PATH, token);

				if (!Utils::crc32file(file, &crc))
					throw VaultException("Could not find modfile %s in folder %s", token, MODFILES_PATH).stacktrace();

				modfiles.emplace_back(token, crc);

				token = strtok(nullptr, ",");
			}

			Dedicated::SetModfiles(modfiles);

			std::thread hDedicatedThread = Dedicated::InitializeServer(port, host, players, announce, query, files, fileslots);
			hDedicatedThread.join();
		}
		catch (std::exception& e)
		{
			try
			{
				VaultException& vaulterror = dynamic_cast<VaultException&>(e);
				vaulterror.Console();
			}
			catch (std::bad_cast& no_vaulterror)
			{
				VaultException vaulterror(e.what());
				vaulterror.Console();
			}

			keep = false;
		}
	} while (keep && !cmd_exit);

	if (hInputThread.joinable())
		hInputThread.join();

	iniparser_freedict(config);

#ifndef __WIN32__
	unsetenv(PWNFILES_KEY);
#endif
};

void CGameApp::RunFrame()
{
	mpSoundSystem->Update(1.0f/60.0f); // TODO
	mpFramework->Frame();
};

}; // namespace f3goaty