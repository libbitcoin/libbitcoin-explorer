###############################################################################
#  Copyright (c) 2014-2026 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# Automake settings.
#==============================================================================
# Look for macros in the 'm4' subdirectory.
#------------------------------------------------------------------------------
ACLOCAL_AMFLAGS = -I m4

# Distribute data.
#==============================================================================
# files => ${pkgconfigdir}
#------------------------------------------------------------------------------
pkgconfig_DATA = \
    libbitcoin-explorer.pc

# files => ${docdir}
#------------------------------------------------------------------------------
doc_DATA = \
    AUTHORS \
    ../../COPYING \
    ChangeLog \
    INSTALL \
    NEWS \
    README

# Libraries.
#==============================================================================
# Target library 'src/libbitcoin-explorer.la'
#------------------------------------------------------------------------------
lib_LTLIBRARIES = src/libbitcoin-explorer.la

src_libbitcoin_explorer_la_LIBS = src/libbitcoin-explorer.la

src_libbitcoin_explorer_la_CPPFLAGS = \
    -I${srcdir}/../../include \
    ${libbitcoin_system_BUILD_CPPFLAGS}

src_libbitcoin_explorer_la_LDFLAGS = \
    ${libbitcoin_system_LDFLAGS}

src_libbitcoin_explorer_la_LIBADD = \
    ${libbitcoin_system_LIBS}

