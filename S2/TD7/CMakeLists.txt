cmake_minimum_required(VERSION 3.24)
include(FetchContent)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set the output directory for the executable to bin/Debug or bin/Release depending on the build type
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Get the name of the current folder and use it as the project name
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME FOLDER_NAME)   
string(REPLACE " " "_" FOLDER_NAME ${FOLDER_NAME})
project(${FOLDER_NAME})

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

Set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SRC_FILES})

# Pass the CMAKE_SOURCE_DIR to the code, so that we can make our paths relative to it
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE CMAKE_SOURCE_DIR=\"${CMAKE_SOURCE_DIR}\")

target_include_directories(${EXECUTABLE_NAME} PRIVATE "src")
target_compile_features(${EXECUTABLE_NAME} PUBLIC cxx_std_20)

# Set good compile options for the executable
if (MSVC)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE /W3)
else()
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# Fetch and link dependencies

# disable TLS verification for environments where CMake cannot validate cert chain.
set(CMAKE_TLS_VERIFY 0)

## glm
FetchContent_Declare(glm URL https://github.com/g-truc/glm/archive/refs/tags/1.0.3.tar.gz)
FetchContent_MakeAvailable(glm)

## pugixml
FetchContent_Declare(pugixml URL https://github.com/zeux/pugixml/archive/refs/tags/v1.15.tar.gz)
FetchContent_MakeAvailable(pugixml)

## argparse
FetchContent_Declare(argparse URL https://github.com/p-ranav/argparse/archive/refs/tags/v3.2.tar.gz)
FetchContent_MakeAvailable(argparse)

## cereal
set(SKIP_PERFORMANCE_COMPARISON ON CACHE INTERNAL "")
Set(BUILD_DOC OFF CACHE INTERNAL "")
Set(BUILD_SANDBOX OFF CACHE INTERNAL "")

FetchContent_Declare(cereal URL https://github.com/USCiLab/cereal/archive/refs/tags/v1.3.2.tar.gz)
FetchContent_MakeAvailable(cereal)

## raylib
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_Declare(raylib URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz)
FetchContent_MakeAvailable(raylib)

target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm pugixml argparse cereal raylib)

# Additional settings for macOS for raylib
if (APPLE)
    # Link necessary frameworks for macOS
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PUBLIC "-framework OpenGL")
endif()