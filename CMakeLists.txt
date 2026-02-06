# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Configuration SDK Pico (Auto-généré par l'extension) ---
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico2 CACHE STRING "Board type")
include(pico_sdk_import.cmake)

project(MicroDesk C CXX ASM)
pico_sdk_init()

# --- Sources ---
# Note : Éviter GLOB autant que possible, mais on garde ta structure ici
file(GLOB LUA_WRAPPER "lib/*.c")
file(GLOB LUA "lib/lua/*.c")

# --- Création de la librairie interne ---
add_library(screen_lib STATIC
    core/screen/screen.c
    core/filesystem/filesystem.c
    core/network/net.c
    core/system.c
    core/utils/shell.c
    core/utils/commands.c
    core/utils/luastd.c
    core/utils/lib.c       # Ton fichier lib.c est ici
    ${LUA}
    ${LUA_WRAPPER}
)

# CRUCIAL : On lie pico_stdlib à la LIBRAIRIE aussi.
# Cela permet à lib.c de trouver "pico/stdlib.h"
target_link_libraries(screen_lib 
    pico_stdlib 
    pico_multicore # Optionnel, souvent utile sur Pico 2
)

# On définit les dossiers d'inclusion pour que "lib.h" soit trouvé partout
target_include_directories(screen_lib PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
    core/utils
    lib/lua
)

# --- Création de l'Exécutable ---
add_executable(MicroDesk MicroDesk.c)

pico_set_program_name(MicroDesk "MicroDesk")
pico_set_program_version(MicroDesk "0.1")

# Configuration des sorties (USB activé, UART désactivé)
pico_enable_stdio_uart(MicroDesk 0)
pico_enable_stdio_usb(MicroDesk 1)

# Liaison de l'exécutable avec notre lib
target_link_libraries(MicroDesk
    PRIVATE screen_lib
)

pico_add_extra_outputs(MicroDesk)
