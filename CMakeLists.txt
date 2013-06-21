cmake_minimum_required(VERSION 2.8)

project(igloo)

include_directories("${PROJECT_SOURCE_DIR}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin)

set(CMAKE_CXX_FLAGS "-Wfatal-errors -Wall -W -Werror -Wfloat-equal -Wundef -Wendif-labels -Wshadow -pedantic-errors")
FILE(GLOB IglooTestSourceFiles tests/*.cpp)

add_executable(igloo-tests ${IglooTestSourceFiles})

add_custom_command(TARGET igloo-tests
                   POST_BUILD
                   COMMAND igloo-tests
                   WORKING_DIRECTORY ./bin)
