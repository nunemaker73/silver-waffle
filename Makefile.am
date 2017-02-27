ACLOCAL_AMFLAGS=-I m4

AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = $(BOOST_CPPFLAGS) $(XERCES_CFLAGS) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS) $(OPENSSL_LDFLAGS) $(XERCES_LDFLAGS) $(PTHREAD_CFLAGS)

bin_PROGRAMS = 	xbrl
xbrl_SOURCES = src/url.cpp \
		src/reports.cpp\
		src/main.cpp

xbrl_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) 

pkgconfigdir = /usr/lib/pkgconfig
pkgconfig_DATA = sec.pc

nobase_include_HEADERS = src/sec.h

lib_LIBRARIES = libsecxx.a
libsecxx_a_SOURCES = src/reports.cpp\
	src/url.cpp

