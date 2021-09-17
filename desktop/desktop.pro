TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

LIBS += \
    $$(JAVA_HOME)/lib/jvm.lib


INCLUDEPATH += $$(JAVA_HOME)/include \
               $$(JAVA_HOME)/include/win32
#error($$(JAVA_HOME))
