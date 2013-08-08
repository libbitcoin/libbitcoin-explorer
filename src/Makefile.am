AM_CPPFLAGS = ${libbitcoin_CFLAGS}

corebindir = ${libdir}/sx-core
corebin_PROGRAMS = \
    sx-addr sx-broadcast-tx sx-genpriv sx-genaddr sx-mktx sx-mpk sx-newkey \
    sx-newseed sx-sendtx sx-showtx sx-sign-input sx-mnemonic sx-pubkey \
    sx-rawscript sx-scripthash sx-showscript sx-set-input sx-decode-addr \
    sx-genpub
corebin_SCRIPTS = sx-qrcode sx-watchtx sx-btc sx-satoshi

bin_SCRIPTS = sx
CLEANFILES = $(bin_SCRIPTS)
EXTRADIST = sx.py

do_subst = sed -e "s,[@]corebindir[@],$(corebindir),g"

sx: sx.py Makefile
	$(do_subst) < $(srcdir)/sx.py > sx
	chmod +x sx

if HAVE_OBELISK
corebin_PROGRAMS += \
    sx-history sx-balance sx-fetch-block-header sx-fetch-transaction

AM_CPPFLAGS += -DSYSCONFDIR=\"${sysconfdir}\"
endif

sx_decode_addr_SOURCES = decode-addr.cpp
sx_decode_addr_LDADD = ${libbitcoin_LIBS}

sx_showscript_SOURCES = showscript.cpp
sx_showscript_LDADD = ${libbitcoin_LIBS}

sx_scripthash_SOURCES = scripthash.cpp
sx_scripthash_LDADD = ${libbitcoin_LIBS}

sx_rawscript_SOURCES = rawscript.cpp
sx_rawscript_LDADD = ${libbitcoin_LIBS}

sx_pubkey_SOURCES = pubkey.cpp
sx_pubkey_LDADD = ${libbitcoin_LIBS}

sx_genpub_SOURCES = genpub.cpp
sx_genpub_LDADD = ${libbitcoin_LIBS}

sx_addr_SOURCES = addr.cpp
sx_addr_LDADD = ${libbitcoin_LIBS}

sx_broadcast_tx_SOURCES = broadcast-tx.cpp
sx_broadcast_tx_LDADD = ${libbitcoin_LIBS}

sx_genpriv_SOURCES = genpriv.cpp
sx_genpriv_LDADD = ${libbitcoin_LIBS}

sx_genaddr_SOURCES = genaddr.cpp
sx_genaddr_LDADD = ${libbitcoin_LIBS}

sx_mktx_SOURCES = mktx.cpp
sx_mktx_LDADD = ${libbitcoin_LIBS}

sx_mpk_SOURCES = mpk.cpp
sx_mpk_LDADD = ${libbitcoin_LIBS}

sx_newkey_SOURCES = newkey.cpp
sx_newkey_LDADD = ${libbitcoin_LIBS}

sx_newseed_SOURCES = newseed.cpp
sx_newseed_LDADD = ${libbitcoin_LIBS}

sx_sendtx_SOURCES = sendtx.cpp
sx_sendtx_LDADD = ${libbitcoin_LIBS}

sx_showtx_SOURCES = showtx.cpp
sx_showtx_LDADD = ${libbitcoin_LIBS}

sx_set_input_SOURCES = set-input.cpp
sx_set_input_LDADD = ${libbitcoin_LIBS}

sx_sign_input_SOURCES = sign-input.cpp
sx_sign_input_LDADD = ${libbitcoin_LIBS}

sx_mnemonic_SOURCES = mnemonic.cpp
sx_mnemonic_LDADD = ${libbitcoin_LIBS}

sx_history_SOURCES = history.cpp config.cpp
sx_history_LDADD = ${libbitcoin_LIBS} ${libobelisk_LIBS}

sx_balance_SOURCES = balance.cpp config.cpp
sx_balance_LDADD = ${libbitcoin_LIBS} ${libobelisk_LIBS}

sx_fetch_transaction_SOURCES = fetch-transaction.cpp config.cpp
sx_fetch_transaction_LDADD = ${libbitcoin_LIBS} ${libobelisk_LIBS} 

sx_fetch_block_header_SOURCES = fetch-block-header.cpp config.cpp
sx_fetch_block_header_LDADD = ${libbitcoin_LIBS} ${libobelisk_LIBS} 

