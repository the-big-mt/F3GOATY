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