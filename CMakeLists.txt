cmake_minimum_required(VERSION 3.5)

project(StageManager LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(StageManager
      main.cpp
      ui/MainWindow.cpp
      ui/MainWindow.h
      ui/MainWindow.ui
      ui/SystemTray.cpp
      ui/SystemTray.h
      ui/SystemTrayMenu.cpp
      ui/SystemTrayMenu.h
      ui/Application.cpp
      ui/Application.h
      ui/SettingsWindow.cpp
      ui/SettingsWindow.h
      ui/SettingsWindow.ui
      ui/ProcessTabWidget.cpp
      ui/ProcessTabWidget.h
      ui/ProcessWidget.cpp
      ui/ProcessWidget.h
      ui/ProcessWidget.ui
      system/Action.h
      system/Action.cpp
      system/Mount.h
      system/Mount.cpp
      system/Umount.cpp
      system/Umount.h
      system/Mkdir.cpp
      system/Mkdir.h
      system/Cp.cpp
      system/Cp.h
      system/Rm.cpp
      system/Rm.h
      system/CompressionAction.cpp
      system/CompressionAction.h
      system/Compress.cpp
      system/Compress.h
      system/Uncompress.cpp
      system/Uncompress.h
      system/Settings.cpp
      system/Settings.h
)

target_link_libraries(StageManager PRIVATE Qt5::Widgets)
