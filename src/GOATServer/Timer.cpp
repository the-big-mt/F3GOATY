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
#include "Timer.hpp"
#include "Network.hpp"

using namespace RakNet;

std::unordered_map<NetworkID, Timer*> Timer::timers;
NetworkID Timer::last_timer = 0;

Timer::Timer(ScriptFunc timer, const std::string& def, std::vector<boost::any> args, unsigned int interval) : ScriptFunction(timer, def), ms(msecs()), interval(interval), args(args), markdelete(false)
{
	this->SetNetworkIDManager(Network::Manager());
	timers.emplace(this->GetNetworkID(), this);
}

Timer::Timer(ScriptFuncPAWN timer, AMX* amx, const std::string& def, std::vector<boost::any> args, unsigned int interval) : ScriptFunction(timer, amx, def), ms(msecs()), interval(interval), args(args), markdelete(false)
{
	this->SetNetworkIDManager(Network::Manager());
	timers.emplace(this->GetNetworkID(), this);
}

Timer::~Timer()
{

}

unsigned int Timer::msecs()
{
	timeval t;
	gettimeofday(&t, nullptr);
	return (unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void Timer::GlobalTick()
{
	for (auto it = timers.begin(); it != timers.end();)
	{
		Timer* timer = it->second;

		if (timer->markdelete)
		{
			timers.erase(it++);
			delete timer;
			continue;
		}

		if ((msecs() - timer->ms) > timer->interval)
		{
			last_timer = it->first;
			timer->Call(timer->args);
			timer->ms = msecs();
		}

		++it;
	}
}

NetworkID Timer::LastTimer()
{
	return last_timer;
}

void Timer::Terminate(NetworkID id)
{
	Timer* timer = Network::Manager()->GET_OBJECT_FROM_ID<Timer*>(id);

	if (timer)
		timer->markdelete = true;
}

void Timer::TerminateAll()
{
	for (auto it = timers.begin(); it != timers.end(); timers.erase(it++))
	{
		Timer* timer = it->second;
		delete timer;
	}
}
