cmake_minimum_required(VERSION 3.16)

project(MusicPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick MultiMedia)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appMusicPlayer
    main.cpp
)

qt_add_qml_module(appMusicPlayer
    URI MusicPlayer
    QML_FILES
        Main.qml
        QML_FILES AudioInfoBox.qml
        QML_FILES ImageButton.qml

    RESOURCES
    assets/images/song_1.jpg
    assets/images/song_2.jpg
    assets/images/song_3.jpg

    assets/videos/video_1.avi

    assets/icons/app_icon.ico
    assets/icons/next_icon.png
    assets/icons/pause_icon.png
    assets/icons/play_icon.png
    assets/icons/previous_icon.png
    assets/icons/add_icon.png
     assets/icons/menu_icon.png
     assets/icons/trash_icon.png

    assets/audio/FlyMeToTheMoon.mpeg
    assets/audio/RollingInTheDeep.mpeg
    assets/audio/TeachMeTonight.mpeg
    assets/audio/SetFireToTheRain.mp4

    SOURCES PlayerController.h PlayerController.cpp
    SOURCES AudioInfo.h AudioInfo.cpp
    QML_FILES PlayListPanel.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMusicPlayer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMusicPlayer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appMusicPlayer
    PRIVATE Qt6::Quick Qt6::Multimedia
)

install(TARGETS appMusicPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
