cmake_minimum_required(VERSION 3.1)
project(worms_server)

add_executable(worms_server
				server_NotifierThread.cpp
				server_StartTurnNotification.cpp
				server_EndTurnNotification.cpp
				server_ClosedConnectionNotification.cpp
				server_RadiocontrolledNotification.cpp
				server_RadiocontrolledExplosionNotification.cpp
				server_DynamiteNotification.cpp
				server_DynamiteExplosionNotification.cpp
				server_BeamNotification.cpp
				server_StageNotification.cpp
				server_WormNotification.cpp
				server_TurnTimeNotification.cpp
				server_Radiocontrolled.cpp
				server_RadiocontrolledEvent.cpp
				server_DynamiteEvent.cpp
				server_Dynamite.cpp
				server_Armory.cpp
				server_Teletransportation.cpp
				server_Beam.cpp
				server_Main.cpp
				server_JumpBackwardEvent.cpp
				server_JumpForwardEvent.cpp
				server_TeletransportationEvent.cpp
				server_MoveRightEvent.cpp
				server_MoveLeftEvent.cpp
				server_StopMovingEvent.cpp
				server_ClosedConnectionEvent.cpp
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
