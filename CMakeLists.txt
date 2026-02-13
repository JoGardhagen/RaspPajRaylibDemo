cmake_minimum_required(VERSION 3.19)
project(RaspPajRaylibDemo C CXX)

# Standarder
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Konfigurera raylib-inställningar INNAN FetchContent ---
# På Pi 5 använder vi "Desktop" eftersom den kör modern Mesa/OpenGL
set(PLATFORM "Desktop" CACHE STRING "raylib platform")
set(BUILD_EXAMPLES OFF CACHE BOOL "Don't build raylib examples")
set(BUILD_GAMES OFF CACHE BOOL "Don't build raylib games")
set(WITH_PIC ON CACHE BOOL "Build with Position Independent Code")

# --- 2. Hämta raylib via FetchContent ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
)
FetchContent_MakeAvailable(raylib)

# --- 3. Definiera din exekverbara fil ---
# Ersätt main.cpp med dina källkodsfiler om du har fler
add_executable(${PROJECT_NAME} main.cpp)

# --- 4. Hitta och länka beroenden ---
if(UNIX AND NOT APPLE)
    # Vi behöver dessa för att raylib ska kunna prata med fönsterhanteraren och ljudet på Pi 5
    find_package(Threads REQUIRED)
    
    # Länka biblioteken
    # raylib target sköter mycket själv, men på Linux behöver vi ofta dessa explicit:
    target_link_libraries(${PROJECT_NAME} PRIVATE 
        raylib 
        GL 
        m 
        pthread 
        dl 
        rt 
        X11
        asound # För ljudstöd
    )
    
    # Om du kör i en ren Wayland-miljö kan du ibland behöva dessa, 
    # men X11-lagret (XWayland) på Pi 5 hanterar det oftast automatiskt.
    
elseif(APPLE)
    # Specifikt för macOS (om du vill köra samma kod där)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

# --- 5. Installation/Output (Valfritt) ---
# Gör det enkelt att hitta binärfilen
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")