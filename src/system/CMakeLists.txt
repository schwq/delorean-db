if(WIN32)
    set(SYSTEM_SRC win)
elseif(APPLE)
    set(SYSTEM_SRC mac)
elseif(UNIX)
    set(SYSTEM_SRC linux)
else() 
    set(SYSTEM_SRC fallback)
endif()

target_sources(deloreandb PRIVATE 
    ${PROJECT_SOURCE_DIR}/src/include/deloreandb/system/cache_info.hpp
    ${PROJECT_SOURCE_DIR}/src/system/${SYSTEM_SRC}/cache_info.cc
)