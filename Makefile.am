###############################################################################
#  Copyright (c) 2014-2015 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# Automake settings.
#==============================================================================
# Look for macros in the m4 subdirectory.
#------------------------------------------------------------------------------
ACLOCAL_AMFLAGS = -I m4


# Distribute, make and install products.
#==============================================================================
# files => ${pkgconfigdir}
#------------------------------------------------------------------------------
pkgconfig_DATA = \
    libbitcoin-explorer.pc

# files => ${docdir}
#------------------------------------------------------------------------------
doc_DATA = \
    AUTHORS \
    COPYING \
    ChangeLog \
    INSTALL \
    NEWS \
    README

# src/libbitcoin-explorer.la => ${libdir}
#------------------------------------------------------------------------------
lib_LTLIBRARIES = src/libbitcoin-explorer.la
src_libbitcoin_explorer_la_CPPFLAGS = -I${srcdir}/include -DSYSCONFDIR=\"${sysconfdir}\" ${bitcoin_client_CPPFLAGS}
src_libbitcoin_explorer_la_LIBADD = ${bitcoin_client_LIBS} ${dl_LIBS}
src_libbitcoin_explorer_la_SOURCES = \
    src/async_client.cpp \
    src/callback_state.cpp \
    src/dispatch.cpp \
    src/display.cpp \
    src/generated.cpp \
    src/obelisk_client.cpp \
    src/prop_tree.cpp \
    src/utility.cpp \
    src/commands/address-decode.cpp \
    src/commands/address-embed.cpp \
    src/commands/address-encode.cpp \
    src/commands/address-validate.cpp \
    src/commands/base16-decode.cpp \
    src/commands/base16-encode.cpp \
    src/commands/base58-decode.cpp \
    src/commands/base58-encode.cpp \
    src/commands/base58check-decode.cpp \
    src/commands/base58check-encode.cpp \
    src/commands/base64-decode.cpp \
    src/commands/base64-encode.cpp \
    src/commands/bci-fetch-last-height.cpp \
    src/commands/bci-history.cpp \
    src/commands/bitcoin160.cpp \
    src/commands/bitcoin256.cpp \
    src/commands/blke-fetch-transaction.cpp \
    src/commands/btc-to-satoshi.cpp \
    src/commands/cert-new.cpp \
    src/commands/cert-public.cpp \
    src/commands/ec-add-secrets.cpp \
    src/commands/ec-add.cpp \
    src/commands/ec-lock.cpp \
    src/commands/ec-multiply-secrets.cpp \
    src/commands/ec-multiply.cpp \
    src/commands/ec-new.cpp \
    src/commands/ec-to-address.cpp \
    src/commands/ec-to-public.cpp \
    src/commands/ec-to-wif.cpp \
    src/commands/ec-unlock.cpp \
    src/commands/fetch-balance.cpp \
    src/commands/fetch-header.cpp \
    src/commands/fetch-height.cpp \
    src/commands/fetch-history.cpp \
    src/commands/fetch-public-key.cpp \
    src/commands/fetch-stealth.cpp \
    src/commands/fetch-tx-index.cpp \
    src/commands/fetch-tx.cpp \
    src/commands/fetch-utxo.cpp \
    src/commands/genaddr.cpp \
    src/commands/genpriv.cpp \
    src/commands/genpub.cpp \
    src/commands/hd-new.cpp \
    src/commands/hd-private.cpp \
    src/commands/hd-public.cpp \
    src/commands/hd-to-address.cpp \
    src/commands/hd-to-ec.cpp \
    src/commands/hd-to-public.cpp \
    src/commands/hd-to-wif.cpp \
    src/commands/help.cpp \
    src/commands/initchain.cpp \
    src/commands/input-set.cpp \
    src/commands/input-sign.cpp \
    src/commands/input-validate.cpp \
    src/commands/message-sign.cpp \
    src/commands/message-validate.cpp \
    src/commands/mnemonic-decode.cpp \
    src/commands/mnemonic-encode.cpp \
    src/commands/mnemonic-new.cpp \
    src/commands/mnemonic-to-seed.cpp \
    src/commands/mpk.cpp \
    src/commands/newseed.cpp \
    src/commands/qrcode.cpp \
    src/commands/ripemd160.cpp \
    src/commands/satoshi-to-btc.cpp \
    src/commands/script-decode.cpp \
    src/commands/script-encode.cpp \
    src/commands/script-to-address.cpp \
    src/commands/seed.cpp \
    src/commands/send-tx-node.cpp \
    src/commands/send-tx-p2p.cpp \
    src/commands/send-tx.cpp \
    src/commands/sendtx-bci.cpp \
    src/commands/settings.cpp \
    src/commands/sha160.cpp \
    src/commands/sha256.cpp \
    src/commands/sha512.cpp \
    src/commands/showblkhead.cpp \
    src/commands/stealth-decode.cpp \
    src/commands/stealth-encode.cpp \
    src/commands/stealth-initiate.cpp \
    src/commands/stealth-newkey.cpp \
    src/commands/stealth-public.cpp \
    src/commands/stealth-secret.cpp \
    src/commands/stealth-shared.cpp \
    src/commands/tx-decode.cpp \
    src/commands/tx-encode.cpp \
    src/commands/tx-sign.cpp \
    src/commands/uri-decode.cpp \
    src/commands/uri-encode.cpp \
    src/commands/validate-tx.cpp \
    src/commands/wallet.cpp \
    src/commands/watch-address.cpp \
    src/commands/watch-tx.cpp \
    src/commands/wif-to-ec.cpp \
    src/commands/wif-to-public.cpp \
    src/commands/wrap-decode.cpp \
    src/commands/wrap-encode.cpp \
    src/primitives/address.cpp \
    src/primitives/base16.cpp \
    src/primitives/base2.cpp \
    src/primitives/base58.cpp \
    src/primitives/base64.cpp \
    src/primitives/base85.cpp \
    src/primitives/btc.cpp \
    src/primitives/btc160.cpp \
    src/primitives/btc256.cpp \
    src/primitives/byte.cpp \
    src/primitives/cert_key.cpp \
    src/primitives/ec_private.cpp \
    src/primitives/ec_public.cpp \
    src/primitives/encoding.cpp \
    src/primitives/endorsement.cpp \
    src/primitives/hashtype.cpp \
    src/primitives/hd_key.cpp \
    src/primitives/hd_priv.cpp \
    src/primitives/hd_pub.cpp \
    src/primitives/header.cpp \
    src/primitives/input.cpp \
    src/primitives/language.cpp \
    src/primitives/output.cpp \
    src/primitives/point.cpp \
    src/primitives/raw.cpp \
    src/primitives/script.cpp \
    src/primitives/signature.cpp \
    src/primitives/stealth.cpp \
    src/primitives/transaction.cpp \
    src/primitives/uri.cpp \
    src/primitives/wif.cpp \
    src/primitives/wrapper.cpp

