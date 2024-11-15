cmake_minimum_required(VERSION 3.16)

project(Help_Viewer VERSION 1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    LinguistTools
    Widgets
)

qt_standard_project_setup()

# Make sure the mandatory command line variables are set
if (NOT DEFINED HELP_VIEWER_PROGRAM_NAME)
    message(FATAL_ERROR "The 'HELP_VIEWER_PROGRAM_NAME' variable must be defined with the program displayed name (use quotes around the name if it contains the space character).")
endif()
if (NOT DEFINED HELP_VIEWER_CONTENT_RESOURCE_FILE)
    message(FATAL_ERROR "The 'HELP_VIEWER_CONTENT_RESOURCE_FILE' variable must be defined with the path to the Qt resource file containing the help documents to display.")
endif()

add_compile_definitions(HELP_VIEWER_PROGRAM_NAME="\"${HELP_VIEWER_PROGRAM_NAME}\"")

# Allow to use global paths in local application includes
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(PROJECT_SOURCES
    Configuration.cpp
    Configuration.hpp
    Main.cpp
    MainWindow.cpp
    MainWindow.hpp
    MainWindow.ui
    RemoteControl.cpp
    RemoteControl.hpp
)

# Resources must be specified before the executable, so the resulting source file can be embedded in the executable
set(PROJECT_RESOURCES "")
qt_add_resources(PROJECT_RESOURCES
    ${HELP_VIEWER_CONTENT_RESOURCE_FILE}
    Resources.qrc
)

qt_add_executable(Help_Viewer
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES}
)

set_target_properties(Help_Viewer PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "Help Viewer"
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(Help_Viewer
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS Help_Viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
