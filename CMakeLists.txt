cmake_minimum_required(VERSION 3.1)
project(worms)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )

include_directories(${PROJECT_SOURCE_DIR})
message("Headers generados: ${PROJECT_SOURCE_DIR}")

set( BOX2D_BUILD_STATIC ON )

add_subdirectory(Box2D)
add_subdirectory(src/server/scenario_parser)
add_subdirectory(src/server)
add_subdirectory(src/client)
add_subdirectory(src/tests)
add_subdirectory(src/editor)
