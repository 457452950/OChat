cmake_minimum_required(VERSION 3.5)

project(OChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set windows nt version
add_definitions(-D_WIN32_WINNT=0x0A00)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets WebSockets)
find_package(asio CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

add_subdirectory("third_party/lazy_box")

set(PROJECT_SOURCES
        main.cpp

        common/log/logger.h common/log/logger.cpp

        common/config/clientsetting.h common/config/clientsetting.cpp
        common/config/config.h common/config/config.cpp

        cache/datacache.h cache/datacache.cpp

        widget/loginwidget.h widget/loginwidget.cpp

        widget/main_widget/usergroupboard.h widget/main_widget/usergroupboard.cpp
        widget/main_widget/chatsessionlist.h widget/main_widget/chatsessionlist.cpp
        widget/main_widget/friendlist.h widget/main_widget/friendlist.cpp
        widget/main_widget/chatgrouplist.h widget/main_widget/chatgrouplist.cpp
        widget/mainwidget.h widget/mainwidget.cpp
        widget/chat_widget/inputwidget.h widget/chat_widget/inputwidget.cpp
        widget/chat_widget/chathistorywidget.h widget/chat_widget/chathistorywidget.cpp
        widget/chatwidget.h widget/chatwidget.cpp

        data_structure/datasructures.h data_structure/datasructures.cpp

        backend/Room/Uid.h
        backend/backend.h backend/backend.cpp
        backend/Room/clientroom.h backend/Room/clientroom.cpp
        backend/Room/user.h backend/Room/user.cpp
        backend/Room/chatentry.h backend/Room/chatentry.cpp

        windowmanager.h windowmanager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(OChat
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET OChat APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(OChat SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(OChat
            ${PROJECT_SOURCES}
            vcpkg.json
        )
    endif()
endif()

target_include_directories(OChat PRIVATE "third_party/lazy_box/include")
target_link_libraries(OChat PRIVATE Qt${QT_VERSION_MAJOR}::Widgets asio::asio OpenSSL::SSL OpenSSL::Crypto Qt${QT_VERSION_MAJOR}::WebSockets lbox)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.OChat)
endif()
set_target_properties(OChat PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS OChat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(OChat)
endif()
