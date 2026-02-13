cmake_minimum_required(VERSION 3.18)
project(RaspPajRaylibDemo)

# C/C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Hämta Raylib via FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
# Bygg Raylib statiskt
set(RAYLIB_BUILD_SHARED OFF CACHE BOOL "Build Raylib as a static library")

# Plattform-specifika flaggor
if(APPLE)
    message(STATUS "Bygger för Mac")
    set(PLATFORM "Desktop")
    set(GRAPHICS "GRAPHICS_API_OPENGL_33")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Bygger för Raspberry Pi")
    set(PLATFORM "Raspberry Pi")
    set(GRAPHICS "GRAPHICS_API_OPENGL_ES2")
endif()

# Gör Raylib tillgängligt
set(FETCHCONTENT_QUIET FALSE)
FetchContent_MakeAvailable(raylib)

# Skapa exekverbar fil
add_executable(RaspPajRaylibDemo main.cpp)

# Länka Raylib
target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)

# Inkludera Raylib headers
target_include_directories(RaspPajRaylibDemo PRIVATE ${raylib_SOURCE_DIR}/src)
