AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS = sx_test

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

#sx_test_HEADERS = \
     command.hpp

sx_test_SOURCES = \
    addr.cpp \
    address.cpp \
    addr-decode.cpp \
    addr-encode.cpp \
    balance.cpp \
    base58.cpp \
    base58check-decode.cpp \
    base58check-encode.cpp \
    base58-decode.cpp \
    base58-encode.cpp \
    bci-fetch-last-height.cpp \
    bci-history.cpp \
    bci-send-transaction.cpp \
    be-fetch-transaction.cpp \
    brainwallet.cpp \
    btc.cpp \
    ec-add.cpp \
    ec-add-secrets.cpp \
    ec-multiply.cpp \
    ec-multiply-secrets.cpp \
    embed-addr.cpp \
    fetch-header-hash.cpp \
    fetch-header-height.cpp \
    fetch-last-height.cpp \
    fetch-stealth.cpp \
    fetch-transaction.cpp \
    fetch-transaction-index.cpp \
    genaddr.cpp \
    generated__broadcast.cpp \
    generated__find.cpp \
    generated__symbol.cpp \
    genpriv.cpp \
    genpub.cpp \
    get-pubkey.cpp \
    get-utxo.cpp \
    hd-priv.cpp \
    hd-pub.cpp \
    help.cpp \
    history.cpp \
    main.cpp \
    parameter.cpp \
    printer.cpp \
    qrcode.cpp \
    satoshi.cpp \
    stealth-addr.cpp \
    unwrap.cpp \
    watchtx.cpp \
    wrap.cpp

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

