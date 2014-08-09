AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS = sx_test

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

#sx_test_HEADERS = \
     command.hpp

sx_test_SOURCES = \
    addr-decode.cpp \
    addr-embed.cpp \
    addr-encode.cpp \
    addr-validate.cpp \
    address.cpp \
    base58.cpp \
    base58check-decode.cpp \
    base58check-encode.cpp \
    base58-decode.cpp \
    base58-encode.cpp \
    bci-fetch-last-height.cpp \
    bci-history.cpp \
    blke-fetch-transaction.cpp \
    brainwallet.cpp \
    btc-to-satoshi.cpp \
    ec-add.cpp \
    ec-add-secrets.cpp \
    ec-multiply.cpp \
    ec-multiply-secrets.cpp \
    ec-new.cpp \
    ec-to-addr.cpp \
    ec-to-pub.cpp \
    fetch-balance.cpp \
    fetch-confirmations.cpp \
    fetch-header.cpp \
    fetch-height.cpp \
    fetch-history.cpp \
    fetch-public-key.cpp \
    fetch-tx.cpp \
    fetch-tx-index.cpp \
    fetch-utxo.cpp \
    genaddr.cpp \
    generated__broadcast.cpp \
    generated__find.cpp \
    generated__symbol.cpp \
    genpriv.cpp \
    genpub.cpp \
    hd-new.cpp \
    hd-priv.cpp \
    hd-pub.cpp \
    hd-seed.cpp \
    hd-to-addr.cpp \
    hd-to-ec.cpp \
    hd-to-pub.cpp \
    hd-to-wif.cpp \
    help.cpp \
    initchain.cpp \
    main.cpp \
    monitor.cpp \
    mpk.cpp \
    newseed.cpp \
    parameter.cpp \
    printer.cpp \
    qrcode.cpp \
    ripemd160.cpp \
    satoshi-to-btc.cpp \
    sendtx-bci.cpp \
    sha160.cpp \
    sha256.cpp \
    sha512.cpp \
    stealth-addr.cpp \
    unwrap.cpp \
    wallet.cpp \
    watch-tx.cpp \
    wif-to-ec.cpp \
    wif-to-pub.cpp \
    wrap-decode.cpp \
    wrap-encode.cpp

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
        $(libobelisk_LIBS)
endif

