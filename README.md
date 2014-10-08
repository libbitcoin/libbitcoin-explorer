[![Build Status](https://travis-ci.org/libbitcoin/libbitcoin-explorer.svg?branch=master)](https://travis-ci.org/libbitcoin/libbitcoin-explorer)

*The automated build is failing because it exceeds the current Travis time-out limit of 50 minutes.*

# Bitcoin Explorer

*The Bitcoin Command Line Tool*

**License Overview**

All files in this repository fall under the license specified in [COPYING](https://github.com/libbitcoin/libbitcoin-explorer/blob/master/COPYING). The project is licensed as [AGPL with a lesser clause](https://wiki.unsystem.net/en/index.php/Libbitcoin/License). It may be used within a proprietary project, but the core library and any changes to it must be published on-line. Source code for this library must always remain free for everybody to access.

**About Libbitcoin**

The libbitcoin toolkit is a set of cross platform C++ libraries for building bitcoin applications. The toolkit consists of several libraries, most of which depend on the foundational [libbitcoin](https://github.com/libbitcoin/libbitcoin) library. Each library's repository can be cloned and built using common [automake](http://www.gnu.org/software/automake) instructions. There are no packages yet in distribution however each library includes an installation script (described below) which is regularly verified in the automated build.

**Table of Contents**

* [Background](#background)
* [Installation](#installation)
  * [Debian/Ubuntu](#debianubuntu)
  * [Macintosh](#macintosh)
  * [Windows](#windows)
* [Design Overview](#design-overview)
  * [Single File Objective](#single-file-objective)
  * [Extensibility Model](#extensibility-model)
  * [Localization Model](#localization-model)
  * [Primitive Types](#primitive-types)
  * [Input Processing](#input-processing)
  * [Output Processing](#output-processing)
  * [Help Integration](#help-integration)
* [Test Methodology](#test-methodology)
* [Explorer Library](#explorer-library)
* [Random Numbers](#random-numbers)
* [Acronyms](#acronyms)
* [Command Taxonomy](#command-taxonomy)
* [Command Map](#command-map)
* [Command List](#command-list)

## Background

Bitcoin Explorer is a fork of the popular [SX command line tool](https://sx.dyne.org/index.html). Many of the commands and their parameters are identical to SX although many have changed, some have been obsoleted and others have been added.

Obsoleted commands include those overtaken by industry standards or by changes to other commands. Others were based on interaction with network services other than the Bitcoin peer-to-peer network or [libbitcoin-server](https://github.com/libbitcoin/libbitcoin-server), making them redundant. Others were administrative interfaces to libbitcoin\_server and it was agreed that this scenario would be better handled independently.

Because of this significant interface change and out of a desire to provide consistent naming across repositories, the repository name of this fork is **libbitcoin-explorer**. Therefore the program is called **explorer** and is referred to as **BX** as a convenience and out of respect for its ground-breaking predecessor.

## Installation

### Debian/Ubuntu

Libbitcoin requires a C++11 compiler, which means [GCC 4.7.0](https://gcc.gnu.org/projects/cxx0x.html) minimum.

> For this reason Ubuntu is not supported prior to version 12.04.

To see your GCC version:

```sh
  $ gcc --version
```

If necessary, upgrade your compiler [as follows](http://bit.ly/1vXaaQL):
```sh
  $ sudo apt-get install g++-4.8
  $ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50
  $ sudo update-alternatives --config g++
```
Next install the [build system](http://wikipedia.org/wiki/GNU_build_system):
```sh
  $ sudo apt-get install build-essential autoconf automake libtool pkg-config
```
Next install [Boost](http://www.boost.org) (1.50.0 or newer) and [GMP](https://gmplib.org) (5.0.0 or newer) development packages:
```sh
  $ sudo apt-get install libboost-all-dev libgmp-dev
```

Finally, execute the [install script](https://github.com/libbitcoin/libbitcoin-explorer/blob/master/install-bx.sh).
```sh
$ ./install-bx.sh
```
Bitcoin Explorer is now installed in `/usr/local/` and can be invoked using the `$ bx` or original `$ sx` alias.

#### Notes

If you intend to inspect and/or modify source code you should [git clone](http://git-scm.com/docs/git-clone) BX and each unpackaged dependency and build them manually. The install script itself is commented so that the manual build steps for each dependency can be inferred by a developer.

You can run the install script from any directory on your system. This will build BX in a subdirectory named `bx_build` and install it to `/usr/local/`. When the build completes successfully the `bx_build` directory is deleted.

The install script should not normally be executed using sudo. Instead it will immediately prompt you for a super user password if required. This ensures that only the necessary installation steps are executed as a super user, as opposed to the entire build process.

**The install can take well over an hour to complete.** The install script clones, builds and installs nine unpackaged repositories, namely:

* [jedisct1/libsodium](https://github.com/jedisct1/libsodium)
* [zeromq/libzmq](https://github.com/zeromq/libzmq)
* [zeromq/czmq](https://github.com/zeromq/czmq)
* [zeromq/czmqpp](https://github.com/zeromq/czmqpp)
* [bitcoin/secp256k1](https://github.com/bitcoin/secp256k1)
* [libbitcoin/libbitcoin](https://github.com/libbitcoin/libbitcoin)
* [libbitcoin/libbitcoin-client](https://github.com/libbitcoin/libbitcoin-client)
* [libbitcoin/libbitcoin-explorer](https://github.com/libbitcoin/libbitcoin-explorer)

Of these libraries, only libzmq is packaged. However we require a more recent version of the library in order to take advantage of new features such as the [SOCKS](http://wikipedia.org/wiki/SOCKS) proxy, so we build it as well.

#### Build Options

Any set of `./configure` options can be passed via the build script, for example:

```sh
  $ ./install-bx.sh CPPFLAGS=-DDEBUG CFLAGS="-Og -g"
```

#### Compiling for Testnet

Currently certain commands cannot work with both [testnet](https://en.bitcoin.it/wiki/Testnet) and mainnet. This is a libbitcoin restriction that will be lifted in a future version. In order to work with testnet in the interim the libbitcoin libraries must be recompiled with the testnet option:
```sh
  $ ./install-bx.sh --enable-testnet
```

### Macintosh

The OSX installation differs from Linux in the installation of the compiler and packaged dependencies.

To upgrade GCC first set the following environment variables:
```sh
  CC=/usr/local/bin/gcc-4.8
  CXX=/usr/local/bin/g++-4.8
```
Next execute the following commands:
```sh
  $ brew install boost gmp
  $ brew tap homebrew/versions
  $ brew install gcc48
  $ sudo ln -sf /usr/local/bin/g++-4.8 /usr/bin/g++
```
Finally, invoke the install script:
```sh
  $ ./install-bx.sh
```

### Windows

Visual Studio solutions are maintained for all libbitcoin libraries and dependencies.

> The libbitcoin execution environment supports `Windows XP Service Pack 2` and newer.

#### Upgrade Compiler

Libbitcoin requires a C++11 compiler, which means **Visual Studio 2013** minimum. Additionally a pre-release compiler must be installed as an update to Visual Studio. Download and install the following tools as necessary. Both are available free of charge:

* [Visual Studio 2013 Express](http://www.microsoft.com/en-us/download/details.aspx?id=43733)
* [November 2013 CTP Compiler](http://www.microsoft.com/en-us/download/details.aspx?id=41151)

#### Create Local NuGet Repository

Dependencies apart from the libbitcoin libraries are available as [NuGet packages](https://www.nuget.org/packages?q=evoskuil). The libbitcoin solution files are configured with references to these packages. To avoid redundancies these references expect a [NuGet.config](http://docs.nuget.org/docs/release-notes/nuget-2.1) in a central location.

> TODO: provide instructions for creation of the central NuGet repository.

The required set of NuGet packages can be viewed using the [NuGet package manager](http://docs.nuget.org/docs/start-here/managing-nuget-packages-using-the-dialog) from the BX solution. The NuGet package manager will automatically download missing packages, either from the build scripts or after prompting you in the Visual Studio environment. For your reference these are the required packages:

* Packages maintained by [sergey.shandar](http://www.nuget.org/profiles/sergey.shandar)
 * [boost](http://www.nuget.org/packages/boost)
 * [boost\_chrono-vc120](http://www.nuget.org/packages/boost_chrono-vc120)
 * [boost\_date\_time-vc120](http://www.nuget.org/packages/boost_date_time-vc120)
 * [boost\_filesystem](http://www.nuget.org/packages/boost_filesystem)
 * [boost\_filesystem-vc120](http://www.nuget.org/packages/boost_filesystem-vc120)
 * [boost\_program\_options-vc120](http://www.nuget.org/packages/boost_program_options-vc120)
 * [boost\_regex-vc120](http://www.nuget.org/packages/boost_regex-vc120)
 * [boost\_system-vc120](http://www.nuget.org/packages/boost_system-vc120)
 * [boost\_unit\_test\_framework-vc120](http://www.nuget.org/packages/boost_unit_test_framework-vc120)
* Packages maintained by [evoskuil](http://www.nuget.org/profiles/evoskuil)
 * [czmq\_vc120](http://www.nuget.org/packages/czmq_vc120)
 * [czmqpp\_vc120](http://www.nuget.org/packages/czmqpp_vc120)
 * [libgmp\_vc120](http://www.nuget.org/packages/libgmp_vc120)
 * [libsodium\_vc120](http://www.nuget.org/packages/libsodium_vc120)
 * [libzmq\_vc120](http://www.nuget.org/packages/libzmq_vc120)
 * [secp256k1\_gmp\_vc120](http://www.nuget.org/packages/secp256k1_gmp_vc120)

> The GMP for Windows project is called [MPIR](http://www.mpir.org) and has binary compatibility with GMP.

#### Build Libbitcoin Projects

To build BX you must also download and build its **libbitcoin dependencies**, as these are not yet packaged. The builds can be performed manually (from within Visual Studio) or using the `buildall.bat` script provided in the `builds\msvc\build\` subdirectory of each repository. The scripts automatically download the required NuGet packages.

> Tip: The `buildall.bat` scripts build *all* valid configurations. The build time can be significantly reduced by disabling all but the desired configuration in the `buildbase.bat` of each project.

Build these solutions in order:

1. [libbitcoin/libbitcoin](https://github.com/libbitcoin/libbitcoin)
3. [libbitcoin/libbitcoin-client](https://github.com/libbitcoin/libbitcoin-client)
4. [libbitcoin/libbitcoin-explorer](https://github.com/libbitcoin/libbitcoin-explorer)

> The libbitcoin dynamic (DLL) build configurations do not compile, as the exports have not yet been fully implemented. These are currently disabled in the build scripts but you will encounter numerous errors if you build then manually.

#### Optional: Build Everything

The non-boost packages above are all sourced from GitHub repositories maintained using the same [Visual Studio template](https://github.com/evoskuil/visual-studio-template) as the libbitcoin libraries. If so desired each of these can be built locally, in the same manner as the libbitcoin libraries above. This allows you to avoid using the pre-built NuGet packages. The repositories for each dependency are as follows:

* Zero Message Queue
 * [jedisct1/libsodium](https://github.com/jedisct1/libsodium)
 * [zeromq/libzmq](https://github.com/zeromq/libzmq)
 * [zeromq/czmq](https://github.com/zeromq/czmq)
 * [zeromq/czmqpp](https://github.com/zeromq/czmqpp)
* Bitcoin Elliptic Curve
 * [evoskuil/mpir](https://github.com/evoskuil/mpir)
 * [evoskuil/secp256k1](https://github.com/evoskuil/secp256k1)

This change is properly accomplished by disabling the "NuGet Dependencies" in the Visual Studio properties user interface for each libbitcoin project and then importing the `.import.props` file(s) for the corresponding dependencies.

> TODO: Update all libbitcoin libs with the .import.props files in a disabled configuration. This will allow this transition to be made entirely in the Visual Studio user interface. Then clarify the above explanation.

## Design Overview

### Single File Objective

The primary objective in the evolution to BX was the desire to produce a single file executable program. This presented several challenges. SX was designed primarily as an individual C++ program for each command. Additionally 14 commands were implemented in Python, as was the help system. Finally the appearance of a single program called SX was achieved by dispatching through a Python program. The single file requirement meant elimination of Python and the integration of the individual programs into one C++ program, with integrated help and dispatch.

### Extensibility Model

With approximately 75 commands and growing, BX requires an extensibility model that eliminates redundant code across commands. Ad-hoc evolution without such a model led to significant maintenance difficulty and increasing fragility. In keeping with the single file requirement the extensions had to be incorporated at compile time.

As such code generation is now used to produce headers, AutoMake files, MSVC project files, component tests, and shared source code from a single [XML metadata document](https://github.com/libbitcoin/libbitcoin-explorer/blob/master/model/generate.xml). The [open source tool GSL](https://github.com/imatix/gsl) is used to push command metadata through a [GSL template](https://github.com/libbitcoin/libbitcoin-explorer/blob/master/model/generate.gsl), producing the necessary artefacts. To implement a new command required creating an XML element, running the code generator, and overriding a single invoke method. A stub for unit/component test execution is automatically defined as well.

### Localization Model

A command line tool with interactive help and a global audience requires a model for content localization. As BX is text-based this is strictly a text conversion problem. Previously literal output and error message text was mixed with non-localizable content and interspersed throughout complex manual serialization and screen layout steps. Help text was similarly integrated into the Python dispatch code. Localization of presentation was impossible in this model.

In keeping with the single file requirement, and given the extensibility model, all localizable text was moved to the command metadata file. The remaining application level localizable content was also relocated to metadata. Within the metadata only a limited set of attributes are localizable. These can be replaced with localized messages, producing a fully-localized build. There is a small amount of work remaining to coordinate this process across a large set of languages and to allow a single build to be localized across all supported languages.

### Primitive Types

BX defines the following set of Bitcoin primitive types in the `bx::primitives` namespace.

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

These are individual classes that are for the most part simple wrappers around types and/or functions exposed by [libbitcoin](tps://github.com/libbitcoin/libbitcoin). The classes consistently implement overrides of stream operators by conversion to/from text encodings. As a result they drop seamlessly into [input processing](#input-processing) and [output processing](#output-processing) like any other serializable type.

Deserialization by any of these primitives, including string-based construction, can throw `boost::program_options::invalid_option_value`. One should consider handling this exception when using `libbitcoin-explorer` as a library.

The primitives that represent complex types also provide conversion functions to Boost [property_tree](http://www.boost.org/doc/libs/1_50_0/doc/html/property_tree.html), enabling complex textual serializations in addition to native formats. BX does not currently support complex textual deserializations apart from native formats, although that could be accomplished in part by extending the primitives with `property\_tree` deserialization.

### Input Processing

#### Command Line

BX uses source code generation and Boost's [program_options](http://www.boost.org/doc/libs/1_50_0/doc/html/program_options/overview.html) library to bind command line parameters to strongly-typed command class properties.

Command headers are generated from metadata during development. The metadata include full definition for all command parameters, including name, shortcut, data type, order, cardinality, optionality, default value, help description, file input delegation, fallback to STDIN and definition for localized messages.
```xml
<command symbol="hd-private" category="WALLET">
    <option name="help" description="Derive a child HD (BIP32) private key from another HD private key." />
    <option name="hard" shortcut="d" description="Signal to create a hardened key." />
    <option name="index" type="uint32_t" description="The HD index, defaults to zero." />
    <argument name="HD_PRIVATE_KEY" stdin="true" type="hd_private" description="The parent HD private key." />
</command>
```
Input processing is handled in shared code and generated headers. All values are available to command implementation via strongly-typed getters on the command class:
```c++
// command implementation
console_result invoke(ostream& output, ostream& error)
{
    // bound getters
    auto hard = get_hard_option();
    auto index = get_index_option();
    auto& secret = get_hd_private_key_argument();

     /* command logic omitted */

    return console_result::okay;
}
```
Corresponding setters enable library consumers to execute BX methods directly. This is the access technique used by all tests:
```c++
BOOST_AUTO_TEST_CASE(hd_private__invoke__mainnet_vector2_m_0_2147483647h_1_2147483646h__okay_output)
{
    BX_DECLARE_COMMAND(hd_private);
    // corresponding setters
    command.set_hard_option(true);
    command.set_index_option(2147483646);
    command.set_hd_private_key_argument({ "xprv9zFnWC6h2cLgpmSA46vutJzBcfJ8yaJGg8cX1..." });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("xprvA1RpRA33e1JQ7ifknakTFpgNXPmW2YvmhqLQYMmrj4xJXXWYpDPS3xz7iAx...");
}
```

#### Standard and File Input

In most commands the option is available to load the primary input parameter via [STDIN](http://wikipedia.org/wiki/Standard_streams#Standard_input_.28stdin.29). In certain cases, such as for transactions, the input value can optionally be loaded from a file by specifying the path on the command line. In such cases, when the path is missing or set to  `-`, the input will instead be read from STDIN. Multi-valued inputs are supported in file formats and STDIN by treating any [whitespace](http://en.wikipedia.org/wiki/Whitespace_character) as a separator.

#### Configuration Settings

BX uses Boost's [program_options](http://www.boost.org/doc/libs/1_50_0/doc/html/program_options/overview.html) library to bind configuration settings to strongly-typed application level properties. Settings are populated by shared code into properties generated from metadata.
```xml
<configuration section="general">
    <setting name="testnet" type="bool" default="false" description="Set to true for testnet operation..." />
</configuration>

<configuration section="server">
    <setting name="address" default="obelisk.unsystem.net:8081" description="The URI of the server..." />
    <setting name="socks-proxy" description="The host name and port number of a Socks5 proxy server." />
    <setting name="server-public-key" description="The public key of the server..." />
</configuration>
```
The implementation supports a two level hierarchy of settings using "sections" to group settings, similar to an `.ini` file:
```ini
# Example libbitcoin explorer configuration file.

[general]
testnet = true

[server]
address = tcp://85.25.198.97:10091
public-key = 573d47524678485575554e23456e334d495d667b7d583a4b576e563d70525a2428286279673d3a68
```
The path to the configuration settings file is specified by the `--config` command line option or `BX_CONFIG` environment variable. If the file is not found or a value is not specified it defaults according to metadata file values.

##### Linux/Unix/OSX

The current user's home directory, as defined by the `HOME` environment variable or by the call `getpwuid(getuid())->pw_dir`. A typical path is `/home/username`.

##### Windows

The path defined by [CSIDL_LOCAL_APPDATA](http://msdn.microsoft.com/en-us/library/windows/desktop/bb762494(v=vs.85).aspx) for the current user. A typical path is `C:\Documents and Settings\username\Local Settings\Application Data`.

Configuration settings are generated from metadata during development. The metadata includes full definition for all settings, including section, name, data type, default value and help description. If there is no configuration settings file, or if individual settings are not specified in the file, then default values are populated to bound properties.

#### Environment Variables

BX uses Boost's [program_options](http://www.boost.org/doc/libs/1_50_0/doc/html/program_options/overview.html) library to bind environment variables. All BX environment variables are prefixed with `BX_`. Currently environment variables are bound explicitly (i.e. bindings are not generated from metadata).

Currently `BX_CONFIG` is the only bound environment variable. BX uses a Boost feature to tie the environment variable and the command line option of the same identity (i.e. `--config`). The command line option takes precedence.

### Output Processing

#### Streams

Command implementations are provided with two invocation arguments, an output stream and an error stream. In BX command line processing these are populated by [STDOUT](http://wikipedia.org/wiki/Standard_streams#Standard_output_.28stdout.29) and [STDERR](http://wikipedia.org/wiki/Standard_streams#Standard_error_.28stderr.29) respectively. These values are mocked for unit testing.

#### Return Codes

Commands also return an enumerated integer value which is passed directly to the console upon command completion. The set of defined return codes is:

|value |meaning        |
|------|---------------|
|-1    |failure        |
|0     |success or true|
|1     |false          |

#### Error Stream

The error stream is intended for human consumption, it is localized and not schematized. Programmatic interpretation of the failure condition, as well as `true` vs. `false` as applicable, should rely solely on the return code. It is possible for a command to fail and not write to the error stream and for a command to write warnings to the error stream in the case of successful execution.

#### Output Stream

All commands have a default output format. Typically this is either the [Base 10](http://en.wikipedia.org/wiki/Decimal), [Base 16](ikipedia.org/wiki/Hexadecimal) or [Base 58](http://en.wikipedia.org/wiki/Base58) standard [binary-to-text](http://en.wikipedia.org/wiki/Binary-to-text_encoding) encoding.

Several commands return complex types. Some of these types have a wire serialization defined by the [Bitcoin protocol](https://en.bitcoin.it/wiki/Protocol_specification). This serialization is referred to as the **native** format.

Commands that return complex objects support serializations to **xml**, **json** and **info** as defined by Boost's [property_tree](http://www.boost.org/doc/libs/1_41_0/doc/html/boost_propertytree/parsers.html), and **native** as applicable. The default format is always **native** when applicable and otherwise **info**. 

Commands with complex outputs define the `format` option:
```xml
<command symbol="address-decode" category="WALLET">
    <option name="help" description="Convert a Bitcoin address to RIPEMD160, dropping the version." />
    <option name="format" type="encoding"
        description="The output format. Options are 'json', 'xml', 'info' or 'native', defaults to native." />
    <argument name="BITCOIN_ADDRESS" stdin="true" type="address" 
        description="The Bitcoin address to convert."/>
</command>
```
To specify a non-default format set the `--format` option on the command line:
```sh
$ bx address-decode --format info 1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E
wrapper
{
    checksum 1476364070
    payload b472a266d0bd89c13706a4132ccfb16f7c3b9fcb
    version 0
}
```
> Outputs from certain commands can be passed directly into others. However, commands that accept complex types as arguments require the **native** format.

#### Whitespace

As a matter of convention content written to either stream is terminated with the Line Feed character `0x0a`. However this presents no difficulty for input processing as [whitespace](http://en.wikipedia.org/wiki/Whitespace_character), including the Line Feed character, is ignored.

#### Cardinality

Some commands can return more than one instance of a given type. In such cases individual instances are separated by the Line Feed character `0x0a`.

### Help Integration

BX generates its help content from command metadata. The command name, description and parameterization are exposed by each command's generated class header. This allows BX to both locate a command by name and to enumerate all commands, and for each command emit the parameterization and/or description.

There is a command named `help` which lists the set of commands in alphabetical order to STDOUT. If BX is invoked without a command the `help` command is executed. These command lines are equivalent:
```sh
$ bx
$ bx help
```
Each command defines a `--help` option (which is implemented in shared code). Applied to any BX command, the help option causes BX to emit the command's help to STDOUT. Command help includes the command's description and full parameterization, including arguments and options with their descriptions and constraints. Similarly, the help command emits help for a specified command.

These command lines are equivalent:
```sh
$ bx address-decode --help
$ bx help address-decode
```
> It is somewhat idiosyncratic that in metadata the help `description` attribute defines command help content as opposed to a description of the help option. 

The help command also supports the `--help` option:
```sh
$ bx help --help
Get the list of commands.
```
An invalid command will result in a message to STDERR indicating that the command is not valid and to invoke `bx help` to see a list of commands.

Invalid parameterization on any command results in a message to STDERR indicating what parameterization is in error and that one may obtain help by using the command's `--help` option.

## Test Methodology

Testing is no substitute for good design. However desigining for testability is a forcing function for good design. For example a rigorous approach to unit testing leads directly to smaller and less conditional units and to a significant reduction in testable surface area through [elimination of repitition](http://en.wikipedia.org/wiki/Don't_repeat_yourself). These side effects of rigorous test methodology produce measurable benefits in the reduction of code complexity.

We break test scope into three distinct categories:

### Unit Test

In order for unit testing to be meaningful a unit must have defined boundaries. The term unit refers to the scope of source code under test. The smallest independently testable unit of source code is a function or method. Therefore we consider a unit test as that which isolates test failures to a single function or method under test. External libraries are considered tested and are therefore not required to be isolated.

Faking is the process of isolating a unit and is accomplished through overriding [virtual methods](http://en.wikipedia.org/wiki/Virtual_function), [dependency injection](http://en.wikipedia.org/wiki/Dependency_injection) and [mocking](http://en.wikipedia.org/wiki/Mock_object). To achieve unit isolation the code under test much achieve complete [inversion of control](http://en.wikipedia.org/wiki/Inversion_of_control) (IoC).

> BX exposes most public functionality via classes with full virtual interfaces, allowing depending libraries to utilize these techniques in the development of testable code. Some utility functions have yet to be virtualized (TODO). BX itself does not yet achieve full IoC due primarily to the lack of an [IoC container](http://www.martinfowler.com/articles/injection.html).

### Component Test

Component testing verifies the interaction between a set of units. Ideally this is a supplement to unit testing, not a substitute. If discrete functionality is called for by design then testing it in isolation is the only way to ensure the design objective has been met. Just as a unit test must isolate failures to the unit under test, a component test must isolate failures to the set of units under test.

> Component testing can be a useful iterative design tool, but is not essential to regression detection or completeness verification. These are the respective roles of unit and functional tests. As BX itself does not yet achieve full inversion of control most test coverage is achieved through component testing.

### Functional Test

Functional testing might also be called "acceptance testing". It consists of testing the application as a single unit, which precludes any isolation of units behind the public interface. In other words faking is not an aspect of functional testing. The application is tested using a harness that is applied to the interface that the end user is expected to utilize. The execution environment may be controlled to any extent, but the application may not be modified. Because of this it can be hard if not impossible to reach various code paths.

Functional testing is easier to implement than testing in isolation. There are no design constraints on the application. However functional testing is an unreliable indicator of regression. The application environment is not faked and therefore environmental changes can lead to spurious failures. For example, functional tests of network commands can and do fail due to situations beyond the control of the code under test.

> BX intends to provide a complete set of functional tests in the form of shell scripts that double as command examples and tutorials (TODO).

### Testing Objectives

#### No Test Hooks

We define a test hook as an interface to the production application that exists for the purpose of testing. Test hooks are also known as "back doors" and we avoid them as bad test and production practice. Functional testing is applied to the only/public interface. Code that is hard to reach in a functional environment (e.g. handling a network failure) should be covered in unit and, if desired, component testing.

> BX achieves this objective by not implementing test hooks. Setters exposed for each generated argument, option and setting property are currently called only in test setup, but are intended as an integral part of the public interface as it is not expected to rely on command line processing. As such these are part of the testable surface area.

#### Declarative Tests

A complex test needs to be tested. This sounds like a problem of infinite regression, but it is not. Unconditional code is not complex, and is generally verifiable through visual inspection. On the other hand, a complex test is not provably correct or necessarily able to reliably detect regression. Complexity is the direct consequence of conditionality. Each condition doubles the number of paths through a unit. Just 10 conditions produce 1024 paths. Iteration, which implies conditionality, introduces the possibility of infinite code paths. To be a test it must be declarative. Test helpers can isolate complexity but as complex code, must be tested as well.

> All BX tests are concise, declarative and visually verifiable, achieving this objective.

#### Test One Thing

Ideally a test should test only one condition. That condition should be contained in the test name so that it's clear what is being tested and so that any regression points immediately to its cause.

> BX achieves this objective in all tests with the exception that return code and stream output are tested together in each command unit test.

#### Independent Tests

All tests should be able to run concurrently and in any order. Global and static state precludes this objective and is avoided. 

> BX achieves this objective as a matter of design. Typical test runs are configured with concurrency and order randomization.

#### Code Coverage

All code paths within a library under test should be covered. In other words the library should provide 100% non-functional test coverage by line. Coverage metrics should be published from regular test execution. External libraries are presumed to be tested independently.

> BX is planning to implement automated code coverage metrics tooling as soon as it is available as a GitHub service for C++ projects. At this point we will have better visibility into actual test coverage. This objective is not yet achieved as coverage is known to be less than complete.

#### Quality Gate

All code should pass through a quality gate before being committed to the repository.

> BX achieves this objective using automated tooling integrated with GitHub. A full build with 100% successful execution of non-functional tests is required for merging code. The quality gate test doubles as the end-user installation script, which ensures that the script is verified with any published change.

## Explorer Library

The `libbitcoin-explorer` build produces static and dynamic libraries that implement all of the functionality of the `explorer` executable. Tests are implemented in a distinct executable called `explorer_test` which also links `libbitcoin-explorer`. The symbolic link `bx` is configured as an alias for `explorer`.

Command parameterization is isolated so that each command unit test bypasses command line and [STDIO](http://wikipedia.org/wiki/Standard_streams) processing. This design also ensures that `libbitcoin-explorer` remains useful as a library for building other applications.

In other words another application can link to `libbitcoin-explorer` and immediately take advantage of the full set of tested commands, as simple methods with no relation to the command line or STDIO. Such applications can even avoid a dependency on Boost program\_options and `libbitcoin-explorer` code that performs I/O processing.

Using the library requires inclusion of the header `<explorer/explorer.hpp>` and a reference to the `libbitcoin-explorer` library and its dependencies. BX exposes common functionality in the following namespaces:
```c++
bc::explorer::commands
bc::explorer::primitives
```
## Random Numbers

In SX it was common for a command to invoke an internal [Pseudo Random Number Generator](http://wikipedia.org/wiki/Pseudorandom_number_generator). As a weak random number generator can introduce cryptographic weakness this technique has been obsoleted. Any BX command that requires a random number obtains that value as an argument. This places the responsibility of ensuring random number strength on the end-user and also helps them understand the potential for problems.

The "seed" command is provided as a convenience, and is the only command that generates randomness. The `seed` command accepts a bit length argument, and has default and minimum value of 128.
```sh
$ bx seed 256
e4d28a5972ce0785477f39f58e424c5ef643b26894c50f8e024601f87736b8fe 
```
Seed output can be passed as an argument to any command that require randomness.
## Acronyms

BX command names, help and parameterization utilize the following set of acronyms.

    BTC     Bitcoin Denomination
    BX      Bitcoin Explorer
    EC      Elliptic Curve
    HD      Hierarchical Deterministic
    PUBKEY  EC Public Key
    QRCODE  Quick Response Code
    RACE    Research and development in Advanced Communications Technologies
    RIPEMD  RACE Integrity Primitives Evaluation Message Digest
    SHA     Secure Hash Algorithm
    SOCKS   Socket Secure (proxy protocol)
    SX      Spesmilo Exchanger (the original version of Bitcoin Explorer)
    TX      Transaction
    UTXO    Unspent Transaction Output
    WIF     Wallet Import Format

### Command Taxonomy

Commands are named with several objectives in mind. Congruence with the [SX command set](https://sx.dyne.org/quickstart.html) and brevity are important considerations, but in many cases these have taken a back seat to internal consistency and transparency.

#### Networking

Commands are generally names so that related commands sort together. In the case of network commands (`fetch-`, `send-`, `validate-` and `watch-`) the command's action (verb) starts the name. In other commands (e.g. `tx-`, `address-`) the primary data type (noun) starts the name. This distinction is primarily based on the congruence objective and also tends to read more naturally.

#### Conversion

Commands that convert from one data type to another (excluding base encoding) are named using the "input-to-output" nomenclature. In certain cases the second data type is implied and the `-encode`/ `-decode` suffixes are used instead. This distinction is a nod to the congruence objective.

#### Hashing

Commands that hash data are named only with the type of hash. In these cases the data type of both the input and the output data type is Base16. As is the nature of hashing, these operations are not reversible and are therefore singletons.

#### Stealth

Commands pertaining to stealth addresses are prefixed with `stealth-` to differentiate them from bitcoin address commands.

#### Validation

Commands preixed or suffixed with `validate` have a third result code state: **invalid** (1). This is in addition to success / **valid** (0) and **failure** (-1), which may be returned by any command.

#### Other

Commands suffixed with `-new` create a new instance of whatever type is specified in the command. Other command actions (e.g. `-set`, `-sign`, `-add`, `-multiply`, `-uncover`) are unique to the contexts in which they are defined.

## Command Map

The following diagrams show the full set of commands, input/output data types and relationships. Commands are grouped according to metadata categorization.

##### Wallet Commands
```
Commands pertaining to bitcoin keys and payment addresses.
```
<img src="/img/wallet-commands.png" width="30%" height="30%"></img>

##### Stealth Commands
```
Commands pertaining to stealth payments and addresses.
```
<img src="/img/stealth-commands.png" width="30%" height="30%"></img>

##### Transaction Commands
```
Commands pertaining to manipulation of transactions, excluding network calls.
```
<img src="/img/transaction-commands.png" width="30%" height="30%"></img>

##### Online Commands
```
Commands that communicate on the bitcoin network.
```
<img src="/img/online-commands.png" width="30%" height="30%"></img>

##### Hash Commands
```
Commands pertaining to hashing and encoding data in the various bitcoin formats.
```
<img src="/img/hash-commands.png" width="30%" height="30%"></img>

##### Math Commands
```
Coin conversion and commands that perform secp256k1 elliptic curve math.
```
<img src="/img/math-commands.png" width="25%" height="25%"></img>

## Command List

BX defines the following set of commands with corresponding names in the `bx::commands` namespace.

    address-decode
    address-embed
    address-encode
    address-validate
    base16-decode
    base16-encode    
    base58-decode
    base58-encode
    base58check-decode
    base58check-encode
    bitcoin160
    bitcoin256
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
    fetch-header
    fetch-height
    fetch-history
    fetch-public-key
    fetch-stealth
    fetch-tx
    fetch-tx-index
    fetch-utxo
    hd-new
    hd-private
    hd-public
    hd-to-address
    hd-to-ec
    hd-to-public
    hd-to-wif
    help
    input-set
    input-sign
    input-validate
    mnemonic-decode
    mnemonic-encode
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
    sha160
    sha256
    sha512
    stealth-address-decode
    stealth-address-encode
    stealth-new
    stealth-shared-secret
    stealth-uncover-public
    stealth-uncover-secret
    tx-decode
    tx-encode
    tx-sign
    validate-tx
    watch-address
    watch-tx
    wif-to-ec
    wif-to-public
    wrap-decode
    wrap-encode
