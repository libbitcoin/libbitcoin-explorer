# ******** GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY ********* #
AUTOMAKE_OPTIONS = subdir-objects

# library
noinst_LTLIBRARIES=libsx.la

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

libsx_la_SOURCES = \
    generated.cpp \
    utility/coin.cpp \
    utility/config.cpp \
    utility/console.cpp \
    utility/curve.cpp \
    utility/dispatch.cpp \
    utility/display.cpp \
    utility/environment.cpp

# Generated from XML data source.
libsx_la_SOURCES += \
    addr.cpp \
    base58-decode.cpp \
    base58-encode.cpp \
    base58check-decode.cpp \
    base58check-encode.cpp \
    bci-fetch-last-height.cpp \
    bci-history.cpp \
    blke-fetch-transaction.cpp \
    brainwallet.cpp \
    btc.cpp \
    decode-addr.cpp \
    ec-add.cpp \
    ec-add-modp.cpp \
    ec-multiply.cpp \
    ec-tweak-add.cpp \
    embed-addr.cpp \
    encode-addr.cpp \
    genaddr.cpp \
    genpriv.cpp \
    genpub.cpp \
    get-pubkey.cpp \
    hd-priv.cpp \
    hd-pub.cpp \
    hd-seed.cpp \
    hd-to-address.cpp \
    hd-to-wif.cpp \
    mktx.cpp \
    mnemonic.cpp \
    mpk.cpp \
    newkey.cpp \
    newseed.cpp \
    pubkey.cpp \
    qrcode.cpp \
    rawscript.cpp \
    ripemd-hash.cpp \
    satoshi.cpp \
    scripthash.cpp \
    secret-to-wif.cpp \
    sendtx-bci.cpp \
    sendtx-node.cpp \
    sendtx-p2p.cpp \
    set-input.cpp \
    sha256.cpp \
    showblkhead.cpp \
    showscript.cpp \
    showtx.cpp \
    sign-input.cpp \
    stealth-addr.cpp \
    stealth-initiate.cpp \
    stealth-newkey.cpp \
    stealth-show-addr.cpp \
    stealth-uncover.cpp \
    stealth-uncover-secret.cpp \
    unwrap.cpp \
    validaddr.cpp \
    validsig.cpp \
    wif-to-secret.cpp \
    wrap.cpp

if HAVE_OBELISK
# Generated from XML data source.
libsx_la_SOURCES += \
    balance.cpp \
    fetch-block-header.cpp \
    fetch-last-height.cpp \
    fetch-stealth.cpp \
    fetch-transaction.cpp \
    fetch-transaction-index.cpp \
    get-utxo.cpp \
    history.cpp \
    monitor.cpp \
    sendtx-obelisk.cpp \
    validtx.cpp \
    wallet.cpp \
    watchtx.cpp \
    obelisk.cpp
    
# There is no independent option for ncurses, currently tied to HAVE_OBELISK.
#sxlib_LDADD += -lncurses ${libobelisk_LIBS}
#sxlib_CPPFLAGS += ${libobelisk_CFLAGS} -DSYSCONFDIR="${sysconfdir}"
endif

if HAVE_OBELISK
# Generated from XML data source.
libsx_la_SOURCES += \
    initchain.cpp
endif

if HAVE_OBELISK

AM_CPPFLAGS += \
    ${libobelisk_CFLAGS} \
    -DSYSCONFDIR=\"${sysconfdir}\"

endif

# console app

bin_PROGRAMS=sx

sx_SOURCES = console/main.cpp

sx_LDADD = \
    -L$(srcdir) -lsx \
    $(libbitcoin_LIBS) \
    $(libwallet_LIBS) \
    -lboost_date_time \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system \
    -lsecp256k1 \
    -lconfig++ \
    -lncurses
#    @LDFLAG_LEVELDB@

if HAVE_OBELISK
sx_LDADD += \
    $(libobelisk_LIBS)
endif
