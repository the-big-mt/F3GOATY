cmake_minimum_required(VERSION 3.14)
project(F3GOATY VERSION 0.0.1.0)

# We want shared libraries (and modules) without any prefix in the name
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_SHARED_MODULE_PREFIX "")

# Set compiled binaries output directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Setup language standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(F3GOATY_SBE_PATH "../SugarBombEngine" CACHE PATH "Path to SugarBombEngine (SDK)")

include_directories(
	${F3GOATY_SBE_PATH}/include
	${F3GOATY_SBE_PATH}/sugarbomb/SDK/Include
)

# Add subdirectories

add_subdirectory(src)