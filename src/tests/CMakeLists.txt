cmake_minimum_required(VERSION 3.1)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors" )

add_executable(tests
				tests.cpp
				../server/server_Radiocontrolled.cpp
				../server/server_Beam.cpp
				../server/server_Movement.cpp
				../server/server_Player.cpp
				../server/server_Stage.cpp
				../server/server_TurnsManager.cpp
				../server/server_Worm.cpp
				../server/server_Teletransportation.cpp
				../server/server_Armory.cpp
				../server/server_Dynamite.cpp)

target_link_libraries(tests Box2D)
