cmake_minimum_required(VERSION 3.20)

project(deloreandb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC) 
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


add_subdirectory(Engine/Source)

add_library(deloreandb ${SOURCE_FILES})

add_executable(deloreandb-cli ${PROJECT_SOURCE_DIR}/Engine/Source/main.cc)

target_link_libraries(deloreandb-cli PRIVATE deloreandb)
target_compile_features(deloreandb PRIVATE cxx_std_23)

add_definitions(-DDEBUG_ENABLED)