src_libbitcoin_explorer_la_SOURCES = \
    ${srcdir}/../../src/dispatch.cpp \
    ${srcdir}/../../src/display.cpp \
    ${srcdir}/../../src/generated.cpp \
    ${srcdir}/../../src/json.cpp \
    ${srcdir}/../../src/parser.cpp \
    ${srcdir}/../../src/utility.cpp \
    ${srcdir}/../../src/commands/address-decode.cpp \
    ${srcdir}/../../src/commands/address-embed.cpp \
    ${srcdir}/../../src/commands/address-encode.cpp \
    ${srcdir}/../../src/commands/address-to-key.cpp \
    ${srcdir}/../../src/commands/base16-decode.cpp \
    ${srcdir}/../../src/commands/base16-encode.cpp \
    ${srcdir}/../../src/commands/base32-decode.cpp \
    ${srcdir}/../../src/commands/base32-encode.cpp \
    ${srcdir}/../../src/commands/base58-decode.cpp \
    ${srcdir}/../../src/commands/base58-encode.cpp \
    ${srcdir}/../../src/commands/base58check-decode.cpp \
    ${srcdir}/../../src/commands/base58check-encode.cpp \
    ${srcdir}/../../src/commands/base64-decode.cpp \
    ${srcdir}/../../src/commands/base64-encode.cpp \
    ${srcdir}/../../src/commands/bech32-decode.cpp \
    ${srcdir}/../../src/commands/bech32-encode.cpp \
    ${srcdir}/../../src/commands/bitcoin160.cpp \
    ${srcdir}/../../src/commands/bitcoin256.cpp \
    ${srcdir}/../../src/commands/broadcast-tx.cpp \
    ${srcdir}/../../src/commands/btc-to-satoshi.cpp \
    ${srcdir}/../../src/commands/cert-new.cpp \
    ${srcdir}/../../src/commands/cert-public.cpp \
    ${srcdir}/../../src/commands/checked-decode.cpp \
    ${srcdir}/../../src/commands/checked-encode.cpp \
    ${srcdir}/../../src/commands/ec-add-secrets.cpp \
    ${srcdir}/../../src/commands/ec-add.cpp \
    ${srcdir}/../../src/commands/ec-decompress.cpp \
    ${srcdir}/../../src/commands/ec-multiply-secrets.cpp \
    ${srcdir}/../../src/commands/ec-multiply.cpp \
    ${srcdir}/../../src/commands/ec-new.cpp \
    ${srcdir}/../../src/commands/ec-to-address.cpp \
    ${srcdir}/../../src/commands/ec-to-ek.cpp \
    ${srcdir}/../../src/commands/ec-to-public.cpp \
    ${srcdir}/../../src/commands/ec-to-wif.cpp \
    ${srcdir}/../../src/commands/ec-to-witness.cpp \
    ${srcdir}/../../src/commands/ek-address.cpp \
    ${srcdir}/../../src/commands/ek-new.cpp \
    ${srcdir}/../../src/commands/ek-public-to-address.cpp \
    ${srcdir}/../../src/commands/ek-public-to-ec.cpp \
    ${srcdir}/../../src/commands/ek-public.cpp \
    ${srcdir}/../../src/commands/ek-to-address.cpp \
    ${srcdir}/../../src/commands/ek-to-ec.cpp \
    ${srcdir}/../../src/commands/electrum-decode.cpp \
    ${srcdir}/../../src/commands/electrum-new.cpp \
    ${srcdir}/../../src/commands/electrum-to-seed.cpp \
    ${srcdir}/../../src/commands/fetch-balance.cpp \
    ${srcdir}/../../src/commands/fetch-block-hashes.cpp \
    ${srcdir}/../../src/commands/fetch-block-height.cpp \
    ${srcdir}/../../src/commands/fetch-block.cpp \
    ${srcdir}/../../src/commands/fetch-filter-checkpoint.cpp \
    ${srcdir}/../../src/commands/fetch-filter-headers.cpp \
    ${srcdir}/../../src/commands/fetch-filter.cpp \
    ${srcdir}/../../src/commands/fetch-header.cpp \
    ${srcdir}/../../src/commands/fetch-height.cpp \
    ${srcdir}/../../src/commands/fetch-history.cpp \
    ${srcdir}/../../src/commands/fetch-public-key.cpp \
    ${srcdir}/../../src/commands/fetch-tx-index.cpp \
    ${srcdir}/../../src/commands/fetch-tx.cpp \
    ${srcdir}/../../src/commands/fetch-utxo.cpp \
    ${srcdir}/../../src/commands/get-filter-checkpoint.cpp \
    ${srcdir}/../../src/commands/get-filter-headers.cpp \
    ${srcdir}/../../src/commands/get-filters.cpp \
    ${srcdir}/../../src/commands/hd-new.cpp \
    ${srcdir}/../../src/commands/hd-private.cpp \
    ${srcdir}/../../src/commands/hd-public.cpp \
    ${srcdir}/../../src/commands/hd-to-address.cpp \
    ${srcdir}/../../src/commands/hd-to-ec.cpp \
    ${srcdir}/../../src/commands/hd-to-public.cpp \
    ${srcdir}/../../src/commands/hd-to-wif.cpp \
    ${srcdir}/../../src/commands/help.cpp \
    ${srcdir}/../../src/commands/input-set.cpp \
    ${srcdir}/../../src/commands/input-sign.cpp \
    ${srcdir}/../../src/commands/input-validate.cpp \
    ${srcdir}/../../src/commands/match-neutrino-address.cpp \
    ${srcdir}/../../src/commands/match-neutrino-script.cpp \
    ${srcdir}/../../src/commands/message-sign.cpp \
    ${srcdir}/../../src/commands/message-validate.cpp \
    ${srcdir}/../../src/commands/mnemonic-decode.cpp \
    ${srcdir}/../../src/commands/mnemonic-encode.cpp \
    ${srcdir}/../../src/commands/mnemonic-to-seed.cpp \
    ${srcdir}/../../src/commands/put-tx.cpp \
    ${srcdir}/../../src/commands/qrcode.cpp \
    ${srcdir}/../../src/commands/ripemd160.cpp \
    ${srcdir}/../../src/commands/satoshi-to-btc.cpp \
    ${srcdir}/../../src/commands/script-decode.cpp \
    ${srcdir}/../../src/commands/script-encode.cpp \
    ${srcdir}/../../src/commands/script-to-address.cpp \
    ${srcdir}/../../src/commands/script-to-key.cpp \
    ${srcdir}/../../src/commands/script-to-witness.cpp \
    ${srcdir}/../../src/commands/seed.cpp \
    ${srcdir}/../../src/commands/send-tx.cpp \
    ${srcdir}/../../src/commands/settings.cpp \
    ${srcdir}/../../src/commands/sha160.cpp \
    ${srcdir}/../../src/commands/sha256.cpp \
    ${srcdir}/../../src/commands/sha512.cpp \
    ${srcdir}/../../src/commands/stealth-public.cpp \
    ${srcdir}/../../src/commands/stealth-secret.cpp \
    ${srcdir}/../../src/commands/stealth-shared.cpp \
    ${srcdir}/../../src/commands/subscribe-block.cpp \
    ${srcdir}/../../src/commands/subscribe-tx.cpp \
    ${srcdir}/../../src/commands/token-new.cpp \
    ${srcdir}/../../src/commands/tx-decode.cpp \
    ${srcdir}/../../src/commands/tx-encode.cpp \
    ${srcdir}/../../src/commands/tx-sign.cpp \
    ${srcdir}/../../src/commands/uri-decode.cpp \
    ${srcdir}/../../src/commands/uri-encode.cpp \
    ${srcdir}/../../src/commands/validate-tx.cpp \
    ${srcdir}/../../src/commands/version.cpp \
    ${srcdir}/../../src/commands/watch-key.cpp \
    ${srcdir}/../../src/commands/watch-tx.cpp \
    ${srcdir}/../../src/commands/wif-to-ec.cpp \
    ${srcdir}/../../src/commands/wif-to-public.cpp \
    ${srcdir}/../../src/commands/witness-to-key.cpp \
    ${srcdir}/../../src/commands/wrap-decode.cpp \
    ${srcdir}/../../src/commands/wrap-encode.cpp \
    ${srcdir}/../../src/config/address.cpp \
    ${srcdir}/../../src/config/algorithm.cpp \
    ${srcdir}/../../src/config/btc.cpp \
    ${srcdir}/../../src/config/byte.cpp \
    ${srcdir}/../../src/config/bytes.cpp \
    ${srcdir}/../../src/config/ec_private.cpp \
    ${srcdir}/../../src/config/electrum.cpp \
    ${srcdir}/../../src/config/endorsement.cpp \
    ${srcdir}/../../src/config/hd_key.cpp \
    ${srcdir}/../../src/config/language.cpp \
    ${srcdir}/../../src/config/sighash.cpp \
    ${srcdir}/../../src/config/signature.cpp \
    ${srcdir}/../../src/config/witness.cpp

