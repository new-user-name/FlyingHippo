QT += qml quick widgets
QT_CONFIG -= no-pkg-config

LANGUAGE = C++

CONFIG += c++17
CONFIG += sdk_no_version_check

MOC_DIR = $${OUT_PWD}/moc

include(platforms.pri)

LinuxBuild {
    QT += x11extras waylandclient
    CONFIG += link_pkgconfig
    PKGCONFIG   += gstreamer-1.0 gstreamer-video-1.0 gstreamer-gl-1.0 egl
    CONFIG      += VideoEnabled
} else:MacBuild {
    #- gstreamer framework installed by the gstreamer devel installer
    GST_ROOT = /Library/Frameworks/GStreamer.framework
    exists($$GST_ROOT) {
        CONFIG      += VideoEnabled
        INCLUDEPATH += $$GST_ROOT/Headers
        LIBS        += -F/Library/Frameworks -framework GStreamer
    }
} else:iOSBuild {
    #- gstreamer framework installed by the gstreamer iOS SDK installer (default to home directory)
    GST_ROOT = $$(HOME)/Library/Developer/GStreamer/iPhone.sdk/GStreamer.framework
    exists($$GST_ROOT) {
        CONFIG      += VideoEnabled
        INCLUDEPATH += $$GST_ROOT/Headers
        LIBS        += -F$$(HOME)/Library/Developer/GStreamer/iPhone.sdk -framework GStreamer -framework AVFoundation -framework CoreMedia -framework CoreVideo -framework VideoToolbox -liconv -lresolv
    }
} else:WindowsBuild {
    #- gstreamer installed by default under c:/gstreamer
    GST_ROOT = c:/gstreamer/1.0/msvc_x86_64
    #GST_ROOT = C:/gstreamer/1.0/mingw_x86_64

    exists($$GST_ROOT) {
        CONFIG      += VideoEnabled

        LIBS        += -L$$GST_ROOT/lib -lgstreamer-1.0 -lgstgl-1.0 -lgstvideo-1.0 -lgstbase-1.0
        LIBS        += -lglib-2.0 -lintl -lgobject-2.0

        INCLUDEPATH += \
            $$GST_ROOT/include \
            $$GST_ROOT/include/gstreamer-1.0 \
            $$GST_ROOT/include/glib-2.0 \
            $$GST_ROOT/lib/gstreamer-1.0/include \
            $$GST_ROOT/lib/glib-2.0/include

        DESTDIR_WIN = $$replace(DESTDIR, "/", "\\")
        GST_ROOT_WIN = $$replace(GST_ROOT, "/", "\\")

        # Copy main GStreamer runtime files
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\bin\*.dll\" \"$$DESTDIR_WIN\" /S/Y $$escape_expand(\\n)
        QMAKE_POST_LINK += xcopy \"$$GST_ROOT_WIN\\bin\*.\" \"$$DESTDIR_WIN\" /S/Y $$escape_expand(\\n)

        # Copy GStreamer plugins
        QMAKE_POST_LINK += $$escape_expand(\\n) xcopy \"$$GST_ROOT_WIN\\lib\\gstreamer-1.0\\*.dll\" \"$$DESTDIR_WIN\\gstreamer-plugins\\\" /Y $$escape_expand(\\n)
    }
} else:AndroidBuild {
    #- gstreamer assumed to be installed in $$PWD/../gstreamer-1.0-android-universal-1.18.1/***
    contains(QT_ARCH, arm) {
        GST_ROOT = c:/gstreamer/armv7
    } else:contains(QT_ARCH, arm64) {
        GST_ROOT = c:/gstreamer/arm64
    } else {
        GST_ROOT = c:/gstreamer/x86
    }
    exists($$GST_ROOT) {
        QMAKE_CXXFLAGS  += -pthread
        CONFIG          += VideoEnabled

        # We want to link these plugins statically
        LIBS += -L$$GST_ROOT/lib/gstreamer-1.0 \
            -lgstvideo-1.0 \
            -lgstcoreelements \
            -lgstplayback \
            -lgstudp \
            -lgstrtp \
            -lgstrtsp \
            -lgstx264 \
            -lgstlibav \
            -lgstsdpelem \
            -lgstvideoparsersbad \
            -lgstrtpmanager \
            -lgstisomp4 \
            -lgstmatroska \
            -lgstmpegtsdemux \
            -lgstandroidmedia \
            -lgstopengl \
            -lgsttcp

        # Rest of GStreamer dependencies
        LIBS += -L$$GST_ROOT/lib \
            -lgraphene-1.0 -ljpeg -lpng16 \
            -lgstfft-1.0 -lm  \
            -lgstnet-1.0 -lgio-2.0 \
            -lgstphotography-1.0 -lgstgl-1.0 -lEGL \
            -lgstaudio-1.0 -lgstcodecparsers-1.0 -lgstbase-1.0 \
            -lgstreamer-1.0 -lgstrtp-1.0 -lgstpbutils-1.0 -lgstrtsp-1.0 -lgsttag-1.0 \
            -lgstvideo-1.0 -lavformat -lavcodec -lavutil -lx264 -lavfilter -lswresample \
            -lgstriff-1.0 -lgstcontroller-1.0 -lgstapp-1.0 \
            -lgstsdp-1.0 -lbz2 -lgobject-2.0 -lgstmpegts-1.0 \
            -Wl,--export-dynamic -lgmodule-2.0 -pthread -lglib-2.0 -lorc-0.4 -liconv -lffi -lintl \

        INCLUDEPATH += \
            $$GST_ROOT/include/gstreamer-1.0 \
            $$GST_ROOT/lib/gstreamer-1.0/include \
            $$GST_ROOT/include/glib-2.0 \
            $$GST_ROOT/lib/glib-2.0/include
    }
}

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += MAVLINK_COMM_NUM_BUFFERS=32

INCLUDEPATH += $${PWD}/mavlink/common
INCLUDEPATH += "C:/gstreamer/1.0/msvc_x86_64/include/gstreamer-1.0/"
INCLUDEPATH += "C:/gstreamer/1.0/msvc_x86_64/include/glib-2.0"
INCLUDEPATH += "C:/gstreamer/1.0/msvc_x86_64/lib/glib-2.0/include"


#INCLUDEPATH += "C:/gstreamer/1.0/mingw_x86_64/include/gstreamer-1.0/"
#INCLUDEPATH += "C:/gstreamer/1.0/mingw_x86_64/include/glib-2.0"
#INCLUDEPATH += "C:/gstreamer/1.0/mingw_x86_64/lib/glib-2.0/include"

SOURCES += \
        main.cc	\
        Vehicle.cc

RESOURCES += qml.qrc

QML_IMPORT_PATH =
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Vehicle.h

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_ABIS = \
        armeabi-v7a
}
