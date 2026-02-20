include_directories(deloreandb include)

set(KERNEL_SOURCES kernels/scalar.cc kernels/kernel.cc)

if (DELOREAN_SIMD STREQUAL "AVX512")
  list(APPEND KERNEL_SOURCES kernels/avx512.cc kernels/avx2.cc kernels/sse41.cc kernels/sse2.cc)
elseif (DELOREAN_SIMD STREQUAL "AVX2")
      list(APPEND KERNEL_SOURCES kernels/avx2.cc kernels/sse41.cc kernels/sse2.cc)
elseif (DELOREAN_SIMD STREQUAL "SSE41")
      list(APPEND KERNEL_SOURCES kernels/sse41.cc kernels/sse2.cc)
elseif (DELOREAN_SIMD STREQUAL "SSE2")
  list(APPEND KERNEL_SOURCES kernels/sse2.cc)
endif()

add_library(deloreandb 
deloreandb.cc 
mem/arena_alloc.cc 
${KERNEL_SOURCES}
)

set_source_files_properties(kernels/sse2.cc PROPERTIES COMPILE_FLAGS "-msse2")
set_source_files_properties(kernels/sse41.cc PROPERTIES COMPILE_FLAGS "-msse4.1")
set_source_files_properties(kernels/avx2.cc PROPERTIES COMPILE_FLAGS "-mavx2")
set_source_files_properties(kernels/avx512.cc PROPERTIES COMPILE_FLAGS "-mavx512f -mavx512dq")


target_include_directories(deloreandb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(deloreandb PUBLIC cxx_std_23)

if (MSVC) 
add_compile_options(delorean PRIVATE /W4)
else()
add_compile_options(delorean PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(system)