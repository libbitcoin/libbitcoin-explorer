AM_CPPFLAGS = ${libbitcoin_CFLAGS} ${libwallet_CFLAGS}

corebindir = ${libdir}/sx-core
corebin_PROGRAMS = \
    sx-addr sx-sendtx-p2p sx-genpriv sx-genaddr sx-mktx sx-mpk sx-newkey \
    sx-newseed sx-sendtx-node sx-showtx sx-sign-input sx-mnemonic sx-pubkey \
    sx-rawscript sx-scripthash sx-showscript sx-set-input sx-decode-addr \
    sx-encode-addr sx-genpub sx-showblkhead sx-validsig \
    sx-validaddr sx-base58-encode sx-base58-decode sx-wrap sx-unwrap \
    sx-ripemd-hash sx-initchain sx-secret-to-wif sx-wif-to-secret \
    sx-hd-seed sx-hd-priv sx-hd-pub sx-hd-to-address sx-hd-to-wif \
    sx-stealth-addr sx-stealth-show-addr sx-stealth-initiate \
    sx-stealth-uncover sx-stealth-uncover-secret \
    sx-ec-multiply sx-ec-tweak-add
corebin_SCRIPTS = sx-qrcode sx-watchtx sx-btc sx-satoshi sx-bci-history \
	sx-get-utxo sx-bci-fetch-last-height sx-sendtx-bci sx-base58check-encode \
	sx-base58check-decode sx-embed-addr sx-blke-fetch-transaction \
	sx-brainwallet sx-get-pubkey

pyobeliskdir = ${libdir}/sx-core/obelisk
pyobelisk_SCRIPTS = \
    obelisk/bitcoin.py obelisk/client.py obelisk/config.py \
    obelisk/deserialize.py obelisk/error_code.py obelisk/__init__.py \
    obelisk/models.py obelisk/numbertheory.py obelisk/serialize.py \
    obelisk/transaction.py obelisk/util.py obelisk/zmqbase.py \
    obelisk/zmq_fallback.py

bin_SCRIPTS = sx
CLEANFILES = $(bin_SCRIPTS)
EXTRADIST = sx.py

cfgdefault = ${pkgdatadir}/sx.cfg

do_subst_corebindir = sed -e "s,[@]corebindir[@],$(corebindir),g"
do_subst_cfgdefault = sed -e "s,[@]cfgdefault[@],$(cfgdefault),g"

sx: sx.py Makefile
	$(do_subst_corebindir) < $(srcdir)/sx.py > sx_1
	$(do_subst_cfgdefault) < sx_1 > sx
	chmod +x sx
	rm sx_1

if HAVE_OBELISK
corebin_PROGRAMS += \
    sx-history sx-balance sx-fetch-block-header sx-fetch-transaction \
    sx-fetch-last-height sx-validtx sx-sendtx-obelisk sx-wallet \
    sx-fetch-transaction-index sx-fetch-stealth sx-monitor

AM_CPPFLAGS += ${libobelisk_CFLAGS} -DSYSCONFDIR=\"${sysconfdir}\"
endif

