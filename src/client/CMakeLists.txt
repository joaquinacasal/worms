cmake_minimum_required(VERSION 3.1)
project(worms_client)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic -pedantic-errors" )

add_executable(worms_client
				capturedEvents/client_CapturedEventFactory.cpp
				capturedEvents/client_TeletransportationCapturedEvent.cpp
				capturedEvents/client_RadiocontrolledCapturedEvent.cpp
				capturedEvents/client_ClosedConnectionCapturedEvent.cpp
				capturedEvents/client_DynamiteCapturedEvent.cpp
				capturedEvents/client_JumpBackwardCapturedEvent.cpp
				capturedEvents/client_JumpForwardCapturedEvent.cpp
				capturedEvents/client_StopMovingCapturedEvent.cpp
				capturedEvents/client_MoveRightCapturedEvent.cpp
				capturedEvents/client_MoveLeftCapturedEvent.cpp
				capturedEvents/client_CapturedEventSender.cpp
				client_ConsoleDrawer.cpp
				drawables/client_DrawableFactory.cpp
				drawables/client_BeamDrawable.cpp
				drawables/client_ClosedConnectionDrawable.cpp
				drawables/client_DynamiteDrawable.cpp
				drawables/client_DynamiteExplosionDrawable.cpp
				drawables/client_MunitionsDrawable.cpp
				drawables/client_EndTurnDrawable.cpp
				drawables/client_RadiocontrolledDrawable.cpp
				drawables/client_RadiocontrolledExplosionDrawable.cpp
				drawables/client_StageDrawable.cpp
				drawables/client_StartTurnDrawable.cpp
				drawables/client_TurnTimeDrawable.cpp
				drawables/client_YouWinDrawable.cpp
				drawables/client_YouLoseDrawable.cpp
				drawables/client_WormDrawable.cpp
				drawables/client_WormDeathDrawable.cpp
				client_SdlWindow.cpp
				client_SdlException.cpp
				client_Area.cpp
				client_SdlTexture.cpp
				client_WormRepresentation.cpp
				client_Message.cpp
				client_MunitionsInformation.cpp
				client_FontFactory.cpp
				client_ColorsFactory.cpp
				client_TextureFactory.cpp
				client_Animation.cpp
				client_Camera.cpp
				client_Main.cpp
				../common/common_SocketProtocol.cpp
				../common/common_Socket.cpp
				../common/common_Thread.cpp
				../common/common_Lock.cpp)

target_link_libraries(worms_client pthread SDL2 SDL2_image SDL2_ttf)

if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

install(TARGETS worms_client DESTINATION ${INSTALL_PATH}/worms/client/bin/)
install(DIRECTORY "assets" DESTINATION ${INSTALL_PATH}/worms/client)
install(DIRECTORY "backgrounds" DESTINATION ${INSTALL_PATH}/worms/client)
