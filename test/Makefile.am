AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS = sx_test

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

sx_test_HEADERS = \
    setup.hpp

sx_test_SOURCES = \
    console__line_out.cpp \
    generated__broadcast.cpp \
    generated__find.cpp \
    generated__symbol.cpp \
    stealth_addr.cpp \
    main.cpp

sx_test_LDADD = \
    -L$(srcdir)/../src/ -lsx \
    $(libbitcoin_LIBS) \
    $(libwallet_LIBS) \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system \
    -lboost_unit_test_framework
    
if HAVE_OBELISK
    AM_CPPFLAGS += \
        ${libobelisk_CFLAGS} \
        -DBOOST_TEST_DYN_LINK
        
    sx_test_LDADD += \
        $(libobelisk_LIBS) \
        -lncurses
endif

