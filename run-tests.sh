#!/bin/sh

# http://bit.ly/1pKbuFP
# Run all unit and component tests (excludes 'network' group).
BOOST_UNIT_TEST_PARAMETERS=\
"--run_test=primitives,generated,offline,stub,obsolete "\
"--random=1 "\
"--show_progress=yes "\
"--detect_memory_leak=0 "\
"--report_level=no "\
"--build_info=yes"

./test/libbitcoin_explorer_test $BOOST_UNIT_TEST_PARAMETERS

exit $?
