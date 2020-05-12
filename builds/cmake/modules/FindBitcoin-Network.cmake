###############################################################################
#  Copyright (c) 2014-2020 libbitcoin-node developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################
# FindBitcoin-Network
#
# Use this module by invoking find_package with the form::
#
#   find_package( Bitcoin-Network
#     [version]              # Minimum version
#     [REQUIRED]             # Fail with error if bitcoin-network is not found
#   )
#
#   Defines the following for use:
#
#   bitcoin_network_FOUND                 - true if headers and requested libraries were found
#   bitcoin_network_INCLUDE_DIRS          - include directories for bitcoin-network libraries
#   bitcoin_network_LIBRARY_DIRS          - link directories for bitcoin-network libraries
#   bitcoin_network_LIBRARIES             - bitcoin-network libraries to be linked
#   bitcoin_network_PKG                   - bitcoin-network pkg-config package specification.
#

if (MSVC)
    if ( Bitcoin-Network_FIND_REQUIRED )
        set( _bitcoin_network_MSG_STATUS "SEND_ERROR" )
    else ()
        set( _bitcoin_network_MSG_STATUS "STATUS" )
    endif()

    set( bitcoin_network_FOUND false )
    message( ${_bitcoin_network_MSG_STATUS} "MSVC environment detection for 'bitcoin-network' not currently supported." )
else ()
    # required
    if ( Bitcoin-Network_FIND_REQUIRED )
        set( _bitcoin_network_REQUIRED "REQUIRED" )
    endif()

    # quiet
    if ( Bitcoin-Network_FIND_QUIETLY )
        set( _bitcoin_network_QUIET "QUIET" )
    endif()

    # modulespec
    if ( Bitcoin-Network_FIND_VERSION_COUNT EQUAL 0 )
        set( _bitcoin_network_MODULE_SPEC "libbitcoin-network" )
    else ()
        if ( Bitcoin-Network_FIND_VERSION_EXACT )
            set( _bitcoin_network_MODULE_SPEC_OP "=" )
        else ()
            set( _bitcoin_network_MODULE_SPEC_OP ">=" )
        endif()

        set( _bitcoin_network_MODULE_SPEC "libbitcoin-network ${_bitcoin_network_MODULE_SPEC_OP} ${Bitcoin-Network_FIND_VERSION}" )
    endif()

    pkg_check_modules( bitcoin_network ${_bitcoin_network_REQUIRED} ${_bitcoin_network_QUIET} "${_bitcoin_network_MODULE_SPEC}" )
    set( bitcoin_network_PKG "${_bitcoin_network_MODULE_SPEC}" )
endif()
