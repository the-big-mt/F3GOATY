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
#include <thread>

#include "vaultserver.hpp"
#include "RakNet.hpp"

#ifdef VAULTMP_DEBUG
#include "Debug.hpp"
#endif

constexpr auto RAKNET_STANDARD_PORT{1770};
constexpr auto RAKNET_STANDARD_CONNECTIONS{4};
constexpr auto RAKNET_MASTER_RATE{2000};
constexpr auto RAKNET_MASTER_STANDARD_PORT{1660};

typedef std::vector<std::pair<std::string, unsigned int>> ModList;

/**
 * \brief The main class of the dedicated server
 */

class ServerEntry;

class Dedicated
{
		friend class NetworkServer;
		friend class Server;
		friend class FileProgress;

	private:
		static RakNet::RakPeerInterface* peer;

		static unsigned int port;
		static const char* host;
		static unsigned int fileslots;
		static unsigned int connections;
		static const char* announce;
		static bool query;
		static bool fileserve;

		static void Announce(bool announce);
		static void Query(RakNet::Packet* packet);
		static RakNet::TimeMS announcetime;
		static RakNet::SystemAddress master;
		static ServerEntry* self;
		static unsigned int cell;
		static ModList modfiles;

		static void DedicatedThread();
		static void FileThread();

		static bool thread;

#ifdef VAULTMP_DEBUG
		static DebugInput<Dedicated> debug;
#endif

	public:
		/**
		 * \brief Initializes the dedicated server
		 *
		 * port - the port to run the server on
		 * connections - the maximum amount of player connections
		 * host - the IP address to listen on
		 * announce - whether the server should announce himself to a MasterServer, can be nullptr
		 * query - enable / disable direct query
		 * fileserver - enable / disable file downloading from this server
		 * fileslots - the maximum amount of file downloading connections
		 */
		static std::thread InitializeServer(unsigned int port, const char* host, unsigned int connections, const char* announce, bool query, bool fileserve, unsigned int fileslots);
		/**
		 * \brief Sets the ServerEntry of the dedicated server
		 *
		 * A ServerEntry contains information about the game, the players and a set of rules / values
		 */
		static void SetServerEntry(ServerEntry* self);
		/**
		 * \brief Sets the ModList of the dedicated server
		 *
		 * A ModList is of the form vector<pair<string, unsigned int> >
		 * string is the relative path to the modfile
		 * unsigned int is the CRC32 of the modfile
		 */
		static void SetModfiles(ModList modfiles);
		/**
		 * \brief Terminates the dedicated server thread
		 */
		static void TerminateThread();

		/**
		 * \brief Sets the server name
		 */
		static void SetServerName(const char* name);
		/**
		 * \brief Sets the server map
		 */
		static void SetServerMap(const char* map);
		/**
		 * \brief Defines a server rule
		 */
		static void SetServerRule(const char* rule, const char* value);
		/**
		 * \brief Sets the default spawn cell for players of the dedicated server
		 */
		static void SetSpawnCell(unsigned int cell);
		/**
		 * \brief Returns the current number of player connections
		 */
		static unsigned int GetCurrentPlayers();
		/**
		 * \brief Returns the maximum number of player connections
		 */
		static unsigned int GetMaximumPlayers();

		//static void SetServerConnections(int connections);

};