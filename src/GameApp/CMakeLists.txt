project(F3GOATY-gameapp)

#******************************************************************************

add_executable(${PROJECT_NAME})

set(SBE_GAME_TITLE "F3GOATY" CACHE STRING "Game title (will be the game window title)")
set(SBE_GAME_SHORT_TITLE "F3GOATY" CACHE STRING "Game short title (will be used as an output file name)")
set(SBE_GAME_CONFIG_PREFIX "Fallout" CACHE STRING "Will be used as a game config files prefix")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/GameConfig.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/GameConfig.hpp)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${SBE_INIPARSER_PATH}/src
)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

target_sources(${PROJECT_NAME}
	PRIVATE ${PROJECT_SOURCES}
)

if(WIN32)
	target_sources(${PROJECT_NAME}
		PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/rc/doom.rc #TODO: app.rc
	)
endif()

target_link_libraries(${PROJECT_NAME} SBE-clientapp SBE-application SBE-external-iniparser)

if(NOT SBE_SINGLE_BINARY)
	if(UNIX)
		target_link_libraries(${PROJECT_NAME} -ldl)
	endif()
endif()

if(SBE_SYSTEM_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} SBE-system)
endif()

if(SBE_RENDERER_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} SBE-renderer)
endif()

if(SBE_INPUT_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} SBE-input)
endif()

if(SBE_SOUND_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} SBE-sound)
endif()

if(SBE_NETWORK_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} SBE-network)
endif()

if(SBE_GAMEFRAMEWORK_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} SBE-gameframework)
endif()

if(SBE_GAME_HARD_LINKED)
	target_link_libraries(${PROJECT_NAME} F3GOATY-game)
endif()

if(SBE_USE_SDL)
	target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
endif()

if(ANDROID)
	# TODO: the app should be compiled as a dll in this case
	target_link_libraries(${PROJECT_NAME} EGL android log)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME ${SBE_GAME_SHORT_TITLE}
)