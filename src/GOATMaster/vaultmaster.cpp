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
#include "Utils.hpp"
#include "MasterServer.hpp"
#include "../vaultmp.hpp"

void InputThread()
{
	char input[64];

	do
	{
		fgets(input, 64, stdin);

		if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') input[strlen(input) - 1] = '\0';

	}
	while (strcmp(input, "exit") != 0);

	MasterServer::TerminateThread();
}

int main()
{
	printf("Vault-Tec MasterServer %s \n----------------------------------------------------------\n", MASTER_VERSION);

	Utils::timestamp();
	printf("Initializing RakNet...\n");

	std::thread hMasterThread = MasterServer::InitalizeRakNet();
	std::thread hInputThread = std::thread(InputThread);

	hMasterThread.join();

	if (hInputThread.joinable())
		hInputThread.join();

	return 0;
}