find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(StageManager
  main.cpp
  MainWindow.cpp
  MainWindow.h
  MainWindow.ui
  SystemTray.cpp
  SystemTray.h
  SystemTrayMenu.cpp
  SystemTrayMenu.h
  Application.cpp
  Application.h
)

target_link_libraries(StageManager PRIVATE Qt5::Widgets libStageManager)