include_bitcoindir = \
    ${includedir}/bitcoin

include_bitcoin_HEADERS = \
    ${srcdir}/../../include/bitcoin/explorer.hpp

include_bitcoin_explorerdir = \
    ${includedir}/bitcoin/explorer

include_bitcoin_explorer_HEADERS = \
    ${srcdir}/../../include/bitcoin/explorer/command.hpp \
    ${srcdir}/../../include/bitcoin/explorer/define.hpp \
    ${srcdir}/../../include/bitcoin/explorer/dispatch.hpp \
    ${srcdir}/../../include/bitcoin/explorer/display.hpp \
    ${srcdir}/../../include/bitcoin/explorer/generated.hpp \
    ${srcdir}/../../include/bitcoin/explorer/json.hpp \
    ${srcdir}/../../include/bitcoin/explorer/parser.hpp \
    ${srcdir}/../../include/bitcoin/explorer/utility.hpp \
    ${srcdir}/../../include/bitcoin/explorer/version.hpp

include_bitcoin_explorer_commandsdir = \
    ${includedir}/bitcoin/explorer/commands

include_bitcoin_explorer_commands_HEADERS = \
    ${srcdir}/../../include/bitcoin/explorer/commands/address-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/address-embed.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/address-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/address-to-key.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base16-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base16-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base32-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base32-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base58-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base58-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base58check-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base58check-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base64-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/base64-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/bech32-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/bech32-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/bitcoin160.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/bitcoin256.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/broadcast-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/btc-to-satoshi.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/cert-new.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/cert-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/checked-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/checked-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-add-secrets.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-add.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-decompress.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-multiply-secrets.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-multiply.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-new.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-to-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-to-ek.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-to-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-to-wif.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ec-to-witness.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-new.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-public-to-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-public-to-ec.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-to-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ek-to-ec.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/electrum-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/electrum-new.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/electrum-to-seed.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-balance.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-block-hashes.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-block-height.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-block.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-filter-checkpoint.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-filter-headers.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-filter.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-header.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-height.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-history.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-public-key.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-tx-index.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/fetch-utxo.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/get-filter-checkpoint.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/get-filter-headers.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/get-filters.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-new.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-private.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-to-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-to-ec.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-to-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/hd-to-wif.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/help.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/input-set.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/input-sign.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/input-validate.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/match-neutrino-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/match-neutrino-script.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/message-sign.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/message-validate.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/mnemonic-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/mnemonic-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/mnemonic-to-seed.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/put-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/qrcode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/ripemd160.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/satoshi-to-btc.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/script-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/script-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/script-to-address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/script-to-key.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/script-to-witness.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/seed.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/send-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/settings.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/sha160.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/sha256.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/sha512.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/stealth-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/stealth-secret.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/stealth-shared.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/subscribe-block.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/subscribe-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/token-new.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/tx-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/tx-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/tx-sign.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/uri-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/uri-encode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/validate-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/version.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/watch-key.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/watch-tx.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/wif-to-ec.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/wif-to-public.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/witness-to-key.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/wrap-decode.hpp \
    ${srcdir}/../../include/bitcoin/explorer/commands/wrap-encode.hpp

