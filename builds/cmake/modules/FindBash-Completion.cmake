###############################################################################
#  Copyright (c) 2014-2020 libbitcoin-server developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################
# FindBash-Completion
#
# Use this module by invoking find_package with the form::
#
#   find_package( Bash-Completion
#     [version]              # Minimum version
#     [REQUIRED]             # Fail with error if bash-completion is not found
#   )
#
#   Defines the following for use:
#
#   bash_completion_FOUND                 - true if headers and requested libraries were found
#   bash_completion_INCLUDE_DIRS          - include directories for bash-completion libraries
#   bash_completion_LIBRARY_DIRS          - link directories for bash-completion libraries
#   bash_completion_LIBRARIES             - bash-completion libraries to be linked
#   bash_completion_PKG                   - bash-completion pkg-config package specification.
#

if (MSVC)
    if ( Bash-Completion_FIND_REQUIRED )
        set( _bash_completion_MSG_STATUS "SEND_ERROR" )
    else ()
        set( _bash_completion_MSG_STATUS "STATUS" )
    endif()

    set( bash_completion_FOUND false )
    message( ${_bash_completion_MSG_STATUS} "MSVC environment detection for 'bash-completion' not currently supported." )
else ()
    # required
    if ( Bash-Completion_FIND_REQUIRED )
        set( _bash_completion_REQUIRED "REQUIRED" )
    endif()

    # quiet
    if ( Bash-Completion_FIND_QUIETLY )
        set( _bash_completion_QUIET "QUIET" )
    endif()

    # modulespec
    if ( Bash-Completion_FIND_VERSION_COUNT EQUAL 0 )
        set( _bash_completion_MODULE_SPEC "bash-completion" )
    else ()
        if ( Bash-Completion_FIND_VERSION_EXACT )
            set( _bash_completion_MODULE_SPEC_OP "=" )
        else ()
            set( _bash_completion_MODULE_SPEC_OP ">=" )
        endif()

        set( _bash_completion_MODULE_SPEC "bash-completion ${_bash_completion_MODULE_SPEC_OP} ${Bash-Completion_FIND_VERSION}" )
    endif()

    pkg_check_modules( bash_completion ${_bash_completion_REQUIRED} ${_bash_completion_QUIET} "${_bash_completion_MODULE_SPEC}" )
    set( bash_completion_PKG "${_bash_completion_MODULE_SPEC}" )
endif()
