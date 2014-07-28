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
    serializer/address.cpp \
    serializer/base58.cpp \
    serializer/bitcoin160.cpp \
    serializer/bitcoin256.cpp \
    serializer/byte.cpp \
    serializer/bytes.cpp \
    serializer/ec_private.cpp \
    serializer/ec_public.cpp \
    serializer/hd_key.cpp \
    serializer/hd_private.cpp \
    serializer/hd_public.cpp \
    serializer/point.cpp \
    serializer/wif.cpp \
    utility/config.cpp \
    utility/environment.cpp \
    utility/parameter.cpp \
    utility/printer.cpp \
    utility/utility.cpp

# Generated from XML data source.
libsx_la_SOURCES += \
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
    ec-new.cpp \
    ec-to-addr.cpp \
    ec-to-pub.cpp \
    ec-to-wif.cpp \
    genaddr.cpp \
    genpriv.cpp \
    genpub.cpp \
    hd-new.cpp \
    hd-priv.cpp \
    hd-pub.cpp \
    hd-to-address.cpp \
    hd-to-ec.cpp \
    hd-to-pub.cpp \
    hd-to-wif.cpp \
    help.cpp \
    initchain.cpp \
    monitor.cpp \
    mpk.cpp \
    newseed.cpp \
    qrcode.cpp \
    ripemd160.cpp \
    satoshi.cpp \
    sha160.cpp \
    sha256.cpp \
    sha512.cpp \
    stealth-addr.cpp \
    unwrap.cpp \
    wallet.cpp \
    wif-to-ec.cpp \
    wif-to-pub.cpp \
    wrap.cpp

# Generated from XML data source.
if HAVE_OBELISK
    libsx_la_SOURCES += \
        balance.cpp \
        fetch-header.cpp \
        fetch-last-height.cpp \
        fetch-public-key.cpp \
        fetch-stealth.cpp \
        fetch-transaction.cpp \
        fetch-transaction-index.cpp \
        fetch-utxo.cpp \
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
        $(libobelisk_LIBS)
endif
