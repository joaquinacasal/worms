cmake_minimum_required(VERSION 3.1)
project(worms_client)

add_executable(worms_client
				client_CapturedEventSender.cpp
				client_CapturedEventFactory.cpp
				client_TeletransportationCapturedEvent.cpp
				client_RadiocontrolledCapturedEvent.cpp
				client_ClosedConnectionCapturedEvent.cpp
				client_DynamiteCapturedEvent.cpp
				client_JumpBackwardCapturedEvent.cpp
				client_JumpForwardCapturedEvent.cpp
				client_StopMovingCapturedEvent.cpp
				client_MoveRightCapturedEvent.cpp
				client_MoveLeftCapturedEvent.cpp
				client_ConsoleDrawer.cpp
				client_DrawableFactory.cpp
				client_BeamDrawable.cpp
				client_ClosedConnectionDrawable.cpp
				client_DynamiteDrawable.cpp
				client_DynamiteExplosionDrawable.cpp
				client_EndTurnDrawable.cpp
				client_RadiocontrolledDrawable.cpp
				client_RadiocontrolledExplosionDrawable.cpp
				client_StageDrawable.cpp
				client_StartTurnDrawable.cpp
				client_TurnTimeDrawable.cpp
				client_YouWinDrawable.cpp
				client_WormDrawable.cpp
				client_WormDeathDrawable.cpp
				client_SdlWindow.cpp
				client_SdlException.cpp
				client_Area.cpp
				client_SdlTexture.cpp
				client_WormRepresentation.cpp
				client_TurnMessage.cpp
				client_YouWinMessage.cpp
				client_FontFactory.cpp
				client_ColorsFactory.cpp
				client_TextureFactory.cpp
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
