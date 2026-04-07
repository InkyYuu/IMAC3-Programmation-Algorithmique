# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.24)
project("IMAC")
# Optionel: Changer le dossier de sortie des exécutables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Trouve tous les fichiers .cpp dans mon répertoire src
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

# Trouve tous les fichiers .cpp dans mon répertoire src préfixés par "td"
file(GLOB_RECURSE SRC_MAIN_FILES CONFIGURE_DEPENDS "src/td*.cpp")

# On enlève les fichiers main_ des fichiers sources
list(REMOVE_ITEM SRC_FILES ${SRC_MAIN_FILES})

# Boucle sur chaque fichier cpp préfixé par "td" pour créer autant d'executables
foreach(SRC_MAIN_FILE ${SRC_MAIN_FILES})
    # Nom du fichier sans le chemin ni l'extension
    get_filename_component(EXECUTABLE_NAME ${SRC_MAIN_FILE} NAME_WE)

    string(REPLACE " " "_" EXECUTABLE_NAME "${EXECUTABLE_NAME}")

    # Ajoute un exécutable avec le nom du fichier et les autres fichiers sources
    add_executable(${EXECUTABLE_NAME} ${SRC_MAIN_FILE} ${SRC_FILES})

    # On ajoute le dossier src pour que le compilateur trouve les headers
    target_include_directories(${EXECUTABLE_NAME} PRIVATE "src")

    # On indique que l'on veut utiliser le C++17
    target_compile_features(${EXECUTABLE_NAME} PRIVATE cxx_std_17)

    # Quelques options de compilation pour ajouter des warnings
    if (MSVC)
        target_compile_options(${EXECUTABLE_NAME} PRIVATE /W3)
    else()
        target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
    endif()
    
endforeach()