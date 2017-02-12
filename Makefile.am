ACLOCAL_AMFLAGS=-I m4

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = $(BOOST_CPPFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)

lib_LIBRARIES = libsecxx.a

libsecxx_a_SOURCES = src/getCIK.cpp \
	src/sec_info.cpp \
	src/url.cpp
 
pkgconfigdir = /usr/lib/pkgconfig
pkgconfig_DATA = sec.pc

nobase_include_HEADERS = src/sec_info.h \
	src/xbrl.h

bin_PROGRAMS = 	xbrl


xbrl_SOURCES = src/sec_info.cpp \
		src/url.cpp \
		src/sec_connection.cpp\
		src/url_helper.cpp\
		src/main.cpp