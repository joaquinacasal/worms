cmake_minimum_required(VERSION 3.1)
project(worms_server)

add_executable(worms_server
				server_NotifierThread.cpp
				notifications/server_StartTurnNotification.cpp
				notifications/server_EndTurnNotification.cpp
				notifications/server_ClosedConnectionNotification.cpp
				notifications/server_RadiocontrolledNotification.cpp
				notifications/server_RadiocontrolledExplosionNotification.cpp
				notifications/server_DynamiteNotification.cpp
				notifications/server_DynamiteExplosionNotification.cpp
				notifications/server_BeamNotification.cpp
				notifications/server_StageNotification.cpp
				notifications/server_WormNotification.cpp
				notifications/server_WormDeathNotification.cpp
				notifications/server_TurnTimeNotification.cpp
				notifications/server_YouWinNotification.cpp
				notifications/server_YouLoseNotification.cpp
				server_Radiocontrolled.cpp
				events/server_RadiocontrolledEvent.cpp
				events/server_DynamiteEvent.cpp
				server_Dynamite.cpp
				server_Armory.cpp
				server_Teletransportation.cpp
				notifications/server_MunitionsNotification.cpp
				server_Beam.cpp
				server_Main.cpp
				events/server_JumpBackwardEvent.cpp
				events/server_JumpForwardEvent.cpp
				events/server_TeletransportationEvent.cpp
				events/server_MoveRightEvent.cpp
				events/server_MoveLeftEvent.cpp
				events/server_StopMovingEvent.cpp
				events/server_ClosedConnectionEvent.cpp
				server_GameThread.cpp
				server_ProtocolTranslator.cpp
				server_ServerThread.cpp
				server_ClientHandler.cpp
				server_Movement.cpp
				server_Player.cpp
				server_Stage.cpp
				server_TurnsManager.cpp
				server_Worm.cpp
				../common/common_Socket.cpp
				../common/common_Thread.cpp
				../common/common_Lock.cpp
				../common/common_SocketProtocol.cpp)

target_link_libraries(worms_server Box2D pthread parser)

if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

install(TARGETS worms_server DESTINATION ${INSTALL_PATH}/worms/server/bin/)
install(DIRECTORY "scenarios" DESTINATION ${INSTALL_PATH}/worms/server)
install(DIRECTORY "config" DESTINATION ${INSTALL_PATH}/worms/server)
