[![Build Status](https://travis-ci.org/libbitcoin/libbitcoin_explorer.svg?branch=master)](https://travis-ci.org/libbitcoin/libbitcoin_explorer)

*The automated build is failing because it exceeds the current Travis timeout limit of 50 minutes.*

# Bitcoin Explorer

*The Bitcoin Command Line Tool*

<!--<img src="/img/wallet-commands.png" width="75%" height="75%"></img>-->

**License Overview**

All files in this repository fall under the license specified in [COPYING](https://github.com/libbitcoin/libbitcoin_explorer/blob/master/COPYING). The project is licensed as [AGPL with a lesser clause](https://wiki.unsystem.net/en/index.php/Libbitcoin/License). It may be used within a proprietary project, but the core library and any changes to it must be published online. Source code for this library must always remain free for everybody to access.

**Table of Contents**

* [Background](#background)
* [Installation](#installation)
  * [Debian/Ubuntu](#debianubuntu)
  * [Macintosh](#macintosh)
  * [Windows](#windows)
* [Design Overview](#design-overview)
  * [Single File Command Line Tool](#single-file-command-line-tool)
  * [Extensibility Model](#extensibility-model)
  * [Localization Model](#localization-model)
  * [Command Taxonomy](#command-taxonomy)
  * [Input Processing](#input-processing)
  * [Output Processing](#output-processing)
  * [Primitives](#primitives)
  * [Help Integration](#help-integration)
  * [Seeding](#seeding)
  * [Use as a Library](#use-as-a-library)
  * [Test Methodology](#test-methodology)
* [Command List](#command-list)

## Background

Bitcoin Explorer is a fork of the popular [SX command line tool](https://sx.dyne.org/index.html). Many of the commands and their parameters are identical to SX although many have changed, some have been obsoleted and others have been added.

Obsoleted commands include those overtaken by industry standards or by changes to other commands. Others were based on interaction with network services other than the Bitcoin peer-to-peer network or libbitcoin\_server (Obelisk), making them redundant. Others were administrative interfaces to libbitcoin\_server and it was agreed that this scenario would be better handled independently.

Because of this significant interface change and out of a desire to provide consistent naming across repositories, the repository name in this fork is **libbitcoin\_explorer**. Therefore the program is called **explorer** and is referred to as **BX** as a convenience and out of respect for its groundbreaking predecessor.

## Installation

### Debian/Ubuntu

Libbitcoin requires a modern C++ compiler, **GCC 4.7.0** minimum. For this reason **Ubuntu is not supported prior to version 12.04**. To see your compiler version:
```
  $ gcc --version
```
If necessary, upgrade your compiler [as follows](http://bit.ly/1vXaaQL):
```
  $ sudo apt-get install g++-4.8
  $ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
  $ sudo update-alternatives --config g++
```
Next install the [build system](http://en.wikipedia.org/wiki/GNU_build_system):
```
  $ sudo apt-get install build-essential autoconf automake libtool pkg-config
```
Next install [Boost](http://www.boost.org) (1.50.0 or newer), [GMP](https://gmplib.org) (5.0.0 or newer), and [LibConfig++](http://www.hyperrealm.com/libconfig) (1.3.2 or newer) development packages:
```
  $ sudo apt-get install libboost-all-dev libgmp-dev libconfig++-dev
```
Next execute the [build script](https://raw.githubusercontent.com/libbitcoin/libbitcoin_explorer/develop/build.sh).
```
$ ./build.sh
```
Bitcoin Explorer is now installed in `/usr/local/` and can be invoked using the `$ bx` (or `$ sx`) alias.

#### Notes

You can run the script from any directory on your system. This will build and install Bitcoin Explorer in a new subdirectory named BUILD. If you are missing dependencies the build will terminate and you will be shown what is missing.

It should not normally be executed using sudo. It will immediately prompt you for a super user password if required. This ensures that only the necessary installation steps are executed as a super user, as opposed to the entire build process.

**The build can take well over an hour to complete.** In addition to the packaged dependencies above, the build script clones, builds and installs nine repositories, namely:

- [jedisct1/libsodium](https://github.com/jedisct1/libsodium)
- [zeromq/libzmq](https://github.com/zeromq/libzmq)
- [zeromq/czmq](https://github.com/zeromq/czmq)
- [zeromq/czmqpp](https://github.com/zeromq/czmqpp)
- [bitcoin/secp256k1](https://github.com/bitcoin/secp256k1)
- [libbitcoin/libbitcoin](https://github.com/libbitcoin/libbitcoin)
- [libbitcoin/libwallet](https://github.com/libbitcoin/libwallet)
- [libbitcoin/obelisk](https://github.com/libbitcoin/obelisk)
- [libbitcoin/libbitcoin_explorer](https://github.com/libbitcoin/libbitcoin_explorer)

Of these libraries, only libzmq is packaged. However we require a more recent version of the library in order to take advantage of new features (e.g. SOCKS5).

#### Build Options

Any set of `./configure` options can be passed via the build script, for example:

```
  $ ./build.sh CPPFLAGS=-DDEBUG CFLAGS="-Og -g"
```

#### Compiling for Testnet

Currently certain commands cannot work with both the **Test Network** (testnet) and mainnet. This is a libbitcoin that restriction will be lifted in a future version. In order to work with testnet in the interim the libraries must be recompiled with the testnet option.:
```
  $ ./build.sh --enable-testnet
```

### Macintosh

The OSX installation differs from Linux in the installation of the compiler and packaged dependencies.

To upgrade GCC first set the folloing environment variables:
```
  CC=/usr/local/bin/gcc-4.8
  CXX=/usr/local/bin/g++-4.8
```
Next execute the following commands:
```
  $ brew install boost gmp libconfig
  $ brew tap homebrew/versions
  $ brew install gcc48
  $ sudo ln -sf /usr/local/bin/g++-4.8 /usr/bin/g++
```
Finally, invoke the installation script:
```
  $ ./build.sh
```

### Windows

Visual Studio solutions are provided for all libbitcoin libraries and dependencies. Because libbitcoin requires a `C++11` compiler, **Visual Studio 2013** is the most recent supported version and requires a modified pre-release compiler.

* [Visual Studio 2013 Express](http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx) is available for [download](http://www.microsoft.com/en-us/download/details.aspx?id=40787) and is free of charge.
* The [November 2013 CTP Compiler](http://blogs.msdn.com/b/vcblog/archive/2013/11/18/announcing-the-visual-c-compiler-november-2013-ctp.aspx) must be [downloaded](http://www.microsoft.com/en-us/download/details.aspx?id=41151) and installed as well.

Dependencies apart from the libbitcoin repos are [available on NuGet](https://www.nuget.org/packages?q=evoskuil). Eventually the libbitcoin libraries and tools will be published as well. The solution files are already configured with references to the NuGet packages and expect a [central NuGet repo](http://docs.nuget.org/docs/release-notes/nuget-2.1). You should be able to restore the packages to the repo once it is properly configured.

Once the dependencies have been downloaded select a **statically-linked build** and build the solution. **The non-static (DLL) build configurations do not compile, as the exports have not yet been completed.**

## Design Overview

### Single File Command Line Tool

The primary objective in the evolution to BX was the desire to produce a single file executable program. This presented several challenges. SX was designed primarily as an individual C++ program for each command. Additionally 14 commands were implemented in Python, as was the help system. Finally the appearance of a single program called SX was achieved by dispatching through a Python program. The single file requirement meant elimination of Python and the integration of the individual programs into one C++ program, with integrated help and dispatch.

### Extensibility Model

With over 70 commands (85 including obsoleted stubs) and growing, Explorer requires an extensibility model that eliminates redundant code across commands. Ad-hoc evolution without such a model led to significant maintenance difficulty and increasing fragility. In keeping with the single file requirement the extensions had to be incorporated at compile time.

As such code generation is now used to produce headers, AutoMake files, MSVC project files, component tests, and shared source code from a single [XML metadata document](https://github.com/libbitcoin/libbitcoin_explorer/blob/master/model/generate.xml). The [open source tool GSL](https://github.com/imatix/gsl) is used to push command metadata through a [GSL template](https://github.com/libbitcoin/libbitcoin_explorer/blob/master/model/generate.gsl), producing the necessary artifacts. To implement a new command required creating an XML element, running the code generator, and overriding a single invoke method. A stub for unit/component test execution is automatically defined as well.

### Localization Model

A command line tool with interactive help and a global audience requires a model for content localization. As BX is text-based this is strictly a text conversion problem. Previously literal output and error message text was mixed with non-localizable content and interspersed throughout complex manual serialization and screen layout steps. Help text was similarly integrated into the Python dispatch code. Localization of presentation was impossible in this model.

In keeping with the single file requirement, and given the extensibility model, all localizable text was moved to the command metadata file. The remaining application level localizable content was also relocated to metadata. Within the metadata only a limited set of attributes are localizable. These can be replaced with localized messages, producing a fully-localized build. There is a small amount of work remaining to coordinate this process across a large set of languages and to allow a single build to be localized across all supported languages.

### Command Taxonomy

Commands are named with several objectives in mind. Congruence with the SX command set and brevity are important considerations, but in many cases these have taken a back seat to internal consistency and transparency.

#### Local vs. Network

Commands are generally names so that related commands sort together. In the case of network commands (`fetch-`, `send-`, and `watch-`) the command's action (verb) starts the name. In other commands (e.g. `tx-`, `address-`) the primary data type (noun) starts the name. This distinction is primarily based on the congruence objective but also tends to read more naturally.

#### Type Conversion

Commands that convert from one data type to another (excluding base encoding) are named using the "input-to-output" format. In certain cases the second data type is implied and the encode/decode suffix is used instead. This distinction is a nod to SX congruence.

#### Data Hashing

Commands that hash data are named only with the type of hash. In these cases the data type of both the input and the output data type is Base16. As is the nature of hashing, these operations are not reversible and are therefore singletons.

#### Stealth

Commands pertaining to stealth addresses are prefixed with `stealth-` to differentiate them from bitcoin address commands.

#### Validate

Commands suffixed with `-validate` have a third result code state: **invalid** (1). This is in addition to success / **valid** (0) and **failure** (-1), which may be returned by any command.

#### New

Commands suffixed with `-new` create a new instance of whatever type is specified in the command.

#### Custom Actions

Other command actions (e.g. `-set`, `-sign`, `-add`, `-multiply`, `-uncover`) are unique to the contexts in which they are defined.

### Input Processing

#### Command Line

SX used and-hoc command line parsing to obtain named (option) and positional (argument) parameters. This manual inline parsing across such a large body of code created complexity and fragility, as well as inconsistency in parameter treatment. BX has resolved these issues by relying on code generation and Boost's program options to process all command line parameterization.

Command headers are generated from metadata during development. The metadata includes full definition for all command inputs, including parameter names, ordering, cardinality, data types, optionality, default values and detailed description. Additionally the same constrained parameters can require or fall back to STDIN, and file input.

Input processing is handled in shared code and generated headers. All input values are delivered to command implementation via strongly-typed getters on the command class. Corresponding setters enable library consumers to execute BX methods directly. This is the access technique used by all tests.

#### Configuration Settings

SX used LibConfig++ to parse a configuration file so that configuration state could be persisted. BX uses Boost's program options to bind configuration settings to application level parameters in a manner nearly identical to that of command line processing. Configuration settings are defined in metadata bindings are emitted into generated code.

BX binds the BX\_CONFIG environment variable and the --config command line option to the configuration settings file path. Boost processes both values and uses the resulting path to locate the settings file. In the case where neither of these values is set the file is loaded from a default path and name. If no file is located default values generated from metadata are automatically bound.

#### Standard and File Input

In most commands the option is available to load the primary input parameter via [STDIN](http://en.wikipedia.org/wiki/Standard_streams#Standard_input_.28stdin.29). In certain cases, such as for transactions, the input value can optionally be loaded from a file by specifying the path, and when the path is missing or set to  `-` the input will fall back to STDIN. Multi-valued inputs are supported in file or STDIN by treating any whitespace as a separator.

### Output Processing

[Command line, [STDERR](http://en.wikipedia.org/wiki/Standard_streams#Standard_error_.28stderr.29), [STDOUT](http://en.wikipedia.org/wiki/Standard_streams#Standard_output_.28stdout.29), files, multiples, native/info/XML/JSON, asymmetry]

[Error Messages, return codes, deserialization exceptions, command line]

### Primitives

    address
    base16
    base58
    btc
    btc160
    btc256
    ec_private
    ec_public
    encoding
    hashtype
    hd_key
    hd_priv
    hd_pub
    header
    input
    output
    point
    prefix
    raw
    script
    stealth
    transaction
    wif
    wrapper

### Help Integration

[All handled in the application framework, help command, no command, command help options]

### Seeding

In SX it was common for a command to call upon an internal [PRNG](http://en.wikipedia.org/wiki/Pseudorandom_number_generator). As a weak random number generator can introduce cryptographic weakness this technique has been obsoleted. Any BX command that requires a random number obtains that value as an argument. This places the responsibility of ensuring random number strength on the end-user and also helps them understand the potential for problems.

The "seed" command is provided as a convenience as the only command that generates randomness. Seed accepts a seed length argument, in number of bits and the default/minimum bit length is 128. The seed result can be passed as an argument to other commands that require randomness.

### Use as a Library

[Text-based library as demonstrated by test cases, examples for all]

### Test Methodology

[Unit, component, functional, virtual, naming/individual, continuous against install script]

## Command List

    address-decode
    address-embed
    address-encode
    address-validate
    base58-decode
    base58-encode
    base58check-decode
    base58check-encode
    bci-fetch-last-height
    bci-history
    bitcoin160
    bitcoin256
    blke-fetch-transaction
    btc-to-satoshi
    ec-add
    ec-add-secrets
    ec-lock
    ec-multiply
    ec-multiply-secrets
    ec-new
    ec-to-address
    ec-to-public
    ec-to-wif
    ec-unlock
    fetch-balance
    fetch-confirmations
    fetch-header
    fetch-height
    fetch-history
    fetch-public-key
    fetch-stealth
    fetch-tx
    fetch-tx-index
    fetch-utxo
    genaddr
    genpriv
    genpub
    hd-new
    hd-private
    hd-public
    hd-to-address
    hd-to-ec
    hd-to-public
    hd-to-wif
    help
    initchain
    input-set
    input-sign
    input-validate
    mnemonic-decode
    mnemonic-encode
    mpk
    newseed
    qrcode
    ripemd160
    satoshi-to-btc
    script-decode
    script-encode
    script-to-address
    seed
    send-tx
    send-tx-node
    send-tx-p2p
    sendtx-bci
    sha160
    sha256
    sha512
    showblkhead
    stealth-address-decode
    stealth-address-encode
    stealth-new
    stealth-newkey
    stealth-shared-secret
    stealth-uncover-public
    stealth-uncover-secret
    tx-decode
    tx-encode
    tx-sign
    wallet
    watch-stealth
    watch-tx
    wif-to-ec
    wif-to-public
    wrap-decode
    wrap-encode.cpp
