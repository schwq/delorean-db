include_directories(deloreandb include)


add_library(deloreandb deloreandb.cc mem/arena_alloc.cc)

target_include_directories(deloreandb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(deloreandb PUBLIC cxx_std_23)

if (MSVC) 
add_compile_options(delorean PRIVATE /W4)
else()
add_compile_options(delorean PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(system)