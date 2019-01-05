###############################################################################
#  Copyright (c) 2014-2019 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################
# FindBitcoin-Client
#
# Use this module by invoking find_package with the form::
#
#   find_package( Bitcoin-Client
#     [version]              # Minimum version
#     [REQUIRED]             # Fail with error if bitcoin-client is not found
#   )
#
#   Defines the following for use:
#
#   bitcoin_client_FOUND                  - true if headers and requested libraries were found
#   bitcoin_client_INCLUDE_DIRS           - include directories for bitcoin-client libraries
#   bitcoin_client_LIBRARY_DIRS           - link directories for bitcoin-client libraries
#   bitcoin_client_LIBRARIES              - bitcoin-client libraries to be linked
#   bitcoin_client_PKG                    - bitcoin-client pkg-config package specification.
#

if (MSVC)
    if ( Bitcoin-Client_FIND_REQUIRED )
        set( _bitcoin_client_MSG_STATUS "SEND_ERROR" )
    else ()
        set( _bitcoin_client_MSG_STATUS "STATUS" )
    endif()

    set( bitcoin_client_FOUND false )
    message( ${_bitcoin_client_MSG_STATUS} "MSVC environment detection for 'bitcoin-client' not currently supported." )
else ()
    # required
    if ( Bitcoin-Client_FIND_REQUIRED )
        set( _bitcoin_client_REQUIRED "REQUIRED" )
    endif()

    # quiet
    if ( Bitcoin-Client_FIND_QUIETLY )
        set( _bitcoin_client_QUIET "QUIET" )
    endif()

    # modulespec
    if ( Bitcoin-Client_FIND_VERSION_COUNT EQUAL 0 )
        set( _bitcoin_client_MODULE_SPEC "libbitcoin-client" )
    else ()
        if ( Bitcoin-Client_FIND_VERSION_EXACT )
            set( _bitcoin_client_MODULE_SPEC_OP "=" )
        else ()
            set( _bitcoin_client_MODULE_SPEC_OP ">=" )
        endif()

        set( _bitcoin_client_MODULE_SPEC "libbitcoin-client ${_bitcoin_client_MODULE_SPEC_OP} ${Bitcoin-Client_FIND_VERSION}" )
    endif()

    pkg_check_modules( bitcoin_client ${_bitcoin_client_REQUIRED} ${_bitcoin_client_QUIET} "${_bitcoin_client_MODULE_SPEC}" )
    set( bitcoin_client_PKG "${_bitcoin_client_MODULE_SPEC}" )
endif()
