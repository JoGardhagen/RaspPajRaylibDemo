cmake_minimum_required(VERSION 3.14)
project(RaspPajRaylibDemo LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# --- Hämta Raylib via FetchContent ---
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(raylib)

# --- Ditt projekt ---
add_executable(RaspPajRaylibDemo main.cpp)
target_link_libraries(RaspPajRaylibDemo PRIVATE raylib)

# --- Plattformsspecifika inställningar ---
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Raspberry Pi: OpenGL ES2 + EGL + Broadcom
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLESv2 REQUIRED glesv2)
    pkg_check_modules(EGL REQUIRED egl)

    target_include_directories(RaspPajRaylibDemo PRIVATE ${GLESv2_INCLUDE_DIRS} ${EGL_INCLUDE_DIRS})
    target_link_libraries(RaspPajRaylibDemo PRIVATE ${GLESv2_LIBRARIES} ${EGL_LIBRARIES} m bcm_host)

elseif(APPLE)
    # macOS: OpenGL (via Cocoa)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(OpenGL_LIBRARY OpenGL REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)

    target_link_libraries(RaspPajRaylibDemo PRIVATE ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif()
