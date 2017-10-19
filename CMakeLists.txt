cmake_minimum_required(VERSION 2.6)

#Configuration du projet

project(MH)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

#Génération de la liste des fichiers sources
file(
        GLOB_RECURSE
        source_files
        src/*
)

#Declaration de l'exécutable
add_executable(
        mh_exe
        ${source_files}
)
