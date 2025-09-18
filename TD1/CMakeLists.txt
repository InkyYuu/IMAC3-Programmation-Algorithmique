cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(TD01)

# On indique que l'on veut créer un exécutable "ex01" compilé à partir du fichier td01_ex01.cpp
add_executable(ex01 src/td01_ex01.cpp)

# On indique que l'on veut créer un exécutable "ex02" compilé à partir du fichier td01_ex02.cpp
add_executable(ex02 src/td01_ex02.cpp)