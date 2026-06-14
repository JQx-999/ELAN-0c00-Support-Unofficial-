cmake_minimum_required(VERSION 3.16)

project(PrejectOp VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(appPrejectOp
    main.cpp
    scripts/usb_handler.c
    scripts/enroll_handler.c
    scripts/remove_handler.c


)

qt_add_qml_module(appPrejectOp
    URI PrejectOp
    QML_FILES
        Main.qml
        RESOURCES Images/back.png
        RESOURCES
        RESOURCES Images/back.png Images/title.png
SOURCES scripts/usb_handler.h scripts/UsbBridge.h
QML_FILES MainMenu.qml
QML_FILES TestPage.qml
RESOURCES Images/back.mp4
QML_FILES about.qml
RESOURCES Images/anime.png
SOURCES
RESOURCES fonts/JetBrainsMono-Italic-VariableFont_wght.ttf fonts/JetBrainsMono-VariableFont_wght.ttf fonts/Montserrat-Italic-VariableFont_wght.ttf fonts/mont.ttf
SOURCES
RESOURCES
SOURCES
RESOURCES
SOURCES
RESOURCES
SOURCES scripts/enroll_handler.h scripts/enrollbridge.h
QML_FILES EnrollPage.qml
SOURCES scripts/remove_handler.h scripts/removebridge.h
QML_FILES DeletePage.qml
RESOURCES Images/icon.svg
RESOURCES Images/icon.png
SOURCES scripts/integration.h
RESOURCES scripts/elan_auth
QML_FILES
QML_FILES integration.qml
SOURCES scripts/removal.h
QML_FILES removal.qml


)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPrejectOp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPrejectOp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appPrejectOp
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Quick usb-1.0
)

install(TARGETS appPrejectOp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
