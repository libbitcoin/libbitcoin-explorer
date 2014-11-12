#!/bin/bash
#
# Script to build and install libbitcoin-explorer and unpackaged dependencies.
#

# BUGBUG: This script doesn't like spaces in paths.
# Verified on Ubuntu and OSX (MacPorts and Homebrew).
# If sudo is required the caller should sudo the script.

# --prefix=<absolute-path> Library install location (defaults to /usr/local).
# --build-dir=<path>       Location of downloaded and intermediate files.

# --build-gmp              Builds GMP library (use no value).
# --build-boost            Builds Boost libraries (use no value).

# --disable-shared         Disables shared library builds (use no value).
# --disable-static         Disables static library builds (use no value).

# All other options (and --prefix) are passed to each build's configure.

# Exit this script on the first error.
set -e

# The build directory, unless specified by --build-dir.
BUILD_DIR="bx-build"

# Boost v1.49
BOOST_URL="http://sourceforge.net/projects/boost/files/boost/1.49.0/boost_1_49_0.tar.bz2/download"
BOOST_ARCHIVE="boost_1_49_0.tar.bz2"

# GMP v6.0.0a
GMP_URL="https://ftp.gnu.org/gnu/gmp/gmp-6.0.0a.tar.bz2"
GMP_ARCHIVE="gmp-6.0.0a.tar.bz2"

# Various Boost configurations.
STATIC_BOOST="link=static"
SHARED_BOOST="link=shared"
DARWIN_BOOST=\
"toolset=clang "\
"cxxflags=-stdlib=libc++ "\
"linkflags=-stdlib=libc++"

# Homebrew: places each package in a distinct pkg-config path.
# Unlike other pkg managers Homebrew declares a package for GMP.
HOMEBREW_BOOST_ROOT_PATH="/usr/local/opt/boost"
HOMEBREW_PKG_CONFIG_PATHS="/usr/local/opt/gmp/lib/pkgconfig"

# MacPorts: necessary for GMP and Boost (no packages, paths only).
MACPORTS_LDFLAGS="-L/opt/local/lib"
MACPORTS_CPPFLAGS="-I/opt/local/include"
MACPORTS_LD_LIBRARY_PATH="/opt/local/lib"
MACPORTS_LD_INCLUDE_PATH="/opt/local/include"

# Set common libbitcoin options.
BITCOIN_OPTIONS=\
"--without-tests "\
"--enable-silent-rules"

# Set primary build target options.
BITCOIN_PRIMARY_OPTIONS=\
"--enable-silent-rules"

# Set Boost options.
# threading=single,multiple variant=release|debug
# Supress all informational messages (-d0), and stop at the first error (-q).
BOOST_OPTIONS=\
"threading=single "\
"variant=release "\
"--disable-icu "\
"--with-chrono "\
"--with-date_time "\
"--with-filesystem "\
"--with-program_options "\
"--with-regex "\
"--with-system "\
"--with-test "\
"-d0 "\
"-q"

# Set CZMQ makecert binary creation.
CZMQ_OPTIONS=\
"--without-makecert"

# Set GMP options (used CLang only, see below).
GMP_OPTIONS=""

# Set secp256k1 options, require GMP.
SECP256K1_OPTIONS=\
"--with-bignum=gmp "\
"--with-field=gmp "\
"--enable-benchmark=no "\
"--enable-tests=no "\
"--enable-endomorphism=no"

# Set Sodium options (used CLang only, see below).
SODIUM_OPTIONS=""

# Set ZMQ options, require libsodium.
ZMQ_OPTIONS=\
"--with-libsodium=yes"

# Define SEQUENTIAL (always 1), PARALLEL (number of concurrent jobs) and OS.
SEQUENTIAL=1
PARALLEL=2
OS=$(uname -s)
if [[ $TRAVIS = "true" ]]; then
    PARALLEL=$SEQUENTIAL
elif [[ $OS = "Linux" ]]; then
    PARALLEL=$(nproc)
elif [[ $OS = "Darwin" ]]; then
    PARALLEL=2
    PREFIX="/usr/local"
else
    echo "Unsupported system: $OS"
    exit 1
fi
 
# Parse command line options that we care about.
for i in "$@"; do
    case $i in
        (--prefix=*) PREFIX="${i#*=}";;
        (--build-dir=*) BUILD_DIR="${i#*=}";;

        (--build-gmp) BUILD_GMP="yes";;
        (--build-boost) BUILD_BOOST="yes";;
        
        (--disable-shared) DISABLE_SHARED="yes";;
        (--disable-static) DISABLE_STATIC="yes";;
    esac
done