sx_ec_tweak_add_SOURCES = ec-tweak-add.cpp
sx_ec_tweak_add_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_ec_multiply_SOURCES = ec-multiply.cpp
sx_ec_multiply_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_stealth_show_addr_SOURCES = stealth-show-addr.cpp
sx_stealth_show_addr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_stealth_initiate_SOURCES = stealth-initiate.cpp
sx_stealth_initiate_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_stealth_uncover_SOURCES = stealth-uncover.cpp
sx_stealth_uncover_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_stealth_uncover_secret_SOURCES = stealth-uncover.cpp
sx_stealth_uncover_secret_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_stealth_addr_SOURCES = stealth-addr.cpp
sx_stealth_addr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_hd_seed_SOURCES = hd-seed.cpp
sx_hd_seed_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_hd_pub_SOURCES = hd-pub.cpp
sx_hd_pub_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_hd_priv_SOURCES = hd-priv.cpp
sx_hd_priv_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_hd_to_address_SOURCES = hd-to-address.cpp
sx_hd_to_address_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_hd_to_wif_SOURCES = hd-to-wif.cpp
sx_hd_to_wif_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_ripemd_hash_SOURCES = ripemd-hash.cpp
sx_ripemd_hash_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_initchain_SOURCES = initchain.cpp
sx_initchain_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_wrap_SOURCES = wrap.cpp
sx_wrap_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_unwrap_SOURCES = unwrap.cpp
sx_unwrap_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_decode_addr_SOURCES = decode-addr.cpp
sx_decode_addr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_encode_addr_SOURCES = encode-addr.cpp
sx_encode_addr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_base58_encode_SOURCES = base58-encode.cpp
sx_base58_encode_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_base58_decode_SOURCES = base58-decode.cpp
sx_base58_decode_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_showscript_SOURCES = showscript.cpp
sx_showscript_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_scripthash_SOURCES = scripthash.cpp
sx_scripthash_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_wif_to_secret_SOURCES = wif-to-secret.cpp
sx_wif_to_secret_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_rawscript_SOURCES = rawscript.cpp
sx_rawscript_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_pubkey_SOURCES = pubkey.cpp
sx_pubkey_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_genpub_SOURCES = genpub.cpp
sx_genpub_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_addr_SOURCES = addr.cpp
sx_addr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_sendtx_p2p_SOURCES = sendtx-p2p.cpp
sx_sendtx_p2p_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_genpriv_SOURCES = genpriv.cpp
sx_genpriv_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_genaddr_SOURCES = genaddr.cpp
sx_genaddr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_validsig_SOURCES = validsig.cpp
sx_validsig_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_mktx_SOURCES = mktx.cpp
sx_mktx_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_secret_to_wif_SOURCES = secret-to-wif.cpp
sx_secret_to_wif_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_mpk_SOURCES = mpk.cpp
sx_mpk_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_newkey_SOURCES = newkey.cpp
sx_newkey_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_newseed_SOURCES = newseed.cpp
sx_newseed_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_sendtx_node_SOURCES = sendtx-node.cpp
sx_sendtx_node_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_showblkhead_SOURCES = showblkhead.cpp
sx_showblkhead_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_validaddr_SOURCES = validaddr.cpp
sx_validaddr_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_showtx_SOURCES = showtx.cpp
sx_showtx_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_set_input_SOURCES = set-input.cpp
sx_set_input_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_sign_input_SOURCES = sign-input.cpp
sx_sign_input_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_mnemonic_SOURCES = mnemonic.cpp
sx_mnemonic_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS}

sx_history_SOURCES = history.cpp config.cpp
sx_history_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS}

sx_balance_SOURCES = balance.cpp config.cpp
sx_balance_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS}

sx_fetch_last_height_SOURCES = fetch-last-height.cpp config.cpp
sx_fetch_last_height_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS} 

sx_fetch_transaction_SOURCES = fetch-transaction.cpp config.cpp
sx_fetch_transaction_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS} 

sx_fetch_stealth_SOURCES = fetch-stealth.cpp config.cpp
sx_fetch_stealth_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS} 

sx_fetch_transaction_index_SOURCES = fetch-transaction-index.cpp config.cpp
sx_fetch_transaction_index_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS} 

sx_fetch_block_header_SOURCES = fetch-block-header.cpp config.cpp
sx_fetch_block_header_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS} 

sx_validtx_SOURCES = validtx.cpp config.cpp
sx_validtx_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS}

sx_sendtx_obelisk_SOURCES = sendtx-obelisk.cpp config.cpp
sx_sendtx_obelisk_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS}

sx_monitor_SOURCES = monitor.cpp config.cpp
sx_monitor_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS}

sx_wallet_SOURCES = wallet.cpp config.cpp
sx_wallet_LDADD = ${libbitcoin_LIBS} ${libwallet_LIBS} ${libobelisk_LIBS} -lncurses

