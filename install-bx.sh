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
#  5. Enable Least Privilege: don't require more privilege than necessary.
#  6. Do Not Repeat Yourself: do not repeat yourself.

# This script will build libbitcoin using this relative directory.
# This is meant to be temporary, just to facilitate the install.
BUILD_DIRECTORY="bx-build"

# The source repository for the primary build (when not running in Travis).
BUILD_ACCOUNT="libbitcoin"
BUILD_REPO="libbitcoin-explorer"
BUILD_BRANCH="master"

# enable testing
TEST_OPTIONS=\
"--with-tests=yes"

# https://github.com/bitcoin/secp256k1
SECP256K1_OPTIONS=\
"--with-bignum=gmp "\
"--with-field=gmp "\
"--enable-benchmark=no "\
"--enable-tests=no "\
"--enable-endomorphism=no"

ZMQ_OPTIONS=\
"--with-libsodium=yes"

SEQUENTIAL="1"

if [ "$TRAVIS" = "true" ]; then
    PARALLEL="$SEQUENTIAL"

    echo "Detected travis install, setting to non-parallel: $PARALLEL"
else
    NPROC=$(nproc)
    PARALLEL="$NPROC"

    echo "Detected cores for parallel make: $PARALLEL"
fi

display_message()
{
    MESSAGE=$1
    echo
    echo "********************** $MESSAGE **********************"
    echo
}

automake_current_directory()
{
    JOBS=$1
    shift 1

    ./autogen.sh
    ./configure --enable-silent-rules "$@"

    if [[ "$JOBS" -gt "$SEQUENTIAL" ]]; then
        make --silent "-j$JOBS"
    else
        make --silent
    fi

    # Sudo can be removed here if installing to a local directory (--prefix).
    sudo make install
    
    # This line can be removed it dynamic linking is not required.
    sudo ldconfig
}

build_from_github()
{
    ACCOUNT=$1
    REPO=$2
    BRANCH=$3
    JOBS=$4

    # Shift the first three parameters out of @.
    shift 4

    # Show the user what repo we are building.
    FORK="$ACCOUNT/$REPO"
    display_message "Download $FORK/$BRANCH"
    
    # Clone the repo locally.
    rm -rf $REPO
    git clone --branch $BRANCH --single-branch "https://github.com/$FORK"

    # Build the local repo clone.
    pushd $REPO
    automake_current_directory "$JOBS" "$@"
    popd
}

build_primary()
{
    JOBS=$1
    shift 1

    if [ "$TRAVIS" = "true" ]; then
        # If the environment is Travis drop out of build directory.
        cd ..
        display_message "Local $TRAVIS_REPO_SLUG"
	    automake_current_directory "$JOBS" "$@"
        build_tests
    else
        # Otherwise we pull the primary repo down for the single file install.
        build_from_github $BUILD_ACCOUNT $BUILD_REPO $BUILD_BRANCH "$JOBS" "$@"

        # Build the tests and drop out of build directory.
        pushd $BUILD_REPO
        build_tests "$JOBS"
        popd
        cd ..
    fi
}

build_tests()
{
    JOBS=$1

    # Build and run unit tests relative to the primary directory.
    if [[ "$JOBS" -gt "$SEQUENTIAL" ]]; then
        make check "-j$JOBS"
    else
        make check
    fi

    # Verify execution (note that 'help' currently returns empty with success).
    bx help
}

create_build_directory()
{
    # Notify that this script will do something destructive.
    echo "This script will erase and build in: $BUILD_DIRECTORY"

    # By default will require privilege, use --prefix=<directory> to avoid.
    rm --force --recursive $BUILD_DIRECTORY
    mkdir $BUILD_DIRECTORY
    cd $BUILD_DIRECTORY

    # Initialize git repository at the root of the build directory.
    git init
    git config user.name anonymous
}

build_library()
{
    # Create and move to a temporary build directory.
    create_build_directory

    # Download, build and install all unpackaged dependencies.
    build_from_github jedisct1 libsodium master "$SEQUENTIAL" "$@"
    build_from_github zeromq libzmq master "$SEQUENTIAL" "$@" $ZMQ_OPTIONS
    build_from_github zeromq czmq master "$SEQUENTIAL" "$@"
    build_from_github zeromq czmqpp master "$SEQUENTIAL" "$@"
    build_from_github evoskuil secp256k1 osx-patch "$SEQUENTIAL" "$@" $SECP256K1_OPTIONS
    build_from_github libbitcoin libbitcoin develop "$PARALLEL" "$@"
    build_from_github libbitcoin protobuf 2.6.0 "$SEQUENTIAL" "$@"
    build_from_github libbitcoin libbitcoin-protocol master "$PARALLEL" "$@"
    build_from_github libbitcoin libbitcoin-client master "$PARALLEL" "$@"

    # The primary build is not downloaded if we are running in Travis.
    build_primary "$PARALLEL" "$@" $TEST_OPTIONS

    # If the build succeeded clean up the build directory.
    delete_build_directory
}

delete_build_directory()
{
    # This precludes use of a 'make uninstall' however that would need to be 
    # applied to dependencies as well. Typically each time a git pull occurs 
    # into a build directory the uninstall is potentially invalidated. This 
    # approach allows us to perform a complete uninstall across all versions.
    rm --force --recursive $BUILD_DIRECTORY
}

# Exit this script on the first error (any statement returns non-true value).
set -e

# Build the primary library and its unpackaged dependencies.
build_library "$@"

