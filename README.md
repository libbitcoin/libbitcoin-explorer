[![Build Status](https://travis-ci.org/libbitcoin/libbitcoin_explorer.svg?branch=master)](https://travis-ci.org/libbitcoin/libbitcoin_explorer)
# Bitcoin Explorer

Bitcoin at the command line

All files in this repository fall under the license specified in [COPYING](https://github.com/libbitcoin/libbitcoin_explorer/blob/master/COPYING). The project is licensed as [AGPL with a lesser clause](https://wiki.unsystem.net/en/index.php/Libbitcoin/License). It may be used within a proprietary project, but the core library and any changes to it must be published online. Source code for this library must always remain free for everybody to access.

# Automated Build Status

The automated build is failing because it exceeds the Travis timeout limit of 50 minutes. There is not much we can do to shorten the build time while maintaining reliability. We are looking into isolating the ZMQ test compilation from the build, but this will be insufficient to complete the build. Travis has indicated to us that a change to this limit is on their roadmap.

# Debian/Ubuntu Instructions

Your system may require updating before installing. Bitcoin Explorer requires a C++11 compiler, **GCC 4.7.0** minimum. For this reason **Ubuntu is not supported prior to version 12.04** .

To see your compiler version:

$ gcc --version

To install and register **GCC 4.8** :

$ sudo apt-get install g++-4.8  
$ sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-4.8 50

**GMP, LibConfig++** and **Boost** are also required:

$ sudo apt-get install libgmp-dev libconfig++-dev libboost-all-dev

Next execute the [**build script**](https://raw.githubusercontent.com/libbitcoin/libbitcoin_explorer/develop/build.sh) **:**

$ ./build.sh

This will build and install Bitcoin Explorer in a new subdirectory named BUILD. You may run the script from any location on your system. It should not normally be executed using sudo. It will immediately prompt you for a super user password if required. This ensures that only the necessary installation steps are executed as a super user, as opposed to the entire build process. If you are missing dependencies the build will terminate and you will be shown what is missing.

**The build can take well over an hour to complete.** In addition to the packaged dependencies above, the build script clones, builds and installs nine repositories, namely:

- jedisct1/libsodium
- zeromq/libzmq
- zeromq/czmq
- zeromq/czmqpp
- bitcoin/secp256k1
- libbitcoin/libbitcoin
- libbitcoin/libwallet
- libbitcoin/obelisk
- libbitcoin/libbitcoin\_explore

Of these libraries only libzmq is packaged, however we require a more recent version of the library in order to take advantage of new features (e.g. SOCKS5).

# Background

**Bitcoin Explorer is a fork of the popular SX command line utility.** Many of the commands and their parameters are identical to SX although many have changed, some have been obsoleted and others have been added.

Obsoleted commands include those overtaken by industry standards or by changes to other commands. Others were based on interaction with network services other than the Bitcoin peer-to-peer network or libbitcoin\_server (Obelisk), making them redundant. Others were administrative interfaces to libbitcoin\_server and it was agreed that this scenario would be better handled independently.

Because of this significant interface change and out of a desire to provide consistent naming across repositories, the repository name in this fork is **libbitcoin\_explorer** . Therefore the program is called **explorer** and is referred to as **BX** as a convenience and out of respect for its groundbreaking predecessor.

# Design Objectives

## Single File Command Line Tool

The primary objective in the evolution to BX was the desire to produce a single file executable program. This presented several challenges. SX was designed primarily as an individual C++ program for each command. Additionally 14 commands were implemented in Python, as was the help system. Finally the appearance of a single program called SX was achieved by dispatching through a Python program. The single file requirement meant elimination of Python and the integration of the individual programs into one C++ program, with integrated help and dispatch.

## Extensibility Model

At over 72 commands (85 including obsoleted stubs) and growing Explorer requires an extensibility model that eliminates redundant code across commands. Ad-hoc evolution without such a model led to significant maintenance difficulty and increasing fragility. In keeping with the single file requirement the extensibility model had to be compile time.

As such code generation is now used to produce headers, AutoMake files, MSVC project files, component tests, and shared source code from a single [XML metadata document](https://github.com/libbitcoin/libbitcoin_explorer/blob/master/model/generate.xml). The [open source tool GSL](https://github.com/imatix/gsl) is used to push command metadata through a [GSL template](https://github.com/libbitcoin/libbitcoin_explorer/blob/master/model/generate.gsl), producing the necessary artifacts. To implement a new command required creating an XML element, running the code generator, and overriding a single invoke method. A stub for unit/component test execution is automatically defined as well.

## Localization Model

A command line tool with interactive help and a global audience requires a model for content localization. As BX is text-based this is strictly a text conversion problem. Previously literal output and error message text was mixed with non-localizable content and interspersed throughout complex manual serialization and screen layout steps. Help text was similarly integrated into the Python dispatch code. Localization of presentation was impossible in this model.

In keeping with the single file requirement, and given the extensibility model, all localizable text was moved to the command metadata file. The remaining application level localizable content was also relocated to metadata. Within the metadata only a limited set of attributes are localizable. These can be replaced with localized messages, producing a fully-localized build. There is a small amount of work remaining to coordinate this process across a large set of languages and to allow a single build to be localized across all supported languages.

## Command Taxonomy

Commands are named with several objectives in mind. Congruence with the SX command set and brevity are important considerations, but in many cases these have taken a back seat to internal consistency and transparency.

### Local vs. Network

Commands are generally names so that related commands sort together. In the case of network commands (fetch, send, and watch) the command's action (verb) starts the name. In other commands the primary data type (noun) starts the name. This distinction is primarily based on the congruence objective but also tends to read more naturally.

### Type Conversion

Commands that convert from one data type to another (excluding base encoding) are named using the "input-to-output" format. In certain cases the second data type is implied and the encode/decode suffix is used instead. This distinction is a nod to congruence.

### Data Hashing

Commands that hash data are named only with the type of hash. In these cases the data type of both the input and the output data type is Base16. As is the nature of hashing, these operations are not reversible and are therefore singletons.

### Stealth

Commands pertaining to stealth addresses are prefixed with "stealth" to differentiate them from bitcoin address commands.

### Validate

Commands suffixed with "validate" have a third result code state: **invalid** (1). This is in addition to success/ **valid** (0) and **failure** (-1), which may be returned by any command.

### New

Commands suffixed with "new" create a new instance of whatever type is specified in the command.

### Custom Actions

Other command actions, such as "set", "sign", "add", "multiply", and "uncover" are unique to the respective context in which they are defined.

## Input Processing

### Command Line

SX used and-hoc command line parsing to obtain named (option) and positional (argument) parameters. This manual inline parsing across such a large body of code created complexity and fragility, as well as inconsistency in parameter treatment. BX has resolved these issues by relying on code generation and Boost's program options to process all command line parameterization.

Command headers are generated from metadata during development. The metadata includes full definition for all command inputs, including parameter names, ordering, cardinality, data types, optionality, default values and detailed description. Additionally the same constrained parameters can require or fall back to STDIN, and file input.

Input processing is handled in shared code and generated headers. All input values are delivered to command implementation via strongly-typed getters on the command class. Corresponding setters enable library consumers to execute BX methods directly. This is the access technique used by all tests.

### Configuration Settings

SX used LibConfig++ to parse a configuration file so that configuration state could be persisted. BX uses Boost's program options to bind configuration settings to application level parameters in a manner nearly identical to that of command line processing. Configuration settings are defined in metadata bindings are emitted into generated code.

BX binds the BX\_CONFIG environment variable and the --config command line option to the configuration settings file path. Boost processes both values and uses the resulting path to locate the settings file. In the case where neither of these values is set the file is loaded from a default path and name. If no file is located default values generated from metadata are automatically bound.

### Standard and File Input

In most commands the option is available to load the primary input parameter via STDIN. In certain cases, such as for transactions, the input value can optionally be loaded from a file by specifying the path, and when the path is missing (or "-") the input will fall back to STDIN. Multi-valued inputs are supported in file or STDIN by treating using any whitespace as a separator.

## Output Processing

[Command line, STDIN, STDOUT, files, multiples, native/info/XML/JSON, asymmetry]

## Primitives

[24 primitive wrappers]

## Help Integration

[All handled in the application framework, help command, no command, command help options]

## Error Handling

[Messages, return codes, deserialization exceptions, command line]

## Seeding

In SX it was common for a command to call upon an internal [PRNG](http://en.wikipedia.org/wiki/Pseudorandom_number_generator). As a weak random number generator can introduce cryptographic weakness this technique has been obsoleted. Any BX command that requires a random number obtains that value as an argument. This places the responsibility of ensuring random number strength on the end-user and also helps them understand the potential for problems.

The "seed" command is provided as a convenience as the only command that generates randomness. Seed accepts a seed length argument, in number of bits and the default/minimum bit length is 128. The seed result can be passed as an argument to other commands that require randomness.

## Use as a Library

[Text-based library as demonstrated by test cases, examples for all]

## Test Methodology

[Unit, component, functional, virtual, naming/individual, continuous against install script]