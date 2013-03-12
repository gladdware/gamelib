# automake for libgwaregame

include ../Common.mk

AM_CPPFLAGS = \
    $(GWAREGAME_IPATH) \
    $(PTHREAD_CFLAGS) \
    $(LIBGL_CFLAGS) \
    $(LIBGLU_CFLAGS) \
    $(LIBSDL_CFLAGS) \
    $(LIBSDL_IMAGE_CFLAGS)

AM_LDFLAGS  = $(PTHREAD_LIBS)

lib_LTLIBRARIES = libgwaregame.la

libgwaregame_la_SOURCES = \
    log/Logger.cpp \
    evt/EventHandler.cpp \
    img/Surface.cpp \
    util/FpsCounter.cpp \
    util/OpenglErr.cpp \
    map/Tile.cpp \
    App.cpp \
    OpenglApp.cpp

libgwaregame_la_LIBADD = \
    $(LIBGL_LIBS) \
    $(LIBGLU_LIBS) \
    $(LIBSDL_LIBS) \
    $(LIBSDL_IMAGE_LIBS)

libgwaregame_la_LDFLAGS = -version-info 1:0:1

libgwaregame_la_includedir = $(includedir)/gwaregame

libgwaregame_la_include_HEADERS = \
    log/Logger.h \
    evt/EventHandlerIntf.h \
    evt/EventHandler.h \
    img/Surface.h \
    util/FpsCounter.h \
    util/OpenglErr.h \
    map/Tile.h \
    App.h \
    OpenglApp.h

