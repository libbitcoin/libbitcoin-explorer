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
    serializer/address.cpp \
    serializer/base16.cpp \
    serializer/base58.cpp \
    serializer/btc.cpp \
    serializer/btc160.cpp \
    serializer/btc256.cpp \
    serializer/ec_private.cpp \
    serializer/ec_public.cpp \
    serializer/encoding.cpp \
    serializer/hashtype.cpp \
    serializer/hd_key.cpp \
    serializer/hd_priv.cpp \
    serializer/hd_pub.cpp \
    serializer/header.cpp \
    serializer/input.cpp \
    serializer/output.cpp \
    serializer/point.cpp \
    serializer/prefix.cpp \
    serializer/raw.cpp \
    serializer/script.cpp \
    serializer/stealth.cpp \
    serializer/transaction.cpp \
    serializer/wif.cpp \
    serializer/wrapper.cpp \
    utility/config.cpp \
    utility/environment.cpp \
    utility/parameter.cpp \
    utility/printer.cpp \
    utility/utility.cpp

# Generated from XML data source.
libsx_la_SOURCES += \
    address-decode.cpp \
    address-embed.cpp \
    address-encode.cpp \
    address-validate.cpp \
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
    ec-to-address.cpp \
    ec-to-public.cpp \
    ec-to-wif.cpp \
    ec-unlock.cpp \
    genaddr.cpp \
    genpriv.cpp \
    genpub.cpp \
    hd-new.cpp \
    hd-private.cpp \
    hd-public.cpp \
    hd-to-address.cpp \
    hd-to-ec.cpp \
    hd-to-public.cpp \
    hd-to-wif.cpp \
    help.cpp \
    initchain.cpp \
    input-set.cpp \
    input-sign.cpp \
    input-validate.cpp \
    mnemonic-decode.cpp \
    mnemonic-encode.cpp \
    mpk.cpp \
    newseed.cpp \
    qrcode.cpp \
    ripemd160.cpp \
    satoshi-to-btc.cpp \
    script-decode.cpp \
    script-encode.cpp \
    script-to-address.cpp \
    seed.cpp \
    send-tx-node.cpp \
    send-tx-p2p.cpp \
    sendtx-bci.cpp \
    sha160.cpp \
    sha256.cpp \
    sha512.cpp \
    showblkhead.cpp \
    stealth-address-decode.cpp \
    stealth-address-encode.cpp \
    stealth-new.cpp \
    stealth-newkey.cpp \
    stealth-shared-secret.cpp \
    stealth-uncover-public.cpp \
    stealth-uncover-secret.cpp \
    tx-decode.cpp \
    tx-encode.cpp \
    tx-sign.cpp \
    wallet.cpp \
    wif-to-ec.cpp \
    wif-to-public.cpp \
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
        fetch-stealth.cpp \
        fetch-tx.cpp \
        fetch-tx-index.cpp \
        fetch-utxo.cpp \
        send-tx.cpp \
        watch-stealth.cpp \
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
