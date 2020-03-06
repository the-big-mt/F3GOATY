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

constexpr auto MODFILES_PATH{"mods"};
constexpr auto SCRIPTS_PATH{"scripts"};
constexpr auto DATA_PATH{"data"};
constexpr auto PWNFILES_PATH{"AMXFILE=files"};
constexpr auto PWNFILES_KEY{"AMXFILE"};
constexpr auto PWNFILES_VAL{"files"};

constexpr auto DB_FALLOUT3{"fallout3.sqlite3"};

#ifndef MAX_PATH
#define MAX_PATH PATH_MAX
#endif

#ifndef __WIN32__
#define _getcwd getcwd
#endif

#ifndef HAVE_STDINT_H
#define HAVE_STDINT_H
#endif