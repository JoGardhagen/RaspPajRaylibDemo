cmake_minimum_required(VERSION 3.18)
project(RaspPajRaylibDemo)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Hämta Raylib via FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
set(RAYLIB_BUILD_SHARED OFF CACHE BOOL "Build Raylib as a static library")
FetchContent_MakeAvailable(raylib)

# Skapa exekverbar fil
add_executable(RaspPajRaylibDemo main.cpp)

# Länka Raylib
target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)
target_include_directories(RaspPajRaylibDemo PRIVATE ${raylib_SOURCE_DIR}/src)

# Plattform-specifika definieringar
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Bygger för Raspberry Pi")
    target_compile_definitions(RaspPajRaylibDemo PRIVATE PLATFORM_RPI)
elseif(APPLE)
    message(STATUS "Bygger för Mac")
    target_compile_definitions(RaspPajRaylibDemo PRIVATE PLATFORM_DESKTOP)
endif()
