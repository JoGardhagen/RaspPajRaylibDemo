cmake_minimum_required(VERSION 3.18)
project(RaspPajRaylibDemo)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# ------------------------------
# Hämta Raylib via FetchContent
# ------------------------------
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)

# Bygg Raylib som statiskt bibliotek
set(RAYLIB_BUILD_SHARED OFF CACHE BOOL "Build Raylib as a static library" FORCE)
set(RAYLIB_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAYLIB_BUILD_GAMES OFF CACHE BOOL "" FORCE)

# Plattformsspecifika inställningar
if(APPLE)
    message(STATUS "Bygger för Mac")
    add_definitions(-DPLATFORM_DESKTOP)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(STATUS "Bygger för Raspberry Pi 5")
    add_definitions(-DPLATFORM_RPI)
    add_definitions(-DGRAPHICS_API_OPENGL_ES2)
    # Säkerställ att Raylib använder rätt backend
    set(RAYLIB_SUPPORT_RPI TRUE CACHE BOOL "Enable Raspberry Pi support" FORCE)
endif()

# Bygg Raylib
FetchContent_MakeAvailable(raylib)

# ------------------------------
# Lägg till exekverbar
# ------------------------------
add_executable(RaspPajRaylibDemo
    main.cpp
    # Lägg till fler cpp-filer här om du vill
)

# Länka Raylib
target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)

# Inkludera Raylib headers
target_include_directories(RaspPajRaylibDemo PRIVATE ${raylib_SOURCE_DIR}/src)

# ------------------------------
# Kopiera assets
# ------------------------------
file(COPY ${CMAKE_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
