###############################################################################
#  Copyright (c) 2014-2020 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# libbitcoin-explorer project configuration.
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(libbitcoin-explorer LANGUAGES C CXX)

enable_testing()

list( APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules" )
include(CheckIncludeFiles)
include(CheckSymbolExists)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (MSVC)
  set( CANONICAL_LIB_NAME libbitcoin-explorer )
else ()
  set( CANONICAL_LIB_NAME bitcoin-explorer )
  find_package( PkgConfig REQUIRED )

  set( prefix "${CMAKE_PREFIX_PATH}" )
  set( exec_prefix "\${prefix}" )
  set( libdir "\${exec_prefix}/lib" )
  set( includedir "\${exec_prefix}/include" )

  set( PACKAGE_VERSION "4.0.0" )
  set( VERSION "${PACKAGE_VERSION}" )
endif ()

set( CMAKE_CXX_STANDARD 11 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# Add compiler options
#------------------------------------------------------------------------------
# Warn on all stuff.
add_compile_options( "-Wall" )

# Warn on extra stuff.
add_compile_options( "-Wextra" )

# Be really annoying.
add_compile_options( "-Wpedantic" )

# Disallow warning on style order of declarations.
add_compile_options( "-Wno-reorder" )

# Suppress warning for incomplete field initialization.
add_compile_options( "-Wno-missing-field-initializers" )

# Conform to style.
add_compile_options( "-Wno-missing-braces" )

# Ignore comments within comments or commenting of backslash extended lines.
add_compile_options( "-Wno-comment" )

# Clean up bx generated code.
add_compile_options( "-Wno-unused-parameter" )

# Conflict in stdlib under clang.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options( "-Wno-mismatched-tags" )
endif()

# Implement -Dbash-completiondir and output ${bash-completiondir} and declare bash-completiondir.
#------------------------------------------------------------------------------
set( bash-completiondir "no" CACHE BOOL "Install bash completion support, optionally specifying the directory. This option may require elevated permissions." )

# Implement -Dpkgconfigdir and output ${pkgconfigdir}.
#------------------------------------------------------------------------------
set( pkgconfigdir "${libdir}/pkgconfig" CACHE PATH "Path to pkgconfig directory." )

# Implement -Dwith-tests and declare with-tests.
#------------------------------------------------------------------------------
set( with-tests "yes" CACHE BOOL "Compile with unit tests." )

# Implement -Dwith-console and declare with-console.
#------------------------------------------------------------------------------
set( with-console "yes" CACHE BOOL "Compile console application." )

# Implement -Denable-ndebug and define NDEBUG.
#------------------------------------------------------------------------------
set( enable-ndebug "yes" CACHE BOOL "Compile without debug assertions." )

if (enable-ndebug)
    add_definitions( -DNDEBUG )
endif()

# Inherit -Denable-shared and define BOOST_ALL_DYN_LINK.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

# Find boost
#------------------------------------------------------------------------------
find_package( Boost 1.72.0 REQUIRED COMPONENTS
    unit_test_framework )

set( boost_unit_test_framework_LIBS "-lboost_unit_test_framework" )

if (enable-ndebug)
    set( Boost_LIBRARY_DIR "${Boost_LIBRARY_DIR_DEBUG}" )
else ()
    set( Boost_LIBRARY_DIR "${Boost_LIBRARY_DIR_RELEASE}" )
endif()

set( boost_CPPFLAGS "-I${Boost_INCLUDE_DIR}" )
set( boost_LDFLAGS "-L${Boost_LIBRARY_DIR}" )

# Find bash-completion
#------------------------------------------------------------------------------
if (bash-completiondir)
    find_package( Bash-Completion 2.0.0 REQUIRED )
endif()

# Find bitcoin-client
#------------------------------------------------------------------------------
find_package( Bitcoin-Client 4.0.0 REQUIRED )

# Find bitcoin-network
#------------------------------------------------------------------------------
find_package( Bitcoin-Network 4.0.0 REQUIRED )

# Find dl
#------------------------------------------------------------------------------
if ((${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    find_package( Dl REQUIRED )
endif()

# Define project common includes directories
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    include_directories( SYSTEM
        ${bitcoin_client_INCLUDE_DIRS}
        ${bitcoin_network_INCLUDE_DIRS}
        ${dl_INCLUDE_DIRS} )
else()
    include_directories( SYSTEM
        ${bitcoin_client_STATIC_INCLUDE_DIRS}
        ${bitcoin_network_STATIC_INCLUDE_DIRS}
        ${dl_INCLUDE_DIRS} )
endif()

# Define project common library directories
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    link_directories(
        ${bitcoin_client_LIBRARY_DIRS}
        ${bitcoin_network_LIBRARY_DIRS}
        ${dl_LIBRARY_DIRS} )
else()
    link_directories(
        ${bitcoin_client_STATIC_LIBRARY_DIRS}
        ${bitcoin_network_STATIC_LIBRARY_DIRS}
        ${dl_LIBRARY_DIRS} )
endif()

# Define project common libraries/linker flags.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    link_libraries(
        "-fstack-protector"
        "-fstack-protector-all"
        ${bitcoin_client_LIBRARIES}
        ${bitcoin_network_LIBRARIES}
        ${dl_LIBRARIES} )
else()
    link_libraries(
        "-fstack-protector"
        "-fstack-protector-all"
        ${bitcoin_client_STATIC_LIBRARIES}
        ${bitcoin_network_STATIC_LIBRARIES}
        ${dl_LIBRARIES} )
endif()

add_definitions(
    -DSYSCONFDIR=\"${sysconfdir}\" )

# Define ${CANONICAL_LIB_NAME} project.
#------------------------------------------------------------------------------
add_library( ${CANONICAL_LIB_NAME}
    "../../src/callback_state.cpp"
    "../../src/dispatch.cpp"
    "../../src/display.cpp"
    "../../src/generated.cpp"
    "../../src/parser.cpp"
    "../../src/prop_tree.cpp"
    "../../src/utility.cpp"
    "../../src/commands/address-decode.cpp"
    "../../src/commands/address-embed.cpp"
    "../../src/commands/address-encode.cpp"
    "../../src/commands/address-to-key.cpp"
    "../../src/commands/base16-decode.cpp"
    "../../src/commands/base16-encode.cpp"
    "../../src/commands/base58-decode.cpp"
    "../../src/commands/base58-encode.cpp"
    "../../src/commands/base58check-decode.cpp"
    "../../src/commands/base58check-encode.cpp"
    "../../src/commands/base64-decode.cpp"
    "../../src/commands/base64-encode.cpp"
    "../../src/commands/bitcoin160.cpp"
    "../../src/commands/bitcoin256.cpp"
    "../../src/commands/broadcast-tx.cpp"
    "../../src/commands/btc-to-satoshi.cpp"
    "../../src/commands/cert-new.cpp"
    "../../src/commands/cert-public.cpp"
    "../../src/commands/ec-add-secrets.cpp"
    "../../src/commands/ec-add.cpp"
    "../../src/commands/ec-decompress.cpp"
    "../../src/commands/ec-multiply-secrets.cpp"
    "../../src/commands/ec-multiply.cpp"
    "../../src/commands/ec-new.cpp"
    "../../src/commands/ec-to-address.cpp"
    "../../src/commands/ec-to-ek.cpp"
    "../../src/commands/ec-to-public.cpp"
    "../../src/commands/ec-to-wif.cpp"
    "../../src/commands/ec-to-witness.cpp"
    "../../src/commands/ek-address.cpp"
    "../../src/commands/ek-new.cpp"
    "../../src/commands/ek-public-to-address.cpp"
    "../../src/commands/ek-public-to-ec.cpp"
    "../../src/commands/ek-public.cpp"
    "../../src/commands/ek-to-address.cpp"
    "../../src/commands/ek-to-ec.cpp"
    "../../src/commands/electrum-new.cpp"
    "../../src/commands/electrum-to-seed.cpp"
    "../../src/commands/fetch-balance.cpp"
    "../../src/commands/fetch-block-hashes.cpp"
    "../../src/commands/fetch-block-height.cpp"
    "../../src/commands/fetch-block.cpp"
    "../../src/commands/fetch-filter-checkpoint.cpp"
    "../../src/commands/fetch-filter-headers.cpp"
    "../../src/commands/fetch-filter.cpp"
    "../../src/commands/fetch-header.cpp"
    "../../src/commands/fetch-height.cpp"
    "../../src/commands/fetch-history.cpp"
    "../../src/commands/fetch-public-key.cpp"
    "../../src/commands/fetch-tx-index.cpp"
    "../../src/commands/fetch-tx.cpp"
    "../../src/commands/fetch-utxo.cpp"
    "../../src/commands/get-filter-checkpoint.cpp"
    "../../src/commands/get-filter-headers.cpp"
    "../../src/commands/get-filters.cpp"
    "../../src/commands/hd-new.cpp"
    "../../src/commands/hd-private.cpp"
    "../../src/commands/hd-public.cpp"
    "../../src/commands/hd-to-address.cpp"
    "../../src/commands/hd-to-ec.cpp"
    "../../src/commands/hd-to-public.cpp"
    "../../src/commands/hd-to-wif.cpp"
    "../../src/commands/help.cpp"
    "../../src/commands/input-set.cpp"
    "../../src/commands/input-sign.cpp"
    "../../src/commands/input-validate.cpp"
    "../../src/commands/match-neutrino-address.cpp"
    "../../src/commands/match-neutrino-script.cpp"
    "../../src/commands/message-sign.cpp"
    "../../src/commands/message-validate.cpp"
    "../../src/commands/mnemonic-decode.cpp"
    "../../src/commands/mnemonic-encode.cpp"
    "../../src/commands/mnemonic-to-seed.cpp"
    "../../src/commands/put-tx.cpp"
    "../../src/commands/qrcode.cpp"
    "../../src/commands/ripemd160.cpp"
    "../../src/commands/satoshi-to-btc.cpp"
    "../../src/commands/script-decode.cpp"
    "../../src/commands/script-encode.cpp"
    "../../src/commands/script-to-address.cpp"
    "../../src/commands/script-to-key.cpp"
    "../../src/commands/seed.cpp"
    "../../src/commands/send-tx.cpp"
    "../../src/commands/settings.cpp"
    "../../src/commands/sha160.cpp"
    "../../src/commands/sha256.cpp"
    "../../src/commands/sha512.cpp"
    "../../src/commands/stealth-decode.cpp"
    "../../src/commands/stealth-encode.cpp"
    "../../src/commands/stealth-public.cpp"
    "../../src/commands/stealth-secret.cpp"
    "../../src/commands/stealth-shared.cpp"
    "../../src/commands/subscribe-block.cpp"
    "../../src/commands/subscribe-tx.cpp"
    "../../src/commands/token-new.cpp"
    "../../src/commands/tx-decode.cpp"
    "../../src/commands/tx-encode.cpp"
    "../../src/commands/tx-sign.cpp"
    "../../src/commands/uri-decode.cpp"
    "../../src/commands/uri-encode.cpp"
    "../../src/commands/validate-tx.cpp"
    "../../src/commands/version.cpp"
    "../../src/commands/watch-key.cpp"
    "../../src/commands/watch-tx.cpp"
    "../../src/commands/wif-to-ec.cpp"
    "../../src/commands/wif-to-public.cpp"
    "../../src/commands/witness-to-key.cpp"
    "../../src/commands/wrap-decode.cpp"
    "../../src/commands/wrap-encode.cpp"
    "../../src/config/address.cpp"
    "../../src/config/address_format.cpp"
    "../../src/config/algorithm.cpp"
    "../../src/config/btc.cpp"
    "../../src/config/byte.cpp"
    "../../src/config/cert_key.cpp"
    "../../src/config/ec_private.cpp"
    "../../src/config/electrum.cpp"
    "../../src/config/encoding.cpp"
    "../../src/config/endorsement.cpp"
    "../../src/config/hashtype.cpp"
    "../../src/config/hd_key.cpp"
    "../../src/config/language.cpp"
    "../../src/config/raw.cpp"
    "../../src/config/signature.cpp"
    "../../src/config/wrapper.cpp" )

# ${CANONICAL_LIB_NAME} project specific include directories.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    target_include_directories( ${CANONICAL_LIB_NAME} PRIVATE
        "../../include"
        ${bitcoin_client_INCLUDE_DIRS}
        ${bitcoin_network_INCLUDE_DIRS}
        ${dl_INCLUDE_DIRS} )
else()
    target_include_directories( ${CANONICAL_LIB_NAME} PRIVATE
        "../../include"
        ${bitcoin_client_STATIC_INCLUDE_DIRS}
        ${bitcoin_network_STATIC_INCLUDE_DIRS}
        ${dl_INCLUDE_DIRS} )
endif()

target_include_directories( ${CANONICAL_LIB_NAME} PUBLIC
"../../include" )

# ${CANONICAL_LIB_NAME} project specific libraries/linker flags.
#------------------------------------------------------------------------------
if (BUILD_SHARED_LIBS)
    target_link_libraries( ${CANONICAL_LIB_NAME}
        ${bitcoin_client_LIBRARIES}
        ${bitcoin_network_LIBRARIES}
        ${dl_LIBRARIES} )
else()
    target_link_libraries( ${CANONICAL_LIB_NAME}
        ${bitcoin_client_STATIC_LIBRARIES}
        ${bitcoin_network_STATIC_LIBRARIES}
        ${dl_LIBRARIES} )
endif()

# Define bx project.
#------------------------------------------------------------------------------
if (with-console)
    add_executable( bx
        "../../console/libbitcoin.ico"
        "../../console/main.cpp" )

#     bx project specific include directories.
#------------------------------------------------------------------------------
    target_include_directories( bx PRIVATE
        "../../include" )

#     bx project specific libraries/linker flags.
#------------------------------------------------------------------------------
    target_link_libraries( bx
        ${CANONICAL_LIB_NAME} )

endif()

# Define libbitcoin-explorer-test project.
#------------------------------------------------------------------------------
if (with-tests)
    add_executable( libbitcoin-explorer-test
        "../../test/generated__broadcast.cpp"
        "../../test/generated__find.cpp"
        "../../test/generated__formerly.cpp"
        "../../test/generated__symbol.cpp"
        "../../test/main.cpp"
        "../../test/commands/address-decode.cpp"
        "../../test/commands/address-embed.cpp"
        "../../test/commands/address-encode.cpp"
        "../../test/commands/address-to-key.cpp"
        "../../test/commands/base16-decode.cpp"
        "../../test/commands/base16-encode.cpp"
        "../../test/commands/base58-decode.cpp"
        "../../test/commands/base58-encode.cpp"
        "../../test/commands/base58check-decode.cpp"
        "../../test/commands/base58check-encode.cpp"
        "../../test/commands/base64-decode.cpp"
        "../../test/commands/base64-encode.cpp"
        "../../test/commands/bitcoin160.cpp"
        "../../test/commands/bitcoin256.cpp"
        "../../test/commands/broadcast-tx.cpp"
        "../../test/commands/btc-to-satoshi.cpp"
        "../../test/commands/cert-new.cpp"
        "../../test/commands/cert-public.cpp"
        "../../test/commands/command.hpp"
        "../../test/commands/ec-add-secrets.cpp"
        "../../test/commands/ec-add.cpp"
        "../../test/commands/ec-decompress.cpp"
        "../../test/commands/ec-multiply-secrets.cpp"
        "../../test/commands/ec-multiply.cpp"
        "../../test/commands/ec-new.cpp"
        "../../test/commands/ec-to-address.cpp"
        "../../test/commands/ec-to-ek.cpp"
        "../../test/commands/ec-to-public.cpp"
        "../../test/commands/ec-to-wif.cpp"
        "../../test/commands/ec-to-witness.cpp"
        "../../test/commands/ek-address.cpp"
        "../../test/commands/ek-new.cpp"
        "../../test/commands/ek-public-to-address.cpp"
        "../../test/commands/ek-public-to-ec.cpp"
        "../../test/commands/ek-public.cpp"
        "../../test/commands/ek-to-address.cpp"
        "../../test/commands/ek-to-ec.cpp"
        "../../test/commands/electrum-decode.cpp"
        "../../test/commands/electrum-new.cpp"
        "../../test/commands/electrum-to-seed.cpp"
        "../../test/commands/fetch-balance.cpp"
        "../../test/commands/fetch-block.cpp"
        "../../test/commands/fetch-header.cpp"
        "../../test/commands/fetch-height.cpp"
        "../../test/commands/fetch-history.cpp"
        "../../test/commands/fetch-public-key.cpp"
        "../../test/commands/fetch-tx-index.cpp"
        "../../test/commands/fetch-tx.cpp"
        "../../test/commands/fetch-utxo.cpp"
        "../../test/commands/get-filter-checkpoint.cpp"
        "../../test/commands/get-filter-headers.cpp"
        "../../test/commands/get-filters.cpp"
        "../../test/commands/hd-new.cpp"
        "../../test/commands/hd-private.cpp"
        "../../test/commands/hd-public.cpp"
        "../../test/commands/hd-to-address.cpp"
        "../../test/commands/hd-to-ec.cpp"
        "../../test/commands/hd-to-public.cpp"
        "../../test/commands/hd-to-wif.cpp"
        "../../test/commands/help.cpp"
        "../../test/commands/input-set.cpp"
        "../../test/commands/input-sign.cpp"
        "../../test/commands/input-validate.cpp"
        "../../test/commands/match-neutrino-address.cpp"
        "../../test/commands/match-neutrino-script.cpp"
        "../../test/commands/message-sign.cpp"
        "../../test/commands/message-validate.cpp"
        "../../test/commands/mnemonic-decode.cpp"
        "../../test/commands/mnemonic-encode.cpp"
        "../../test/commands/mnemonic-to-seed.cpp"
        "../../test/commands/put-tx.cpp"
        "../../test/commands/qrcode.cpp"
        "../../test/commands/ripemd160.cpp"
        "../../test/commands/satoshi-to-btc.cpp"
        "../../test/commands/script-decode.cpp"
        "../../test/commands/script-encode.cpp"
        "../../test/commands/script-to-address.cpp"
        "../../test/commands/script-to-key.cpp"
        "../../test/commands/seed.cpp"
        "../../test/commands/send-tx.cpp"
        "../../test/commands/settings.cpp"
        "../../test/commands/sha160.cpp"
        "../../test/commands/sha256.cpp"
        "../../test/commands/sha512.cpp"
        "../../test/commands/stealth-decode.cpp"
        "../../test/commands/stealth-encode.cpp"
        "../../test/commands/stealth-public.cpp"
        "../../test/commands/stealth-secret.cpp"
        "../../test/commands/stealth-shared.cpp"
        "../../test/commands/subscribe-block.cpp"
        "../../test/commands/subscribe-tx.cpp"
        "../../test/commands/token-new.cpp"
        "../../test/commands/tx-decode.cpp"
        "../../test/commands/tx-encode.cpp"
        "../../test/commands/tx-sign.cpp"
        "../../test/commands/uri-decode.cpp"
        "../../test/commands/uri-encode.cpp"
        "../../test/commands/validate-tx.cpp"
        "../../test/commands/watch-key.cpp"
        "../../test/commands/watch-tx.cpp"
        "../../test/commands/wif-to-ec.cpp"
        "../../test/commands/wif-to-public.cpp"
        "../../test/commands/witness-to-key.cpp"
        "../../test/commands/wrap-decode.cpp"
        "../../test/commands/wrap-encode.cpp"
        "../../test/config/address.cpp" )

    add_test( NAME libbitcoin-explorer-test COMMAND libbitcoin-explorer-test
            --run_test=generated,obsolete,offline,config,stub
            --show_progress=no
            --detect_memory_leak=0
            --report_level=no
            --build_info=yes )

#     libbitcoin-explorer-test project specific include directories.
#------------------------------------------------------------------------------
    target_include_directories( libbitcoin-explorer-test PRIVATE
        "../../include" )

#     libbitcoin-explorer-test project specific libraries/linker flags.
#------------------------------------------------------------------------------
    target_link_libraries( libbitcoin-explorer-test
        ${CANONICAL_LIB_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

endif()

# Manage pkgconfig installation.
#------------------------------------------------------------------------------
configure_file(
  "../../libbitcoin-explorer.pc.in"
  "libbitcoin-explorer.pc" @ONLY )

install( FILES
    "${CMAKE_CURRENT_BINARY_DIR}/libbitcoin-explorer.pc"
    DESTINATION "${pkgconfigdir}" )

# Manage installation of docs.
#------------------------------------------------------------------------------
install( FILES
    "../../AUTHORS"
    "../../COPYING"
    "../../ChangeLog"
    "../../INSTALL"
    "../../NEWS"
    "../../README"
    DESTINATION share/doc/libbitcoin-explorer )

# Manage ${CANONICAL_LIB_NAME} installation.
#------------------------------------------------------------------------------
install( TARGETS ${CANONICAL_LIB_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include )

# Manage bx installation.
#------------------------------------------------------------------------------
if (with-console)
    install( TARGETS bx
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include )
endif()

# Manage include installation.
#------------------------------------------------------------------------------
install( DIRECTORY "../../include/bitcoin"
    DESTINATION include )

# Manage data installation for bash_completion prefixed product.
#------------------------------------------------------------------------------
if (bash-completiondir)
    install( FILES
        "../../data/bx"
        DESTINATION etc/libbitcoin )
endif()

# Manage data installation for sysconf prefixed product.
#------------------------------------------------------------------------------
if (with-console)
    install( FILES
        "../../data/bx.cfg"
        DESTINATION etc/libbitcoin )
endif()

