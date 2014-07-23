# ******** GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY ********* #

AUTOMAKE_OPTIONS = subdir-objects

# Library
noinst_LTLIBRARIES = libsx.la

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

libsx_la_SOURCES = \
    dispatch.cpp \
    display.cpp \
    generated.cpp \
    utility/coin.cpp \
    utility/config.cpp \
    utility/console.cpp \
    utility/environment.cpp \
    utility/parameter.cpp \
    utility/printer.cpp

# Generated from XML data source.
libsx_la_SOURCES += \
    addr.cpp \
    addr-decode.cpp \
    addr-embed.cpp \
    addr-encode.cpp \
    addr-validate.cpp \
    base58-decode.cpp \
    base58-encode.cpp \
    base58check-decode.cpp \
    base58check-encode.cpp \
    bci-fetch-last-height.cpp \
    bci-history.cpp \
    bci-send-transaction.cpp \
    be-fetch-transaction.cpp \
    bitcoin160.cpp \
    bitcoin256.cpp \
    brainwallet.cpp \
    btc.cpp \
    ec-add.cpp \
    ec-add-secrets.cpp \
    ec-multiply.cpp \
    ec-multiply-secrets.cpp \
    ec-to-wif.cpp \
    genaddr.cpp \
    genpriv.cpp \
    genpub.cpp \
    get-pubkey.cpp \
    hd-priv.cpp \
    hd-pub.cpp \
    hd-seed.cpp \
    hd-to-address.cpp \
    hd-to-wif.cpp \
    help.cpp \
    mpk.cpp \
    newkey.cpp \
    newseed.cpp \
    qrcode.cpp \
    ripemd160.cpp \
    satoshi.cpp \
    sha1.cpp \
    sha256.cpp \
    sha512.cpp \
    stealth-addr.cpp \
    unwrap.cpp \
    wif-to-ec.cpp \
    wrap.cpp

# Generated from XML data source.
if HAVE_OBELISK
    libsx_la_SOURCES += \
        balance.cpp \
        fetch-header-hash.cpp \
        fetch-header-height.cpp \
        fetch-last-height.cpp \
        fetch-stealth.cpp \
        fetch-transaction.cpp \
        fetch-transaction-index.cpp \
        get-utxo.cpp \
        history.cpp \
        watchtx.cpp \
        obelisk_client.cpp

    AM_CPPFLAGS += \
        ${libobelisk_CFLAGS} \
        -DSYSCONFDIR="${sysconfdir}"
endif

# Console Application
bin_PROGRAMS = sx

sx_SOURCES = \
    console/main.cpp

sx_LDADD = \
    -L$(srcdir) -lsx \
    $(libbitcoin_LIBS) \
    $(libwallet_LIBS) \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system

if HAVE_OBELISK
    sx_LDADD += \
        $(libobelisk_LIBS) \
        -lncurses
endif
