cmake_minimum_required(VERSION 3.18)
project(RaspPajRaylibDemo C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Hämta Raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

# Bygg Raylib som statiskt bibliotek
set(RAYLIB_BUILD_SHARED OFF CACHE BOOL "Build Raylib as a static library")

# Plattform-specifika flaggor
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Bygger för Raspberry Pi")
    set(PLATFORM "PLATFORM_RPI")
    set(GRAPHICS "GRAPHICS_API_OPENGL_ES2")  # viktigt för Pi 5!
elseif(APPLE)
    message(STATUS "Bygger för Mac")
    set(PLATFORM "PLATFORM_DESKTOP")
    set(GRAPHICS "GRAPHICS_API_OPENGL_33")
endif()

# Skicka flaggor till Raylib
set(RAYLIB_PLATFORMS ${PLATFORM})
set(RAYLIB_GRAPHICS_API ${GRAPHICS})

FetchContent_MakeAvailable(raylib)

# Exekverbar fil
add_executable(RaspPajRaylibDemo main.cpp)

# Länka mot Raylib
target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)

# Inkludera Raylibs headers
target_include_directories(RaspPajRaylibDemo PRIVATE ${raylib_SOURCE_DIR}/src)
