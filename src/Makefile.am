# ******** GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY ********* #

AUTOMAKE_OPTIONS = subdir-objects

# Library
noinst_LTLIBRARIES = libsx.la

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

libsx_la_SOURCES = \
    async_client.cpp \
    callback_state.cpp \
    dispatch.cpp \
    display.cpp \
    generated.cpp \
    prop_tree.cpp \
    serializer/address.hpp \
    serializer/base58.hpp \
    serializer/btc160.hpp \
    serializer/btc256.hpp \
    serializer/byte.hpp \
    serializer/ec_private.hpp \
    serializer/ec_public.hpp \
    serializer/encoding.hpp \
    serializer/hd_key.hpp \
    serializer/hd_private.hpp \
    serializer/hd_public.hpp \
    serializer/header.hpp \
    serializer/hex.hpp \
    serializer/input.hpp \
    serializer/output.hpp \
    serializer/point.hpp \
    serializer/prefix.hpp \
    serializer/raw.hpp \
    serializer/script.hpp \
    serializer/transaction.hpp \
    serializer/wif.hpp \
    serializer/wrapper.hpp \
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
    bitcoin160.cpp \
    bitcoin256.cpp \
    blke-fetch-transaction.cpp \
    btc-to-satoshi.cpp \
    ec-add.cpp \
    ec-add-secrets.cpp \
    ec-lock.cpp \
    ec-multiply.cpp \
    ec-multiply-secrets.cpp \
    ec-new.cpp \
    ec-to-addr.cpp \
    ec-to-pub.cpp \
    ec-to-wif.cpp \
    ec-unlock.cpp \
    genaddr.cpp \
    genpriv.cpp \
    genpub.cpp \
    hd-new.cpp \
    hd-priv.cpp \
    hd-pub.cpp \
    hd-to-addr.cpp \
    hd-to-ec.cpp \
    hd-to-pub.cpp \
    hd-to-wif.cpp \
    help.cpp \
    initchain.cpp \
    mnemonic-decode.cpp \
    mnemonic-encode.cpp \
    mpk.cpp \
    newseed.cpp \
    qrcode.cpp \
    ripemd160.cpp \
    satoshi-to-btc.cpp \
    script-decode.cpp \
    script-encode.cpp \
    script-to-addr.cpp \
    seed.cpp \
    send-tx-node.cpp \
    send-tx-p2p.cpp \
    sendtx-bci.cpp \
    sha160.cpp \
    sha256.cpp \
    sha512.cpp \
    showblkhead.cpp \
    stealth-addr-encode.cpp \
    stealth-newkey.cpp \
    tx-decode.cpp \
    tx-encode.cpp \
    tx-sign.cpp \
    wallet.cpp \
    wif-to-ec.cpp \
    wif-to-pub.cpp \
    wrap-decode.cpp \
    wrap-encode.cpp

# Generated from XML data source.
if HAVE_OBELISK
    libsx_la_SOURCES += \
        fetch-balance.cpp \
        fetch-confirmations.cpp \
        fetch-header.cpp \
        fetch-height.cpp \
        fetch-history.cpp \
        fetch-public-key.cpp \
        fetch-tx.cpp \
        fetch-tx-index.cpp \
        fetch-utxo.cpp \
        send-tx.cpp \
        watch-tx.cpp \
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
