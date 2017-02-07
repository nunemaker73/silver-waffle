ACLOCAL_AMFLAGS=-I m4

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = $(BOOST_CPPFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS)

lib_LIBRARIES = libsec++.a
libsec++_a_LDADD=
libsec++_a_SOURCES = src/getCIK.cpp \
	src/sec_info.cpp
 
pkgconfigdir = /usr/lib/pkgconfig
pkgconfig_DATA = sec.pc

nobase_include_HEADERS = src/sec_info.h \
	src/xbrl.h

bin_PROGRAMS = 	xbrl
xbrl_LDADD = 

xbrl_SOURCES = src/getCIK.cpp\
		src/sec_info.cpp\
		src/main.cpp