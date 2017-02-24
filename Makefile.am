ACLOCAL_AMFLAGS=-I m4

AUTOMAKE_OPTIONS = subdir-objects
AM_CPPFLAGS = -Wfatal-errors $(BOOST_CPPFLAGS) $(PTHREAD_CFLAGS)
AM_LDFLAGS=$(BOOST_LDFLAGS) $(OPENSSL_LDFLAGS)

lib_LIBRARIES = libsecxx.a

libsecxx_a_SOURCES = src/sec_connection.cpp
	src/url.cpp
libsecxx_a_LIBADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) $(PTHREAD_CFLAGS)
 
pkgconfigdir = /usr/lib/pkgconfig
pkgconfig_DATA = sec.pc

nobase_include_HEADERS = src/sec.h

bin_PROGRAMS = 	xbrl

xbrl_LDADD = $(BOOST_DATE_TIME_LIB) $(BOOST_SYSTEM_LIB) $(OPENSSL_LIBS) $(PTHREAD_CFLAGS)

xbrl_SOURCES = src/url.cpp \
		src/sec_connection.cpp\
		src/url_helper.cpp\
		src/client.cpp\
		src/url.cpp\
		src/main.cpp