# Purge our custom options so they don't go to configure.
CONFIGURE_OPTIONS=( "$@" )
CUSTOM_OPTIONS=( "--build-dir=$BUILD_DIR" "--build-boost" "--build-gmp" )
for OPTION in ${CUSTOM_OPTIONS[@]}
do
    CONFIGURE_OPTIONS=( "${CONFIGURE_OPTIONS[@]/$OPTION}" )
done

# Match boost linkage to other projects.
BOOST_LINK="static,shared"
if [[ $DISABLE_STATIC == "yes" ]]; then
    BOOST_LINK="shared"
elif [[ $DISABLE_SHARED == "yes" ]]; then
    BOOST_LINK="static"
fi
BOOST_OPTIONS="link=$BOOST_LINK $BOOST_OPTIONS"

# Configure OSX settings.
if [[ $OS == "Darwin" ]]; then

    # Always require CLang, common lib linking will otherwise fail.
    export CC="clang"
    export CXX="clang++"

    # Suppress CLang warnings (do here because we don't own these repos).
    # -Wno-unused-value -Wno-tautological-compare -Wno-empty-translation-unit
    GMP_OPTIONS="$GMP_OPTIONS CPPFLAGS=-Wno-parentheses"
    SODIUM_OPTIONS="$SODIUM_OPTIONS CPPFLAGS=-Qunused-arguments"
    SECP256K1_OPTIONS="$SECP256K1_OPTIONS CPPFLAGS=-Wno-unused-value"

    # Set up default Homebrew repository, if it exists.
    if [[ -d "/usr/local/opt" ]]; then
        export BOOST_ROOT="$HOMEBREW_BOOST_ROOT_PATH"
        export PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$HOMEBREW_PKG_CONFIG_PATHS"
    fi

    # Set up default MacPorts repository, if it exists.
    if [[ -d "/opt/local" ]]; then
        export LDFLAGS="$LDFLAGS $MACPORTS_LDFLAGS"
        export CPPFLAGS="$CPPFLAGS $MACPORTS_CPPFLAGS"
        export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:$MACPORTS_LD_LIBRARY_PATH"
        export LD_INCLUDE_PATH="$LD_INCLUDE_PATH:$MACPORTS_LD_INCLUDE_PATH"
    fi
    
    # Set up boost for CLang build.
    BOOST_OPTIONS="$BOOST_OPTIONS $DARWIN_BOOST"
fi

# Expose prefix, if it is specified (or on Darwin).
if [[ $PREFIX ]]; then

    # Add the prefix to the boost build options.
    BOOST_OPTIONS="$BOOST_OPTIONS --prefix=$PREFIX"

    # Augment PKG_CONFIG_PATH with prefix path, for pkg-config packages. 
    export PKG_CONFIG_PATH="$PREFIX/lib/pkgconfig:$PKG_CONFIG_PATH"

    # Boost M4 discovery searches in the following order:
    # --with-boost=<path>
    # /usr, /usr/local, /opt, /opt/local
    # BOOST_ROOT
    # These work for MacPorts, Linux (system) and Homebrew (BOOST_ROOT).
    # Below we incorporate and prioritize the --prefix path for boost.

    # Set boost path, assume internal build (no pkg-config).
    BOOST_LOAD="--with-boost=$PREFIX"

    # Augment include/lib paths for GMP, assuming local build (no pkg-config).
    GMP_LOAD="CPPFLAGS=-I$PREFIX/include LDFLAGS=-L$PREFIX/lib"

    SECP256K1_OPTIONS="$SECP256K1_OPTIONS $GMP_LOAD"
    BITCOIN_OPTIONS="$BITCOIN_OPTIONS $GMP_LOAD $BOOST_LOAD"
fi

# Give user feedback on build configuration.
echo "Install prefix: $PREFIX"
echo "Allocated jobs: $PARALLEL"
echo "Making for system: $OS"
echo "Build directory: $BUILD_DIR"
echo "Boost link: $BOOST_LINK"

display_message()
{
    MESSAGE=$1
    echo
    echo "********************** $MESSAGE **********************"
    echo
}

configure_options()
{
    echo "configure: $@"
    ./configure "$@"
}

make_silent()
{
    JOBS=$1
    TARGET=$2
    
    # Avoid setting -j1.
    if [[ $JOBS -gt $SEQUENTIAL ]]; then
        make --silent -j$JOBS $TARGET
    else
        make --silent
    fi
}

automake_current_directory()
{
    JOBS=$1
    shift 1

    ./autogen.sh
    configure_options "$@"
    make_silent $JOBS
    make install

    # Use ldconfig only in case of non --prefix installation on Linux.    
    if [[ ($OS == "Linux") && !($PREFIX)]]; then
        ldconfig
    fi
}

