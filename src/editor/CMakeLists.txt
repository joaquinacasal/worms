cmake_minimum_required(VERSION 3.1)

project(worms_editor)

set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

include_directories(${PROJECT_BINARY_DIR})
include_directories(.)

set(SOURCES
    main.cpp
    mainwindow.cpp
    dragwidget.cpp
    draglabel.cpp
    dialog.cpp
)

qt5_wrap_ui(UIS_HEADERS
        mainwindow.ui
        dialog.ui
)

qt5_add_resources(ICONS icons.qrc)

add_executable(worms_editor ${SOURCES} ${UIS_HEADERS} ${ICONS})

target_link_libraries(worms_editor Qt5::Widgets Qt5::Core Qt5::Gui yaml-cpp)

if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

install(TARGETS worms_editor DESTINATION ${INSTALL_PATH}/worms/editor/bin/)
install(DIRECTORY "scenarios" DESTINATION ${INSTALL_PATH}/worms/editor)
install(DIRECTORY "resources" DESTINATION ${INSTALL_PATH}/worms/editor)
install(FILES ${ICONS} DESTINATION ${INSTALL_PATH}/worms/editor/resources)