include_bitcoin_explorer_configdir = \
    ${includedir}/bitcoin/explorer/config

include_bitcoin_explorer_config_HEADERS = \
    ${srcdir}/../../include/bitcoin/explorer/config/address.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/algorithm.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/btc.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/byte.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/bytes.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/ec_private.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/electrum.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/endorsement.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/hd_key.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/language.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/sighash.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/signature.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/witness.hpp \
    ${srcdir}/../../include/bitcoin/explorer/config/wrapper.hpp

include_bitcoin_explorer_impldir = \
    ${includedir}/bitcoin/explorer/impl

include_bitcoin_explorer_impl_HEADERS = \
    ${srcdir}/../../include/bitcoin/explorer/impl/utility.ipp

# Tests.
#==============================================================================
# Target test 'test/libbitcoin-explorer-test'
#------------------------------------------------------------------------------
if WITH_TESTS

check_PROGRAMS = test/libbitcoin-explorer-test

test_libbitcoin_explorer_test_CPPFLAGS = \
    -I${srcdir}/../../test \
    ${boost_BUILD_CPPFLAGS} \
    ${boost_unit_test_framework_BUILD_CPPFLAGS} \
    ${src_libbitcoin_explorer_la_CPPFLAGS}

test_libbitcoin_explorer_test_LDFLAGS = \
    ${boost_LDFLAGS} \
    ${boost_unit_test_framework_LDFLAGS} \
    ${src_libbitcoin_explorer_la_LDFLAGS}

test_libbitcoin_explorer_test_LDADD = \
    ${boost_LIBS} \
    ${boost_unit_test_framework_LIBS} \
    ${src_libbitcoin_explorer_la_LIBS} \
    ${src_libbitcoin_explorer_la_LIBADD}

