#!/bin/sh
###############################################################################
# Copyright (c) 2014-2023 libbitcoin developers (see COPYING).
#
# Generate libbitcoin build artifacts from XML + GSL.
#
# This executes the iMatix GSL code generator.
# See https://github.com/imatix/gsl for details.
###############################################################################

# Exit this script on the first build error.
set -e

# Do everything relative to this file location.
cd `dirname "$0"`

mkdir -p ../data
mkdir -p ../src/commands
mkdir -p ../include/bitcoin/explorer/commands

gsl -q generate.xml
