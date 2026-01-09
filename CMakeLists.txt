cmake_minimum_required(VERSION 3.20)

project(deloreandb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)
FetchContent_Declare(
    googletest 
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(deloreandb-cli src/include)

add_subdirectory(test)
add_subdirectory(src)

add_executable(deloreandb-cli ${PROJECT_SOURCE_DIR}/src/main.cc)

target_link_libraries(deloreandb-cli PRIVATE deloreandb)

add_definitions(-DDEBUG_ENABLED)