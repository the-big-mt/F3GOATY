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

#include <unordered_map>

#include "vaultserver.hpp"
#include "ScriptFunction.hpp"
#include "RakNet.hpp"

/**
 * \brief Create timers to be used in scripts
 */

class Timer : public ScriptFunction, public RakNet::NetworkIDObject
{
	private:
		~Timer();

		unsigned int ms;
		unsigned int interval;
		std::vector<boost::any> args;
		bool markdelete;

		static std::unordered_map<RakNet::NetworkID, Timer*> timers;
		static RakNet::NetworkID last_timer;
		static unsigned int msecs();

		Timer(ScriptFunc timer, const std::string& def, std::vector<boost::any> args, unsigned int interval);
		Timer(ScriptFuncPAWN timer, AMX* amx, const std::string& def, std::vector<boost::any> args, unsigned int interval);

	public:
		template<typename... Args>
		static Timer* MakeTimer(Args&&... args) { return new Timer(std::forward<Args>(args)...); }

		/**
		 * \brief Called from the dedicated server main thread
		 *
		 * Calls timer functions
		 */
		static void GlobalTick();
		/**
		 * \brief Returns the NetworkID of the latest timer
		 */
		static RakNet::NetworkID LastTimer();
		/**
		 * \brief Terminates a timer
		 */
		static void Terminate(RakNet::NetworkID id);
		/**
		 * \brief Terminates all timers
		 */
		static void TerminateAll();
};