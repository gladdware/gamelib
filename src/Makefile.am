
AM_CPPFLAGS = $(PTHREAD_CFLAGS) $(LIBSDL_CFLAGS) $(LIBSDL_IMAGE_CFLAGS)
AM_LDFLAGS  = $(PTHREAD_LIBS)

lib_LTLIBRARIES = libgwaresdlgame.la

libgwaresdlgame_la_SOURCES = \
    log/Logger.cpp \
    evt/EventHandler.cpp \
    img/Surface.cpp \
    App.cpp

libgwaresdlgame_la_LIBADD = \
    $(LIBSDL_LIBS) \
    $(LIBSDL_IMAGE_LIBS)

libgwaresdlgame_la_LDFLAGS = -version-info 0:0:0

libgwaresdlgame_la_includedir = $(includedir)/gwaresdlgame

libgwaresdlgame_la_include_HEADERS = \
    log/Logger.h \
    evt/EventHandlerIntf.h \
    evt/EventHandler.h \
    img/Surface.h \
    App.h

