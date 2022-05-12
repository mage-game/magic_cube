cmake_minimum_required(VERSION 3.16)

project("magic_cube")

find_package(folly REQUIRED)
find_package(Threads REQUIRED)
find_package(gflags REQUIRED)
find_package(glog REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g2 -Wall -std=c++17 -D_DEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE  "-O0 -g3 -Wall -std=c++17 -DNDEBUG")

set_and_check(FOLLY_INCLUDE_DIR /usr/local/include/folly)
set_and_check(FOLLY_CMAKE_DIR /usr/local/lib/cmake/folly)

if (NOT TARGET Folly::folly)
    include("${FOLLY_CMAKE_DIR}/folly-targets.cmake")
endif ()

set(FOLLY_LIBRARIES Folly::folly)

if (NOT folly_FIND_QUIETLY)
    message(STATUS "Found folly: ${PACKAGE_PREFIX_DIR}")
endif ()

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/archive)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/library)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 包含子项目。
add_subdirectory("code/framework")
add_subdirectory("code/plugins/network_plugin")
add_subdirectory("code/servers/center_server")
add_subdirectory("code/servers/log_server")

