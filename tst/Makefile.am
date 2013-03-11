# automake file for libgwaregame tests

AM_CPPFLAGS = $(LIBSDL_CFLAGS) \
    -I../src \
    -I../src/evt \
    -I../src/img \
    -I../src/log \
    -I../src/util

noinst_PROGRAMS = testapp testglapp testlog

testapp_SOURCES = \
    TestApp.cpp

testapp_LDADD = \
    ../src/libgwaregame.la

testglapp_SOURCES = \
    TestGlApp.cpp

testglapp_LDADD = \
    ../src/libgwaregame.la

testlog_SOURCES = \
    TestLogger.cpp

testlog_LDADD = \
    ../src/libgwaregame.la
