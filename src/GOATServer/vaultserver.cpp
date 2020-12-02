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

#include "vaultserver.hpp"
#include "Dedicated.hpp"
#include "Script.hpp"
#include "Utils.hpp"
#include "Client.hpp"
#include "ServerEntry.hpp"

#include "iniparser/src/dictionary.h"
#include "iniparser/src/iniparser.h"

#ifdef __WIN32__
#include <winsock2.h>
#endif

#include <cstdio>
#include <thread>
#include <unordered_map>
#include <csignal>
#include <cstdlib>

//*****************************************************************************

using namespace RakNet;

bool cmd_exit = false;

void InputThread()
{
	cmd_exit = false;
	char input[256];
	std::string cmd;

	do
	{
		fgets(input, sizeof(input), stdin);

		unsigned int len;
		if (*input && input[(len = strlen(input)) - 1] == '\n')
			input[len - 1] = '\0';

		char* tok = strtok(input, " ");

		if (!tok)
			continue;

		cmd = std::string(tok);

		if (!strcmp(cmd.c_str(), "ls"))
		{
			std::vector<RakNetGUID> clients = Client::GetNetworkList(nullptr);

			for (RakNetGUID& guid : clients)
			{
				Client* client = Client::GetClientFromGUID(guid);

				if (client)
				{
					unsigned int id = client->GetID();
					auto player = GameFactory::Get<Player>(client->GetPlayer());

					if (player)
						printf("client ID: %d, player name: %s\n", id, player->GetName().c_str());
				}
			}
		}
		else if (!strcmp(cmd.c_str(), "uimsg"))
		{
			const char* _id = strtok(nullptr, " ");

			if (_id)
			{
				unsigned int id = atoi(_id);
				Client* client = Client::GetClientFromID(id);

				if (client)
				{
					const char* msg = _id + strlen(_id) + 1;

					if (*msg)
						Script::UIMessage(client->GetPlayer(), msg, 0);
				}
			}
		}
	}
	while (!cmd_exit && !(cmd_exit = !strcmp(cmd.c_str(), "exit")));

	Dedicated::TerminateThread();
}

void SignalHandler(int)
{
	printf("SIGTERM/SIGINT received. Shutting down... Press enter to continue.\n");
	cmd_exit = true;
	Dedicated::TerminateThread();
}

int main(int, char* argv[])
{


	return EXIT_SUCCESS;
}
