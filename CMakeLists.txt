cmake_minimum_required(VERSION 3.20)
project(MotionEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
find_package(PkgConfig REQUIRED)

# 1. Dépendance JSON
find_package(nlohmann_json REQUIRED)

# 2. Récupération automatique de Skia (Linux x64)
set(SKIA_DIR "" CACHE PATH "Chemin optionnel vers une installation Skia locale")

if(NOT SKIA_DIR)
    message(STATUS "Téléchargement automatique des binaires pré-compilés de Skia...")

    if(POLICY CMP0135)
        cmake_policy(SET CMP0135 NEW)
    endif()

    FetchContent_Declare(
            skia_binaries
            URL https://github.com/aseprite/skia/releases/download/m102-861e4743af/Skia-Linux-Release-x64-libstdc++.zip
            DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(skia_binaries)
    set(SKIA_DIR ${skia_binaries_SOURCE_DIR})
endif()

# Détection des sous-dossiers et de la librairie Skia
set(SKIA_INCLUDE_DIR ${SKIA_DIR})
set(SKIA_LIBRARY ${SKIA_DIR}/out/Release-x64/libskia.a)

# 3. Dépendances système requises par Skia pour le rendu vectoriel & polices
pkg_check_modules(FONTCONFIG REQUIRED fontconfig)
pkg_check_modules(FREETYPE REQUIRED freetype2)

# 4. Cible principale
add_executable(motion_engine
        src/main.cpp
        src/core/timeline.cpp
        src/core/timeline.h
        src/renderer/encoder.cpp
        src/renderer/encoder.h
        src/core/easing.h
        src/core/keyframes.h
)

target_include_directories(motion_engine PRIVATE
        src
        ${SKIA_INCLUDE_DIR}
)

target_link_libraries(motion_engine PRIVATE
        nlohmann_json::nlohmann_json
        ${SKIA_LIBRARY}
        ${FONTCONFIG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        GL
        z
        pthread
        dl
)
target_include_directories(motion_engine PRIVATE
        ${FONTCONFIG_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
)