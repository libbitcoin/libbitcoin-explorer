#!/bin/sh
###############################################################################
#  Copyright (c) 2014-2020 libbitcoin-explorer developers (see COPYING).
#
#         GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
#
###############################################################################

# Define tests and options.
#==============================================================================
BOOST_UNIT_TEST_OPTIONS=\
"--run_test=generated,obsolete,offline,config,stub "\
"--show_progress=no "\
"--detect_memory_leak=0 "\
"--report_level=no "\
"--build_info=yes"


# Run tests.
#==============================================================================
./test/libbitcoin-explorer-test ${BOOST_UNIT_TEST_OPTIONS} > test.log