build_from_tarball_boost()
{
    URL=$1
    ARCHIVE=$2
    REPO=$3
    JOBS=$4
    shift 4

    if [[ $BUILD_BOOST != "yes" ]]; then
        display_message "Boost build not enabled"
        return
    fi
    
    display_message "Download $ARCHIVE"

    create_directory $REPO
    pushd $REPO

    # Extract the source locally.
    wget --output-document $ARCHIVE $URL
    tar --extract --file $ARCHIVE --bzip2 --strip-components=1

    echo "configure: $@"
    echo

    # Build and install (note that "$@" is not from script args).
    # -j N => Run up to N commands in parallel (TODO: validate -j/-j 1).
    ./bootstrap.sh
    ./b2 install -j $JOBS "$@"

    popd
}

build_from_tarball_gmp()
{
    URL=$1
    ARCHIVE=$2
    REPO=$3
    JOBS=$4
    shift 4

    if [[ $BUILD_GMP != "yes" ]]; then
        display_message "GMP build not enabled"
        return
    fi

    display_message "Download $ARCHIVE"
    
    create_directory $REPO
    pushd $REPO
    
    # Extract the source locally.
    wget --output-document $ARCHIVE $URL
    tar --extract --file $ARCHIVE --bzip2 --strip-components=1

    # Build the local sources.
    # GMP does not provide autogen.sh or package config.
    configure_options "$@"
    make_silent $JOBS
    make install

    popd
}

build_from_github()
{
    ACCOUNT=$1
    REPO=$2
    BRANCH=$3
    JOBS=$4
    shift 4

    FORK="$ACCOUNT/$REPO"
    display_message "Download $FORK/$BRANCH"
    
    # Clone the repo locally.
    git clone --branch $BRANCH --single-branch "https://github.com/$FORK"

    # Build the local repo clone.
    pushd $REPO
    automake_current_directory $JOBS "$@"
    popd
}

build_from_local()
{
    MESSAGE=$1
    JOBS=$2
    shift 2

    display_message $MESSAGE

    # Build the current directory.
    automake_current_directory $JOBS "$@"
}

build_primary()
{
    ACCOUNT=$1
    REPO=$2
    BRANCH=$3
    JOBS=$4
    shift 4
    
    # The primary build is not downloaded if we are running in Travis.
    if [[ $TRAVIS == "true" ]]; then
        cd ..
        build_from_local "Local $TRAVIS_REPO_SLUG" $JOBS "$@"
        build_tests
        cd $BUILD_DIR
    else
        build_from_github $ACCOUNT $REPO $BRANCH $JOBS "$@"
        pushd $REPO
        build_tests $JOBS
        popd
    fi
}

build_tests()
{
    JOBS=$1

    # Build and run unit tests relative to the primary directory.
    make_silent $JOBS check

    # Get the path.
    BX_PATH="bx"
    if [[ $PREFIX ]]; then
        BX_PATH="$PREFIX/bin/bx"
    fi

    # Verify linkage (static or dynamic).
    ldd --verbose $BX_PATH
    echo

    # Verify execution.
    $BX_PATH help

    echo "BX is located here: $BX_PATH"
}

create_directory()
{
    DIRECTORY=$1

    rm -rf $DIRECTORY
    mkdir $DIRECTORY
}

initialize_git()
{
    # Initialize git repository at the root of the current directory.
    git init
    git config user.name anonymous
}

build_library()
{
    create_directory $BUILD_DIR
    pushd $BUILD_DIR
    initialize_git

    # Build all dependencies and primary library.
    build_from_tarball_boost $BOOST_URL $BOOST_ARCHIVE boost $PARALLEL $BOOST_OPTIONS
    build_from_tarball_gmp $GMP_URL $GMP_ARCHIVE gmp $PARALLEL "$@" $GMP_OPTIONS
    build_from_github jedisct1 libsodium master $PARALLEL "$@" $SODIUM_OPTIONS
    build_from_github zeromq libzmq master $PARALLEL "$@" $ZMQ_OPTIONS
    build_from_github zeromq czmq master $PARALLEL "$@" $CZMQ_OPTIONS
    build_from_github zeromq czmqpp master $PARALLEL "$@"
    build_from_github bitcoin secp256k1 master $PARALLEL "$@" $SECP256K1_OPTIONS
    build_from_github evoskuil libbitcoin version2 $PARALLEL "$@" $BITCOIN_OPTIONS
    build_from_github evoskuil protobuf 2.6.0 $SEQUENTIAL "$@"
    build_from_github evoskuil libbitcoin-protocol version2 $PARALLEL "$@" $BITCOIN_OPTIONS
    build_from_github evoskuil libbitcoin-client version2 $PARALLEL "$@" $BITCOIN_OPTIONS
    build_primary evoskuil libbitcoin-explorer version2 $PARALLEL "$@" $BITCOIN_PRIMARY_OPTIONS

    popd
}

# Build the primary library and all dependencies.
time build_library "${CONFIGURE_OPTIONS[@]}"
