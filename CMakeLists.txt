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

        common/config/client_setting.h common/config/client_setting.cpp
        common/config/config.h common/config/config.cpp
        common/log/logger.h common/log/logger.cpp
        common/debug.h

        cache/data_cache.h cache/data_cache.cpp

        widget/main_widget/shown_board.h widget/main_widget/shown_board.cpp
        widget/main_widget/session_list.h widget/main_widget/session_list.cpp
        widget/main_widget/friend_list.h widget/main_widget/friend_list.cpp
        widget/main_widget/room_list.h widget/main_widget/room_list.cpp

        widget/chat_widget/input_widget.h widget/chat_widget/input_widget.cpp
        widget/chat_widget/chat_history_widget.h widget/chat_widget/chat_history_widget.cpp

        widget/main_widget.h widget/main_widget.cpp
        widget/chat_widget.h widget/chat_widget.cpp
        widget/login_widget.h widget/login_widget.cpp

        widget/wrapper.h widget/wrapper.cpp

        backend/backend.h backend/backend.cpp
        backend/Room/client_room.h backend/Room/client_room.cpp
        backend/Room/user.h backend/Room/user.cpp
        backend/Room/chat_entry.h backend/Room/chat_entry.cpp

        window_manager.h window_manager.cpp

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

target_include_directories(OChat PRIVATE "third_party/lazy_box/include" "./")
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
