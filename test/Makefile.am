# ******** GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY ********* #

AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS = libbitcoin_explorer_test

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

#libbitcoin_explorer_test_HEADERS = \
    command.hpp \
    precompile.hpp

libbitcoin_explorer_test_SOURCES = \
    address.cpp \
    base58.cpp \
    generated__broadcast.cpp \
    generated__find.cpp \
    generated__symbol.cpp \
    main.cpp \
    obelisk_client.cpp \
    parameter.cpp \
    printer.cpp

# Generated from XML data source.
libbitcoin_explorer_test_SOURCES += \
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
    send-tx.cpp \
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
    watch-stealth.cpp \
    watch-tx.cpp \
    wif-to-ec.cpp \
    wif-to-public.cpp \
    wrap-decode.cpp \
    wrap-encode.cpp

libbitcoin_explorer_test_LDADD = \
    -L$(srcdir)/../src/ -llibbitcoin_explorer \
    $(libbitcoin_LIBS) \
    $(libwallet_LIBS) \
    $(libobelisk_LIBS) \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system \
    -lboost_unit_test_framework
      
AM_CPPFLAGS += \
    ${libobelisk_CFLAGS} \
    -DBOOST_TEST_DYN_LINK