test_libbitcoin_explorer_test_SOURCES = \
    ${srcdir}/../../test/generated__broadcast.cpp \
    ${srcdir}/../../test/generated__find.cpp \
    ${srcdir}/../../test/generated__formerly.cpp \
    ${srcdir}/../../test/generated__symbol.cpp \
    ${srcdir}/../../test/main.cpp \
    ${srcdir}/../../test/commands/address-decode.cpp \
    ${srcdir}/../../test/commands/address-embed.cpp \
    ${srcdir}/../../test/commands/address-encode.cpp \
    ${srcdir}/../../test/commands/address-to-key.cpp \
    ${srcdir}/../../test/commands/base16-decode.cpp \
    ${srcdir}/../../test/commands/base16-encode.cpp \
    ${srcdir}/../../test/commands/base32-decode.cpp \
    ${srcdir}/../../test/commands/base32-encode.cpp \
    ${srcdir}/../../test/commands/base58-decode.cpp \
    ${srcdir}/../../test/commands/base58-encode.cpp \
    ${srcdir}/../../test/commands/base58check-decode.cpp \
    ${srcdir}/../../test/commands/base58check-encode.cpp \
    ${srcdir}/../../test/commands/base64-decode.cpp \
    ${srcdir}/../../test/commands/base64-encode.cpp \
    ${srcdir}/../../test/commands/bech32-decode.cpp \
    ${srcdir}/../../test/commands/bech32-encode.cpp \
    ${srcdir}/../../test/commands/bitcoin160.cpp \
    ${srcdir}/../../test/commands/bitcoin256.cpp \
    ${srcdir}/../../test/commands/broadcast-tx.cpp \
    ${srcdir}/../../test/commands/btc-to-satoshi.cpp \
    ${srcdir}/../../test/commands/cert-new.cpp \
    ${srcdir}/../../test/commands/cert-public.cpp \
    ${srcdir}/../../test/commands/checked-decode.cpp \
    ${srcdir}/../../test/commands/checked-encode.cpp \
    ${srcdir}/../../test/commands/ec-add-secrets.cpp \
    ${srcdir}/../../test/commands/ec-add.cpp \
    ${srcdir}/../../test/commands/ec-decompress.cpp \
    ${srcdir}/../../test/commands/ec-multiply-secrets.cpp \
    ${srcdir}/../../test/commands/ec-multiply.cpp \
    ${srcdir}/../../test/commands/ec-new.cpp \
    ${srcdir}/../../test/commands/ec-to-address.cpp \
    ${srcdir}/../../test/commands/ec-to-ek.cpp \
    ${srcdir}/../../test/commands/ec-to-public.cpp \
    ${srcdir}/../../test/commands/ec-to-wif.cpp \
    ${srcdir}/../../test/commands/ec-to-witness.cpp \
    ${srcdir}/../../test/commands/ek-address.cpp \
    ${srcdir}/../../test/commands/ek-new.cpp \
    ${srcdir}/../../test/commands/ek-public-to-address.cpp \
    ${srcdir}/../../test/commands/ek-public-to-ec.cpp \
    ${srcdir}/../../test/commands/ek-public.cpp \
    ${srcdir}/../../test/commands/ek-to-address.cpp \
    ${srcdir}/../../test/commands/ek-to-ec.cpp \
    ${srcdir}/../../test/commands/electrum-decode.cpp \
    ${srcdir}/../../test/commands/electrum-new.cpp \
    ${srcdir}/../../test/commands/electrum-to-seed.cpp \
    ${srcdir}/../../test/commands/fetch-balance.cpp \
    ${srcdir}/../../test/commands/fetch-block.cpp \
    ${srcdir}/../../test/commands/fetch-header.cpp \
    ${srcdir}/../../test/commands/fetch-height.cpp \
    ${srcdir}/../../test/commands/fetch-history.cpp \
    ${srcdir}/../../test/commands/fetch-public-key.cpp \
    ${srcdir}/../../test/commands/fetch-tx-index.cpp \
    ${srcdir}/../../test/commands/fetch-tx.cpp \
    ${srcdir}/../../test/commands/fetch-utxo.cpp \
    ${srcdir}/../../test/commands/get-filter-checkpoint.cpp \
    ${srcdir}/../../test/commands/get-filter-headers.cpp \
    ${srcdir}/../../test/commands/get-filters.cpp \
    ${srcdir}/../../test/commands/hd-new.cpp \
    ${srcdir}/../../test/commands/hd-private.cpp \
    ${srcdir}/../../test/commands/hd-public.cpp \
    ${srcdir}/../../test/commands/hd-to-address.cpp \
    ${srcdir}/../../test/commands/hd-to-ec.cpp \
    ${srcdir}/../../test/commands/hd-to-public.cpp \
    ${srcdir}/../../test/commands/hd-to-wif.cpp \
    ${srcdir}/../../test/commands/help.cpp \
    ${srcdir}/../../test/commands/input-set.cpp \
    ${srcdir}/../../test/commands/input-sign.cpp \
    ${srcdir}/../../test/commands/input-validate.cpp \
    ${srcdir}/../../test/commands/match-neutrino-address.cpp \
    ${srcdir}/../../test/commands/match-neutrino-script.cpp \
    ${srcdir}/../../test/commands/message-sign.cpp \
    ${srcdir}/../../test/commands/message-validate.cpp \
    ${srcdir}/../../test/commands/mnemonic-decode.cpp \
    ${srcdir}/../../test/commands/mnemonic-encode.cpp \
    ${srcdir}/../../test/commands/mnemonic-to-seed.cpp \
    ${srcdir}/../../test/commands/put-tx.cpp \
    ${srcdir}/../../test/commands/qrcode.cpp \
    ${srcdir}/../../test/commands/ripemd160.cpp \
    ${srcdir}/../../test/commands/satoshi-to-btc.cpp \
    ${srcdir}/../../test/commands/script-decode.cpp \
    ${srcdir}/../../test/commands/script-encode.cpp \
    ${srcdir}/../../test/commands/script-to-address.cpp \
    ${srcdir}/../../test/commands/script-to-key.cpp \
    ${srcdir}/../../test/commands/script-to-witness.cpp \
    ${srcdir}/../../test/commands/seed.cpp \
    ${srcdir}/../../test/commands/send-tx.cpp \
    ${srcdir}/../../test/commands/settings.cpp \
    ${srcdir}/../../test/commands/sha160.cpp \
    ${srcdir}/../../test/commands/sha256.cpp \
    ${srcdir}/../../test/commands/sha512.cpp \
    ${srcdir}/../../test/commands/stealth-public.cpp \
    ${srcdir}/../../test/commands/stealth-secret.cpp \
    ${srcdir}/../../test/commands/stealth-shared.cpp \
    ${srcdir}/../../test/commands/subscribe-block.cpp \
    ${srcdir}/../../test/commands/subscribe-tx.cpp \
    ${srcdir}/../../test/commands/token-new.cpp \
    ${srcdir}/../../test/commands/tx-decode.cpp \
    ${srcdir}/../../test/commands/tx-encode.cpp \
    ${srcdir}/../../test/commands/tx-sign.cpp \
    ${srcdir}/../../test/commands/uri-decode.cpp \
    ${srcdir}/../../test/commands/uri-encode.cpp \
    ${srcdir}/../../test/commands/validate-tx.cpp \
    ${srcdir}/../../test/commands/watch-key.cpp \
    ${srcdir}/../../test/commands/watch-tx.cpp \
    ${srcdir}/../../test/commands/wif-to-ec.cpp \
    ${srcdir}/../../test/commands/wif-to-public.cpp \
    ${srcdir}/../../test/commands/witness-to-key.cpp \
    ${srcdir}/../../test/commands/wrap-decode.cpp \
    ${srcdir}/../../test/commands/wrap-encode.cpp \
    ${srcdir}/../../test/config/address.cpp

TESTS = test_runner.sh

endif WITH_TESTS

# Installed Binaries.
#==============================================================================
# Target binary 'console/bx'
#------------------------------------------------------------------------------
if WITH_CONSOLE

bin_PROGRAMS = console/bx

console_bx_CPPFLAGS = \
    ${src_libbitcoin_explorer_la_CPPFLAGS}

console_bx_LDFLAGS = \
    ${src_libbitcoin_explorer_la_LDFLAGS}

console_bx_LDADD = \
    ${src_libbitcoin_explorer_la_LIBS} \
    ${src_libbitcoin_explorer_la_LIBADD}

console_bx_SOURCES = \
    ${srcdir}/../../console/main.cpp

target_console = console/bx

console: ${target_console}

endif WITH_CONSOLE
