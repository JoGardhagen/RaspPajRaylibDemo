cmake_minimum_required(VERSION 3.13)
project(RaspPajRaylibDemo LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Lägg till Raylib som submodule eller extern projekt
add_subdirectory(_deps/raylib-src)

# Din huvudfil
set(SRC_FILES main.cpp)

add_executable(RaspPajRaylibDemo ${SRC_FILES})

# Länka Raylib
target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)

# Platform-specifika inställningar
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Raspberry Pi: behövs för OpenGL ES2
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLESv2 REQUIRED glesv2)
    pkg_check_modules(EGL REQUIRED egl)

    target_include_directories(RaspPajRaylibDemo PRIVATE ${GLESv2_INCLUDE_DIRS} ${EGL_INCLUDE_DIRS})
    target_link_libraries(RaspPajRaylibDemo PRIVATE ${GLESv2_LIBRARIES} ${EGL_LIBRARIES} m bcm_host)
else()
    # Desktop OpenGL (Linux, macOS, Windows)
    find_package(OpenGL REQUIRED)
    target_link_libraries(RaspPajRaylibDemo PRIVATE OpenGL::GL)
endif()

# Valfri compiler-warning flaggar
if(MSVC)
    target_compile_options(RaspPajRaylibDemo PRIVATE /W4 /WX)
else()
    target_compile_options(RaspPajRaylibDemo PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
