#!/bin/bash
#
# Script to build and install Bitcoin Explorer and unpackaged dependencies.
#
# This build script is based on a few ideas.
# -----------------------------------------------------------------------------
#  0. Start Clean: make reliable by never building from cached results.
#  1. Fail Fast: make all errors fail the build so that none are overlooked.
#  3. Self-Contain: build everything that needs to be built from one file.
#  2. Validate Dependencies: detect dependency breaks before they ship.
#  3. Validate Deployment: this file is both deployment and verification build.
#  3. Be Declarative: make behavior obvious by not using conditional statements.
#  4. Be Explicit: not everyone speaks the same code or human languages.
#  5. Use Least Privilege: don't require sudo for the entire script.
#  6. Do Not Repeat Yourself: do not repeat yourself.

# This script will build explorer from this relative directory.
# This is meant to be temporary, just to facilitate the install.
BUILD_DIRECTORY="libbitcoin_explorer_build"

# https://github.com/bitcoin/secp256k1
SECP256K1_OPTIONS=\
"--with-bignum=gmp "\
"--with-field=gmp "\
"--enable-benchmark=no "\
"--enable-tests=no "\
"--enable-endomorphism=no"

# http://bit.ly/1pKbuFP
BOOST_UNIT_TEST_PARAMETERS=\
"--run_test=* "\
"--random=1 "\
"--show_progress=yes "\
"--result_code=no "\
"--detect_memory_leak=0 "\
"--report_level=no "\
"--build_info=yes"

# The source repository for the main build.
# This will be adjusted to the Travis build if running in Travis.
BUILD_ACCOUNT="libbitcoin"
BUILD_REPO="libbitcoin_explorer"
BUILD_BRANCH="master"

check_travis()
{
    # If this is a Travis build switch to the requested repo/branch.
    if [ "x$TRAVIS_REPO_SLUG" != "x" ]; then
	    BUILD_ACCOUNT=`echo $TRAVIS_REPO_SLUG | cut -d'/' -f1`
	    BUILD_REPO=`echo $TRAVIS_REPO_SLUG | cut -d'/' -f2`
	    BUILD_BRANCH=$TRAVIS_BRANCH
    fi
}

github_build()
{
    # This function parameters.
    ACCOUNT=$1
    REPO=$2
    BRANCH=$3

    # Shift the first three parameters out of @.
    shift 3

    FORK=$ACCOUNT"/"$REPO
    echo
    echo "******************* install" $FORK"/"$BRANCH "**********************"
    echo
    
    # git clone the repo.
    rm -rf $REPO
    git clone --branch $BRANCH --single-branch "https://github.com/"$FORK
    cd $REPO
    
    # Do the standard stuff.
    ./autogen.sh
    ./configure "$@"
    make
    sudo make install
    sudo ldconfig
    
    cd ..
}

build_explorer()
{
    # Modify $BUILD_ACCOUNT $BUILD_REPO $BUILD_BRANCH if running in Travis.
    check_travis

    # Initialize git repository at the root of the build directory.
    git init
    git config user.name anonymous

    # Download, build and install all unpackaged dependencies.
    # This script args are passed to configure of each build.
    github_build jedisct1 libsodium master "$@"
    github_build zeromq libzmq master "$@"
    github_build zeromq czmq master "$@"
    github_build zeromq czmqpp master "$@"
    github_build bitcoin secp256k1 master "$@" $SECP256K1_OPTIONS
    github_build libbitcoin libbitcoin develop "$@"
    github_build libbitcoin obelisk develop "$@"
    github_build $BUILD_ACCOUNT $BUILD_REPO $BUILD_BRANCH "$@"
    
    # Run unit tests.
    cd libbitcoin_explorer/test
    ./explorer_test $BOOST_UNIT_TEST_PARAMETERS
    cd ../..

    # Verify execution (note that 'help' currently returns empty with success).
    cd libbitcoin_explorer/src
    ./explorer help
    cd ../..

    # Allow the user to invoke by typing BX or SX.
    sudo ln --symbolic --force /usr/local/bin/explorer /usr/local/bin/bx
    sudo ln --symbolic --force /usr/local/bin/explorer /usr/local/bin/sx
}

# Exit this script on the first error (any statement returns non-true value).
set -e

# Warn that this script will do something destructive.
echo "This script will erase and build in the subdirectory: "$BUILD_DIRECTORY

# Create and move to the build directory.
# Cache credentials for subsequent sudo calls and clean the build directory.
sudo rm -rf $BUILD_DIRECTORY
mkdir $BUILD_DIRECTORY
cd $BUILD_DIRECTORY

# Build explorer.
build_explorer "$@"

# If we succeed clean up the build directory.
# This precludes use of 'make uninstall' however that would need to be applied
# to dependencies as well. Typically each time a git pull occurs into a build
# directory the uninstall is potentially invalidated. This approach allows us
# to provide a script which performs a complete uninstall across all versions.
sudo rm -rf $BUILD_DIRECTORY
