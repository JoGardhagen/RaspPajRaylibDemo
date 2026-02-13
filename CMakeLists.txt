cmake_minimum_required(VERSION 3.19)
project(RaspPajRaylibDemo C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Hämta raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0.0
)
FetchContent_MakeAvailable(raylib)

add_executable(RaspPajRaylibDemo main.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Raspberry Pi
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLESv2 REQUIRED glesv2)
    pkg_check_modules(EGL REQUIRED egl)

    target_include_directories(RaspPajRaylibDemo PRIVATE ${GLESv2_INCLUDE_DIRS} ${EGL_INCLUDE_DIRS})
    target_link_libraries(RaspPajRaylibDemo PRIVATE raylib ${GLESv2_LIBRARIES} ${EGL_LIBRARIES} m)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # macOS
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(OPENGL_LIBRARY OpenGL REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)

    target_link_libraries(RaspPajRaylibDemo PRIVATE raylib ${COCOA_LIBRARY} ${OPENGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
else()
    # Annan plattform (standard)
    target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)
endif()
