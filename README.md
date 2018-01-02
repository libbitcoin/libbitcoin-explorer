[![Build Status](https://travis-ci.org/libbitcoin/libbitcoin-explorer.svg?branch=master)](https://travis-ci.org/libbitcoin/libbitcoin-explorer)

[![Coverage Status](https://coveralls.io/repos/libbitcoin/libbitcoin-explorer/badge.svg)](https://coveralls.io/r/libbitcoin/libbitcoin-explorer)

*The automated build often fails on generating test metrics due to performance limits on Travis.*

# Bitcoin Explorer

*The Bitcoin Command Line Tool*

[Documentation](https://github.com/libbitcoin/libbitcoin-explorer/wiki) is available on the wiki.

[Downloads](https://github.com/libbitcoin/libbitcoin-explorer/wiki/Download-BX) are available for Linux, Macintosh and Windows.

**License Overview**

All files in this repository fall under the license specified in [COPYING](https://github.com/libbitcoin/libbitcoin-explorer/blob/master/COPYING). The project is licensed as [AGPL with a lesser clause](https://wiki.unsystem.net/en/index.php/Libbitcoin/License). It may be used within a proprietary project, but the core library and any changes to it must be published on-line. Source code for this library must always remain free for everybody to access.

**About Libbitcoin**

The libbitcoin toolkit is a set of cross platform C++ libraries for building bitcoin applications. The toolkit consists of several libraries, most of which depend on the foundational [libbitcoin](https://github.com/libbitcoin/libbitcoin) library. Each library's repository can be cloned and built using common [Automake](http://www.gnu.org/software/automake) instructions.

**About Libbitcoin Explorer**

BX is a command line tool for working with Bitcoin. It can be built as a single portable executable for Linux, macOS or Windows and is available for download as a signed single executable for each. BX exposes over 80 commands and supports network communication with [libbitcoin-server](https://github.com/libbitcoin/libbitcoin-server) or its predecessor [Obelisk](https://github.com/spesmilo/obelisk), and the P2P Bitcoin network. BX is well documented and supports simple and advanced scenarios, including stealth and multisig.

## Installation

BX can be built from sources or downloaded as a signed portable [single file executable](https://github.com/libbitcoin/libbitcoin-explorer/wiki/Download-BX).

On Linux and Macintosh BX is built using Autotools as follows and depends on [libbitcoin-client](https://github.com/libbitcoin/libbitcoin-client).

```sh
$ ./autogen.sh
$ ./configure
$ make
$ sudo make install # optional
$ sudo ldconfig     # optional
```

Detailed instructions are provided below.
* [Debian/Ubuntu](#debianubuntu)
* [Macintosh](#macintosh)
* [Windows](#windows)

### Debian/Ubuntu

Libbitcoin requires a C++11 compiler, currently minimum [GCC 4.8.0](https://gcc.gnu.org/projects/cxx0x.html) or Clang based on [LLVM 3.5](http://llvm.org/releases/3.5.0/docs/ReleaseNotes.html).

To see your GCC version:
```sh
$ g++ --version
```
```
g++ (Ubuntu 4.8.2-19ubuntu1) 4.8.2
Copyright (C) 2013 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
If necessary, upgrade your compiler as follows:
```sh
$ sudo apt-get install g++-4.8
$ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
$ sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 50
$ sudo update-alternatives --install /usr/bin/gcov gcov /usr/bin/gcov-4.8 50
```
Next install the [build system](http://wikipedia.org/wiki/GNU_build_system) and git:
```sh
$ sudo apt-get install build-essential autoconf automake libtool pkg-config git
```
Next install the [Boost](http://www.boost.org) (minimum 1.57.0) development package:
```sh
$ sudo apt-get install libboost-all-dev
```
Next download the [install script](https://github.com/libbitcoin/libbitcoin-explorer/blob/version3/install.sh) and enable execution:
```sh
$ wget https://raw.githubusercontent.com/libbitcoin/libbitcoin-explorer/version3/install.sh
$ chmod +x install.sh
```
Finally install BX with default [build options](#build-notes-for-linux--macos):
```sh
$ sudo ./install.sh
```
Bitcoin Explorer is now installed in `/usr/local/bin` and can be invoked as `$ bx`.

### Macintosh

The macOS installation differs from Linux in the installation of the compiler and packaged dependencies. BX supports both [Homebrew](http://brew.sh) and [MacPorts](https://www.macports.org) package managers. Both require Apple's [Xcode](https://developer.apple.com/xcode) command line tools. Neither requires Xcode as the tools may be installed independently.

BX compiles with Clang on macOS and requires C++11 support. Installation has been verified using Clang based on [LLVM 3.5](http://llvm.org/releases/3.5.0/docs/ReleaseNotes.html). This version or newer should be installed as part of the Xcode command line tools.

To see your Clang/LLVM  version:
```sh
$ clang++ --version
```
You may encounter a prompt to install the Xcode command line developer tools, in which case accept the prompt.
```
Apple LLVM version 6.0 (clang-600.0.54) (based on LLVM 3.5svn)
Target: x86_64-apple-darwin14.0.0
Thread model: posix
```
If required update your version of the command line tools as follows:
```sh
$ xcode-select --install
```

#### Using Homebrew

First install [Homebrew](https://brew.sh).
```sh
$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
Next install the [build system](http://wikipedia.org/wiki/GNU_build_system) and [wget](http://www.gnu.org/software/wget):
```sh
$ brew install autoconf automake libtool pkgconfig wget
```
Next install the [Boost](http://www.boost.org) (1.57.0 or newer) development package:
```sh
$ brew install boost
```
Next download the [install script](https://github.com/libbitcoin/libbitcoin-explorer/blob/version3/install.sh) and enable execution:
```sh
$ wget https://raw.githubusercontent.com/libbitcoin/libbitcoin-explorer/version3/install.sh
$ chmod +x install.sh
```
Finally install BX with default [build options](#build-notes-for-linux--macos):
```sh
$ ./install.sh
```
Bitcoin Explorer is now installed in `/usr/local/bin` and can be invoked as `$ bx`.

##### Installing from Formula

Instead of building, Bitcoin Explorer can be installed from a formula:
```sh
$ brew install libbitcoin-explorer
```
or
```sh
$ brew install bx
```

#### Using MacPorts

First install [MacPorts](https://www.macports.org/install.php).

Next install the [build system](http://wikipedia.org/wiki/GNU_build_system) and [wget](http://www.gnu.org/software/wget):
```sh
$ sudo port install autoconf automake libtool pkgconfig wget
```
Next install the [Boost](http://www.boost.org) (1.57.0 or newer) development package. The `-` options remove MacPort defaults that are not Boost defaults:
```sh
$ sudo port install boost -no_single -no_static -python27
```
Next download the [install script](https://github.com/libbitcoin/libbitcoin-explorer/blob/version3/install.sh) and enable execution:
```sh
$ wget https://raw.githubusercontent.com/libbitcoin/libbitcoin-explorer/version3/install.sh
$ chmod +x install.sh
```
Finally install BX with default [build options](#build-notes-for-linux--macos):
```sh
$ ./install.sh
```
Bitcoin Explorer is now installed in `/usr/local/bin` and can be invoked as `$ bx`.

### Build Notes for Linux / macOS

Any set of `./configure` options can be passed via the build script, several examples follow.

Building for minimum size and with debug symbols stripped:
```sh
$ sudo ./install.sh CXXFLAGS="-Os -s"
```

> The `-s` option is not supported by the Clang compiler. Instead use the command `$ strip bs` after the build.

Building without NDEBUG (i.e. with debug assertions) defined:
```sh
$ sudo ./install.sh --disable-ndebug
```
Building without building tests:
```sh
$ sudo ./install.sh --without-tests
```
Building from a specified directory, such as `/home/me/mybuild`:
```sh
$ sudo ./install.sh --build-dir=/home/me/mybuild
```
Building into a directory other than `/usr/local`, such as `/home/me/myprefix`:
```sh
$ ./install.sh --prefix=/home/me/myprefix
```
Building and linking with a private copy of the Boost dependency:
```sh
$ ./install.sh --build-boost --prefix=/home/me/myprefix
```
Building a statically-linked executable:
```sh
$ ./install.sh --disable-shared --build-boost --prefix=/home/me/myprefix
```
Building a small statically-linked executable most quickly:
```sh
$ ./install.sh CXXFLAGS="-Os -s" --without-tests --disable-shared --build-boost --prefix=/home/me/myprefix
```
Building with bash-completion support:

> If your target system does not have it pre-installed you must first install the [bash-completion](http://bash-completion.alioth.debian.org) package. Packages are available for common package managers, including apt-get, homebrew and macports.

```sh
$ sudo ./install.sh --with-bash-completion-dir
```

#### Compiling with ICU (International Components for Unicode)

Since the addition of [BIP-39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki) and later [BIP-38](https://github.com/bitcoin/bips/blob/master/bip-0038.mediawiki) support, libbitcoin conditionally incorporates [ICU](http://site.icu-project.org). To use the BIP-38 and BIP-39 passphrase normalization features libbitcoin must be compiled with the `--with-icu` option.
```sh
$ ./install.sh --with-icu
```

#### Compiling with QR Code Support

Since the addition of [qrcode](https://github.com/evoskuil/libbitcoin/blob/master/src/wallet/qrcode.cpp) support, libbitcoin conditionally incorporates `qrencode`. This requires compiling with the `--with-qrencode` option.
```sh
$ ./install.sh --with-qrencode
```

Since the addition of [png](https://github.com/evoskuil/libbitcoin/blob/master/src/utility/png.cpp) support, libbitcoin conditionally incorporates `libpng` (which in turn requires `zlib`). This requires compiling with the `--with-png` option.
```sh
$ ./install.sh --with-png
```

> There is a bug in the PNG library when using space optimization levels such as `CXXFLAGS=-Os` which will show up in a test run failure.

#### Building ICU, ZLib, PNG, QREncode and/or Boost

The installer can download and install any or all of these dependencies. ICU is a large package that is not typically preinstalled at a sufficient level. Using these builds ensures compiler and configuration compatibility across all of the build components. It is recommended to use a prefix directory when building these components.
```sh
$ ./install.sh --with-icu --with-png --with-qrencode --build-icu --build-zlib --build-png --build-qrencode --build-boost --prefix=/home/me/myprefix
```

### Windows

Visual Studio solutions are maintained for all libbitcoin libraries and dependencies. See the [libbitcoin](https://github.com/libbitcoin/libbitcoin/blob/master/README.md#windows) repository general information about building the Visual Studio solutions. To build Libbitcoin Explorer you must also download and build its **libbitcoin dependencies**, as these are not yet packaged.

Build these solutions in order:

1. [libbitcoin/libbitcoin](https://github.com/libbitcoin/libbitcoin)
2. [libbitcoin/libbitcoin-protocol](https://github.com/libbitcoin/libbitcoin-protocol)
3. [libbitcoin/libbitcoin-client](https://github.com/libbitcoin/libbitcoin-client)
4. [libbitcoin/libbitcoin-explorer](https://github.com/libbitcoin/libbitcoin-explorer)