# console/bx => ${bindir}
#------------------------------------------------------------------------------
if WITH_CONSOLE

bin_PROGRAMS = console/bx
console_bx_CPPFLAGS = -I${srcdir}/include -DSYSCONFDIR=\"${sysconfdir}\" ${bitcoin_client_CPPFLAGS}
console_bx_LDADD = src/libbitcoin-explorer.la ${bitcoin_client_LIBS} ${dl_LIBS}
console_bx_SOURCES = \
    console/main.cpp

endif WITH_CONSOLE

# local: test/libbitcoin_explorer_test
#------------------------------------------------------------------------------
if WITH_TESTS

TESTS = libbitcoin_explorer_test_runner.sh

check_PROGRAMS = test/libbitcoin_explorer_test
test_libbitcoin_explorer_test_CPPFLAGS = -I${srcdir}/include -DSYSCONFDIR=\"${sysconfdir}\" ${bitcoin_client_CPPFLAGS}
test_libbitcoin_explorer_test_LDADD = src/libbitcoin-explorer.la ${boost_unit_test_framework_LIBS} ${bitcoin_client_LIBS} ${dl_LIBS}
test_libbitcoin_explorer_test_SOURCES = \
    test/generated__broadcast.cpp \
    test/generated__find.cpp \
    test/generated__formerly.cpp \
    test/generated__symbol.cpp \
    test/main.cpp \
    test/commands/address-decode.cpp \
    test/commands/address-embed.cpp \
    test/commands/address-encode.cpp \
    test/commands/address-validate.cpp \
    test/commands/base16-decode.cpp \
    test/commands/base16-encode.cpp \
    test/commands/base58-decode.cpp \
    test/commands/base58-encode.cpp \
    test/commands/base58check-decode.cpp \
    test/commands/base58check-encode.cpp \
    test/commands/base64-decode.cpp \
    test/commands/base64-encode.cpp \
    test/commands/bci-fetch-last-height.cpp \
    test/commands/bci-history.cpp \
    test/commands/bitcoin160.cpp \
    test/commands/bitcoin256.cpp \
    test/commands/blke-fetch-transaction.cpp \
    test/commands/btc-to-satoshi.cpp \
    test/commands/cert-new.cpp \
    test/commands/cert-public.cpp \
    test/commands/command.hpp \
    test/commands/ec-add-secrets.cpp \
    test/commands/ec-add.cpp \
    test/commands/ec-lock.cpp \
    test/commands/ec-multiply-secrets.cpp \
    test/commands/ec-multiply.cpp \
    test/commands/ec-new.cpp \
    test/commands/ec-to-address.cpp \
    test/commands/ec-to-public.cpp \
    test/commands/ec-to-wif.cpp \
    test/commands/ec-unlock.cpp \
    test/commands/fetch-balance.cpp \
    test/commands/fetch-header.cpp \
    test/commands/fetch-height.cpp \
    test/commands/fetch-history.cpp \
    test/commands/fetch-public-key.cpp \
    test/commands/fetch-stealth.cpp \
    test/commands/fetch-tx-index.cpp \
    test/commands/fetch-tx.cpp \
    test/commands/fetch-utxo.cpp \
    test/commands/genaddr.cpp \
    test/commands/genpriv.cpp \
    test/commands/genpub.cpp \
    test/commands/hd-new.cpp \
    test/commands/hd-private.cpp \
    test/commands/hd-public.cpp \
    test/commands/hd-to-address.cpp \
    test/commands/hd-to-ec.cpp \
    test/commands/hd-to-public.cpp \
    test/commands/hd-to-wif.cpp \
    test/commands/help.cpp \
    test/commands/initchain.cpp \
    test/commands/input-set.cpp \
    test/commands/input-sign.cpp \
    test/commands/input-validate.cpp \
    test/commands/message-sign.cpp \
    test/commands/message-validate.cpp \
    test/commands/mnemonic-decode.cpp \
    test/commands/mnemonic-encode.cpp \
    test/commands/mnemonic-new.cpp \
    test/commands/mnemonic-to-seed.cpp \
    test/commands/mpk.cpp \
    test/commands/newseed.cpp \
    test/commands/qrcode.cpp \
    test/commands/ripemd160.cpp \
    test/commands/satoshi-to-btc.cpp \
    test/commands/script-decode.cpp \
    test/commands/script-encode.cpp \
    test/commands/script-to-address.cpp \
    test/commands/seed.cpp \
    test/commands/send-tx-node.cpp \
    test/commands/send-tx-p2p.cpp \
    test/commands/send-tx.cpp \
    test/commands/sendtx-bci.cpp \
    test/commands/settings.cpp \
    test/commands/sha160.cpp \
    test/commands/sha256.cpp \
    test/commands/sha512.cpp \
    test/commands/showblkhead.cpp \
    test/commands/stealth-decode.cpp \
    test/commands/stealth-encode.cpp \
    test/commands/stealth-initiate.cpp \
    test/commands/stealth-newkey.cpp \
    test/commands/stealth-public.cpp \
    test/commands/stealth-secret.cpp \
    test/commands/stealth-shared.cpp \
    test/commands/tx-decode.cpp \
    test/commands/tx-encode.cpp \
    test/commands/tx-sign.cpp \
    test/commands/uri-decode.cpp \
    test/commands/uri-encode.cpp \
    test/commands/validate-tx.cpp \
    test/commands/wallet.cpp \
    test/commands/watch-address.cpp \
    test/commands/watch-tx.cpp \
    test/commands/wif-to-ec.cpp \
    test/commands/wif-to-public.cpp \
    test/commands/wrap-decode.cpp \
    test/commands/wrap-encode.cpp \
    test/primitives/address.cpp \
    test/primitives/base58.cpp

