cmake_minimum_required(VERSION 3.10)
project(parser)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(libs/include)

add_executable(parser
        BeamDTO.cpp
        BeamDTO.h
        main.cpp
        ScenarioDTO.cpp
        ScenarioDTO.h
        WormDTO.cpp
        WormDTO.h
        YamlParser.cpp
        YamlParser.h)

target_link_libraries(parser ${PROJECT_SOURCE_DIR}/libs/libyaml-cpp.a)