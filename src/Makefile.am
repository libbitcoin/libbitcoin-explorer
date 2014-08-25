# ******** GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY ********* #

AUTOMAKE_OPTIONS = subdir-objects

# Library
noinst_LTLIBRARIES = libbitcoin_explorer.la

AM_CPPFLAGS = \
    ${libbitcoin_CFLAGS} \
    ${libwallet_CFLAGS} \
    -I$(srcdir)/../include

libbitcoin_explorer_la_SOURCES = \
    async_client.cpp \
    callback_state.cpp \
    dispatch.cpp \
    display.cpp \
    generated.cpp \
    obelisk_client.cpp \
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
libbitcoin_explorer_la_SOURCES += \
    command/address-decode.cpp \
    command/address-embed.cpp \
    command/address-encode.cpp \
    command/address-validate.cpp \
    command/base58-decode.cpp \
    command/base58-encode.cpp \
    command/base58check-decode.cpp \
    command/base58check-encode.cpp \
    command/bci-fetch-last-height.cpp \
    command/bci-history.cpp \
    command/bitcoin160.cpp \
    command/bitcoin256.cpp \
    command/blke-fetch-transaction.cpp \
    command/btc-to-satoshi.cpp \
    command/ec-add.cpp \
    command/ec-add-secrets.cpp \
    command/ec-lock.cpp \
    command/ec-multiply.cpp \
    command/ec-multiply-secrets.cpp \
    command/ec-new.cpp \
    command/ec-to-address.cpp \
    command/ec-to-public.cpp \
    command/ec-to-wif.cpp \
    command/ec-unlock.cpp \
    command/fetch-balance.cpp \
    command/fetch-confirmations.cpp \
    command/fetch-header.cpp \
    command/fetch-height.cpp \
    command/fetch-history.cpp \
    command/fetch-public-key.cpp \
    command/fetch-stealth.cpp \
    command/fetch-tx.cpp \
    command/fetch-tx-index.cpp \
    command/fetch-utxo.cpp \
    command/genaddr.cpp \
    command/genpriv.cpp \
    command/genpub.cpp \
    command/hd-new.cpp \
    command/hd-private.cpp \
    command/hd-public.cpp \
    command/hd-to-address.cpp \
    command/hd-to-ec.cpp \
    command/hd-to-public.cpp \
    command/hd-to-wif.cpp \
    command/help.cpp \
    command/initchain.cpp \
    command/input-set.cpp \
    command/input-sign.cpp \
    command/input-validate.cpp \
    command/mnemonic-decode.cpp \
    command/mnemonic-encode.cpp \
    command/mpk.cpp \
    command/newseed.cpp \
    command/qrcode.cpp \
    command/ripemd160.cpp \
    command/satoshi-to-btc.cpp \
    command/script-decode.cpp \
    command/script-encode.cpp \
    command/script-to-address.cpp \
    command/seed.cpp \
    command/send-tx.cpp \
    command/send-tx-node.cpp \
    command/send-tx-p2p.cpp \
    command/sendtx-bci.cpp \
    command/sha160.cpp \
    command/sha256.cpp \
    command/sha512.cpp \
    command/showblkhead.cpp \
    command/stealth-address-decode.cpp \
    command/stealth-address-encode.cpp \
    command/stealth-new.cpp \
    command/stealth-newkey.cpp \
    command/stealth-shared-secret.cpp \
    command/stealth-uncover-public.cpp \
    command/stealth-uncover-secret.cpp \
    command/tx-decode.cpp \
    command/tx-encode.cpp \
    command/tx-sign.cpp \
    command/wallet.cpp \
    command/watch-stealth.cpp \
    command/watch-tx.cpp \
    command/wif-to-ec.cpp \
    command/wif-to-public.cpp \
    command/wrap-decode.cpp \
    command/wrap-encode.cpp

AM_CPPFLAGS += \
    ${libobelisk_CFLAGS} \
    -DSYSCONFDIR="${sysconfdir}"

# Console Application
bin_PROGRAMS = sx

sx_SOURCES = \
    console/main.cpp

sx_LDADD = \
    -L$(srcdir) -llibbitcoin_explorer \
    $(libbitcoin_LIBS) \
    $(libwallet_LIBS) \
    $(libobelisk_LIBS) \
    -lboost_filesystem \
    -lboost_program_options \
    -lboost_regex \
    -lboost_system