endif WITH_TESTS

# files => ${includedir}/bitcoin
#------------------------------------------------------------------------------
include_bitcoindir = ${includedir}/bitcoin
include_bitcoin_HEADERS = \
    include/bitcoin/explorer.hpp

include_bitcoin_explorerdir = ${includedir}/bitcoin/explorer
include_bitcoin_explorer_HEADERS = \
    include/bitcoin/explorer/async_client.hpp \
    include/bitcoin/explorer/callback_state.hpp \
    include/bitcoin/explorer/command.hpp \
    include/bitcoin/explorer/define.hpp \
    include/bitcoin/explorer/dispatch.hpp \
    include/bitcoin/explorer/display.hpp \
    include/bitcoin/explorer/generated.hpp \
    include/bitcoin/explorer/obelisk_client.hpp \
    include/bitcoin/explorer/prop_tree.hpp \
    include/bitcoin/explorer/utility.hpp \
    include/bitcoin/explorer/version.hpp

include_bitcoin_explorer_commandsdir = ${includedir}/bitcoin/explorer/commands
include_bitcoin_explorer_commands_HEADERS = \
    include/bitcoin/explorer/commands/address-decode.hpp \
    include/bitcoin/explorer/commands/address-embed.hpp \
    include/bitcoin/explorer/commands/address-encode.hpp \
    include/bitcoin/explorer/commands/address-validate.hpp \
    include/bitcoin/explorer/commands/base16-decode.hpp \
    include/bitcoin/explorer/commands/base16-encode.hpp \
    include/bitcoin/explorer/commands/base58-decode.hpp \
    include/bitcoin/explorer/commands/base58-encode.hpp \
    include/bitcoin/explorer/commands/base58check-decode.hpp \
    include/bitcoin/explorer/commands/base58check-encode.hpp \
    include/bitcoin/explorer/commands/base64-decode.hpp \
    include/bitcoin/explorer/commands/base64-encode.hpp \
    include/bitcoin/explorer/commands/bci-fetch-last-height.hpp \
    include/bitcoin/explorer/commands/bci-history.hpp \
    include/bitcoin/explorer/commands/bitcoin160.hpp \
    include/bitcoin/explorer/commands/bitcoin256.hpp \
    include/bitcoin/explorer/commands/blke-fetch-transaction.hpp \
    include/bitcoin/explorer/commands/btc-to-satoshi.hpp \
    include/bitcoin/explorer/commands/cert-new.hpp \
    include/bitcoin/explorer/commands/cert-public.hpp \
    include/bitcoin/explorer/commands/ec-add-secrets.hpp \
    include/bitcoin/explorer/commands/ec-add.hpp \
    include/bitcoin/explorer/commands/ec-lock.hpp \
    include/bitcoin/explorer/commands/ec-multiply-secrets.hpp \
    include/bitcoin/explorer/commands/ec-multiply.hpp \
    include/bitcoin/explorer/commands/ec-new.hpp \
    include/bitcoin/explorer/commands/ec-to-address.hpp \
    include/bitcoin/explorer/commands/ec-to-public.hpp \
    include/bitcoin/explorer/commands/ec-to-wif.hpp \
    include/bitcoin/explorer/commands/ec-unlock.hpp \
    include/bitcoin/explorer/commands/fetch-balance.hpp \
    include/bitcoin/explorer/commands/fetch-header.hpp \
    include/bitcoin/explorer/commands/fetch-height.hpp \
    include/bitcoin/explorer/commands/fetch-history.hpp \
    include/bitcoin/explorer/commands/fetch-public-key.hpp \
    include/bitcoin/explorer/commands/fetch-stealth.hpp \
    include/bitcoin/explorer/commands/fetch-tx-index.hpp \
    include/bitcoin/explorer/commands/fetch-tx.hpp \
    include/bitcoin/explorer/commands/fetch-utxo.hpp \
    include/bitcoin/explorer/commands/genaddr.hpp \
    include/bitcoin/explorer/commands/genpriv.hpp \
    include/bitcoin/explorer/commands/genpub.hpp \
    include/bitcoin/explorer/commands/hd-new.hpp \
    include/bitcoin/explorer/commands/hd-private.hpp \
    include/bitcoin/explorer/commands/hd-public.hpp \
    include/bitcoin/explorer/commands/hd-to-address.hpp \
    include/bitcoin/explorer/commands/hd-to-ec.hpp \
    include/bitcoin/explorer/commands/hd-to-public.hpp \
    include/bitcoin/explorer/commands/hd-to-wif.hpp \
    include/bitcoin/explorer/commands/help.hpp \
    include/bitcoin/explorer/commands/initchain.hpp \
    include/bitcoin/explorer/commands/input-set.hpp \
    include/bitcoin/explorer/commands/input-sign.hpp \
    include/bitcoin/explorer/commands/input-validate.hpp \
    include/bitcoin/explorer/commands/message-sign.hpp \
    include/bitcoin/explorer/commands/message-validate.hpp \
    include/bitcoin/explorer/commands/mnemonic-decode.hpp \
    include/bitcoin/explorer/commands/mnemonic-encode.hpp \
    include/bitcoin/explorer/commands/mnemonic-new.hpp \
    include/bitcoin/explorer/commands/mnemonic-to-seed.hpp \
    include/bitcoin/explorer/commands/mpk.hpp \
    include/bitcoin/explorer/commands/newseed.hpp \
    include/bitcoin/explorer/commands/qrcode.hpp \
    include/bitcoin/explorer/commands/ripemd160.hpp \
    include/bitcoin/explorer/commands/satoshi-to-btc.hpp \
    include/bitcoin/explorer/commands/script-decode.hpp \
    include/bitcoin/explorer/commands/script-encode.hpp \
    include/bitcoin/explorer/commands/script-to-address.hpp \
    include/bitcoin/explorer/commands/seed.hpp \
    include/bitcoin/explorer/commands/send-tx-node.hpp \
    include/bitcoin/explorer/commands/send-tx-p2p.hpp \
    include/bitcoin/explorer/commands/send-tx.hpp \
    include/bitcoin/explorer/commands/sendtx-bci.hpp \
    include/bitcoin/explorer/commands/settings.hpp \
    include/bitcoin/explorer/commands/sha160.hpp \
    include/bitcoin/explorer/commands/sha256.hpp \
    include/bitcoin/explorer/commands/sha512.hpp \
    include/bitcoin/explorer/commands/showblkhead.hpp \
    include/bitcoin/explorer/commands/stealth-decode.hpp \
    include/bitcoin/explorer/commands/stealth-encode.hpp \
    include/bitcoin/explorer/commands/stealth-initiate.hpp \
    include/bitcoin/explorer/commands/stealth-newkey.hpp \
    include/bitcoin/explorer/commands/stealth-public.hpp \
    include/bitcoin/explorer/commands/stealth-secret.hpp \
    include/bitcoin/explorer/commands/stealth-shared.hpp \
    include/bitcoin/explorer/commands/tx-decode.hpp \
    include/bitcoin/explorer/commands/tx-encode.hpp \
    include/bitcoin/explorer/commands/tx-sign.hpp \
    include/bitcoin/explorer/commands/uri-decode.hpp \
    include/bitcoin/explorer/commands/uri-encode.hpp \
    include/bitcoin/explorer/commands/validate-tx.hpp \
    include/bitcoin/explorer/commands/wallet.hpp \
    include/bitcoin/explorer/commands/watch-address.hpp \
    include/bitcoin/explorer/commands/watch-tx.hpp \
    include/bitcoin/explorer/commands/wif-to-ec.hpp \
    include/bitcoin/explorer/commands/wif-to-public.hpp \
    include/bitcoin/explorer/commands/wrap-decode.hpp \
    include/bitcoin/explorer/commands/wrap-encode.hpp

