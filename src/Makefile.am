AM_CPPFLAGS = ${libbitcoin_CFLAGS}

bin_PROGRAMS = sx-addr sx-broadcast-tx sx-genpriv sx-genpub sx-mktx sx-mpk sx-newkey sx-newseed sx-sendtx sx-showtx sx-sign-input sx-mnemonic

if HAVE_OBELISK
bin_PROGRAMS += sx-history sx-balance

AM_CPPFLAGS += -DSYSCONFDIR=\"${sysconfdir}\"
endif

bin_SCRIPTS = sx-genqr sx-watchtx

sx_addr_SOURCES = addr.cpp
sx_addr_LDADD = ${libbitcoin_LIBS}

sx_broadcast_tx_SOURCES = broadcast-tx.cpp
sx_broadcast_tx_LDADD = ${libbitcoin_LIBS}

sx_genpriv_SOURCES = genpriv.cpp
sx_genpriv_LDADD = ${libbitcoin_LIBS}

sx_genpub_SOURCES = genpub.cpp
sx_genpub_LDADD = ${libbitcoin_LIBS}

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

sx_sign_input_SOURCES = sign-input.cpp
sx_sign_input_LDADD = ${libbitcoin_LIBS}

sx_mnemonic_SOURCES = mnemonic.cpp
sx_mnemonic_LDADD = ${libbitcoin_LIBS}

sx_history_SOURCES = history.cpp config.cpp
sx_history_LDADD = ${libbitcoin_LIBS} ${libobelisk_LIBS}

sx_balance_SOURCES = balance.cpp config.cpp
sx_balance_LDADD = ${libbitcoin_LIBS} ${libobelisk_LIBS}

