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
    commands/address-decode.cpp \
    commands/address-embed.cpp \
    commands/address-encode.cpp \
    commands/address-validate.cpp \
    commands/base58-decode.cpp \
    commands/base58-encode.cpp \
    commands/base58check-decode.cpp \
    commands/base58check-encode.cpp \
    commands/bci-fetch-last-height.cpp \
    commands/bci-history.cpp \
    commands/bitcoin160.cpp \
    commands/bitcoin256.cpp \
    commands/blke-fetch-transaction.cpp \
    commands/btc-to-satoshi.cpp \
    commands/ec-add.cpp \
    commands/ec-add-secrets.cpp \
    commands/ec-lock.cpp \
    commands/ec-multiply.cpp \
    commands/ec-multiply-secrets.cpp \
    commands/ec-new.cpp \
    commands/ec-to-address.cpp \
    commands/ec-to-public.cpp \
    commands/ec-to-wif.cpp \
    commands/ec-unlock.cpp \
    commands/fetch-balance.cpp \
    commands/fetch-confirmations.cpp \
    commands/fetch-header.cpp \
    commands/fetch-height.cpp \
    commands/fetch-history.cpp \
    commands/fetch-public-key.cpp \
    commands/fetch-stealth.cpp \
    commands/fetch-tx.cpp \
    commands/fetch-tx-index.cpp \
    commands/fetch-utxo.cpp \
    commands/genaddr.cpp \
    commands/genpriv.cpp \
    commands/genpub.cpp \
    commands/hd-new.cpp \
    commands/hd-private.cpp \
    commands/hd-public.cpp \
    commands/hd-to-address.cpp \
    commands/hd-to-ec.cpp \
    commands/hd-to-public.cpp \
    commands/hd-to-wif.cpp \
    commands/help.cpp \
    commands/initchain.cpp \
    commands/input-set.cpp \
    commands/input-sign.cpp \
    commands/input-validate.cpp \
    commands/mnemonic-decode.cpp \
    commands/mnemonic-encode.cpp \
    commands/mpk.cpp \
    commands/newseed.cpp \
    commands/qrcode.cpp \
    commands/ripemd160.cpp \
    commands/satoshi-to-btc.cpp \
    commands/script-decode.cpp \
    commands/script-encode.cpp \
    commands/script-to-address.cpp \
    commands/seed.cpp \
    commands/send-tx.cpp \
    commands/send-tx-node.cpp \
    commands/send-tx-p2p.cpp \
    commands/sendtx-bci.cpp \
    commands/sha160.cpp \
    commands/sha256.cpp \
    commands/sha512.cpp \
    commands/showblkhead.cpp \
    commands/stealth-address-decode.cpp \
    commands/stealth-address-encode.cpp \
    commands/stealth-new.cpp \
    commands/stealth-newkey.cpp \
    commands/stealth-shared-secret.cpp \
    commands/stealth-uncover-public.cpp \
    commands/stealth-uncover-secret.cpp \
    commands/tx-decode.cpp \
    commands/tx-encode.cpp \
    commands/tx-sign.cpp \
    commands/wallet.cpp \
    commands/watch-stealth.cpp \
    commands/watch-tx.cpp \
    commands/wif-to-ec.cpp \
    commands/wif-to-public.cpp \
    commands/wrap-decode.cpp \
    commands/wrap-encode.cpp

libbitcoin_explorer_test_LDADD = \
    -L$(srcdir)/../src/ -lbitcoin_explorer \
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

