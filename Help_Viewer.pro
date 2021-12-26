QT += core gui widgets

CONFIG += c++11

# Windows application icon
RC_ICONS = Icon/Icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# All this escaping allows to provide a HELP_VIEWER_PROGRAM_NAME variable that contains spaces (declare it as HELP_VIEWER_PROGRAM_NAME="name with spaces" when calling qmake)
DEFINES += HELP_VIEWER_PROGRAM_NAME="\"\\\"$$HELP_VIEWER_PROGRAM_NAME\\\"\""

SOURCES += \
    Configuration.cpp \
    Main.cpp \
    MainWindow.cpp \
    RemoteControl.cpp

HEADERS += \
    Configuration.hpp \
    MainWindow.hpp \
    RemoteControl.hpp

FORMS += \
    MainWindow.ui

RESOURCES += \
    $$HELP_VIEWER_CONTENT_RESOURCE_FILE \
    Resources.qrc

TRANSLATIONS += \
    Translations/de.ts \
    Translations/es.ts \
    Translations/fr.ts \
    Translations/it.ts
