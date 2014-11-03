cmake_minimum_required(VERSION 2.8)

project(igloo)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/cotire/CMake")
include(cotire)

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP ")
else()
  # Assume GCC-style arguments
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels -Wshadow -pedantic-errors")
endif()


FILE(GLOB IglooTestSourceFiles tests/*.cpp tests/**/*.cpp)
add_executable(igloo-tests ${IglooTestSourceFiles})
set_target_properties(igloo-tests PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "tests/igloo_self_test.h")
set_target_properties(igloo-tests PROPERTIES COTIRE_ADD_UNIT_BUILD FALSE)
# cotire(igloo-tests)

set(cfg "C++" CACHE STRING "Configuration for snowhouse")
add_subdirectory(igloo/external/snowhouse)

add_custom_command(TARGET igloo-tests
                   POST_BUILD
                   COMMAND igloo-tests
                   WORKING_DIRECTORY ./bin)

add_custom_command(TARGET snowhouse-tests
                   POST_BUILD
                   COMMAND snowhouse-tests
                   WORKING_DIRECTORY ./bin)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/igloo
        DESTINATION include/
        FILES_MATCHING PATTERN "*.h"
        PATTERN "igloo/external/snowhouse/example" EXCLUDE)