include_bitcoin_explorer_impldir = ${includedir}/bitcoin/explorer/impl
include_bitcoin_explorer_impl_HEADERS = \
    include/bitcoin/explorer/impl/prop_tree.ipp \
    include/bitcoin/explorer/impl/utility.ipp

include_bitcoin_explorer_primitivesdir = ${includedir}/bitcoin/explorer/primitives
include_bitcoin_explorer_primitives_HEADERS = \
    include/bitcoin/explorer/primitives/address.hpp \
    include/bitcoin/explorer/primitives/base16.hpp \
    include/bitcoin/explorer/primitives/base2.hpp \
    include/bitcoin/explorer/primitives/base58.hpp \
    include/bitcoin/explorer/primitives/base64.hpp \
    include/bitcoin/explorer/primitives/base85.hpp \
    include/bitcoin/explorer/primitives/btc.hpp \
    include/bitcoin/explorer/primitives/btc160.hpp \
    include/bitcoin/explorer/primitives/btc256.hpp \
    include/bitcoin/explorer/primitives/byte.hpp \
    include/bitcoin/explorer/primitives/cert_key.hpp \
    include/bitcoin/explorer/primitives/ec_private.hpp \
    include/bitcoin/explorer/primitives/ec_public.hpp \
    include/bitcoin/explorer/primitives/encoding.hpp \
    include/bitcoin/explorer/primitives/endorsement.hpp \
    include/bitcoin/explorer/primitives/hashtype.hpp \
    include/bitcoin/explorer/primitives/hd_key.hpp \
    include/bitcoin/explorer/primitives/hd_priv.hpp \
    include/bitcoin/explorer/primitives/hd_pub.hpp \
    include/bitcoin/explorer/primitives/header.hpp \
    include/bitcoin/explorer/primitives/input.hpp \
    include/bitcoin/explorer/primitives/language.hpp \
    include/bitcoin/explorer/primitives/output.hpp \
    include/bitcoin/explorer/primitives/point.hpp \
    include/bitcoin/explorer/primitives/raw.hpp \
    include/bitcoin/explorer/primitives/script.hpp \
    include/bitcoin/explorer/primitives/signature.hpp \
    include/bitcoin/explorer/primitives/stealth.hpp \
    include/bitcoin/explorer/primitives/transaction.hpp \
    include/bitcoin/explorer/primitives/uri.hpp \
    include/bitcoin/explorer/primitives/wif.hpp \
    include/bitcoin/explorer/primitives/wrapper.hpp

# files => ${bash_completiondir}
#------------------------------------------------------------------------------
if BASH_COMPLETIONDIR

dist_bash_completion_DATA = \
    data/bx

endif BASH_COMPLETIONDIR

# files => ${sysconfdir}/libbitcoin
#------------------------------------------------------------------------------
sysconf_libbitcoindir = ${sysconfdir}/libbitcoin
sysconf_libbitcoin_DATA = \
    data/bx.cfg


# Custom make targets.
#==============================================================================
# make target: console
#------------------------------------------------------------------------------
target_console = \
    console/bx

console: ${target_console}

