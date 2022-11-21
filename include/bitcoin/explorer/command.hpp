/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_COMMAND_HPP
#define BX_COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/address.hpp>
#include <bitcoin/explorer/config/algorithm.hpp>
#include <bitcoin/explorer/config/btc.hpp>
#include <bitcoin/explorer/config/byte.hpp>
#include <bitcoin/explorer/config/bytes.hpp>
#include <bitcoin/explorer/config/electrum.hpp>
#include <bitcoin/explorer/config/encoding.hpp>
#include <bitcoin/explorer/config/endorsement.hpp>
#include <bitcoin/explorer/config/hd_key.hpp>
#include <bitcoin/explorer/config/language.hpp>
#include <bitcoin/explorer/config/sighash.hpp>
#include <bitcoin/explorer/config/signature.hpp>
#include <bitcoin/explorer/config/witness.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>
#include <bitcoin/protocol/zmq/sodium.hpp>
#include <bitcoin/explorer/utility.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

namespace libbitcoin {
namespace explorer {

#define BX_PROGRAM_NAME "bx"
#define BX_HELP_VARIABLE "help"
#define BX_CONFIG_VARIABLE "config"
BC_DECLARE_CONFIG_DEFAULT_PATH("libbitcoin" / BX_PROGRAM_NAME ".cfg")

/**
 * Base class for definition of each Bitcoin Explorer command.
 */
class BCX_API command
{
public:

    /**
     * The symbolic (not localizable) command name, lower case.
     */
    static const char* symbol()
    {
        return "not-implemented";
    }

    /**
     * Destructor.
     */
    virtual ~command()
    {
    }

    /**
     * The symbolic (not localizable) command name, lower case.
     * @return  Example: "fetch-transaction"
     */
    virtual const char* name()
    {
        return symbol();
    }

    /**
     * The localizable command category name, upper case.
     * @return  Example: "ONLINE"
     */
    virtual const char* category()
    {
        return "not-implemented";
    }

    /**
     * The localizable command description.
     * @return  Example: "Get transactions by hash."
     */
    virtual const char* description()
    {
        return "not-implemented";
    }

    /**
     * Declare whether the command has been obsoleted.
     * @return  True if the command is obsolete
     */
    virtual bool obsolete()
    {
        return false;
    }

    /**
     * Determines if STDIN is required to be raw.
     * @return  True if the type of the STDIN argument is primitive::raw.
     */
    virtual bool requires_raw_input()
    {
        return false;
    }

    /**
     * Determines if STDOUT is required to be raw.
     * @return  True if the type of the STDOUT argument is primitive::raw.
     */
    virtual bool requires_raw_output()
    {
        return false;
    }

    /**
     * Invoke the command.
     * @param[out]  output  The input stream for the command execution.
     * @param[out]  error   The input stream for the command execution.
     * @return              The appropriate console return code { -1, 0, 1 }.
     */
    virtual system::console_result invoke(std::ostream& output,
        std::ostream& error)
    {
        return system::console_result::failure;
    }

    /**
     * Load command argument definitions.
     * A value of -1 indicates that the number of instances is unlimited.
     * @return  The loaded argument definitions.
     */
    virtual system::arguments_metadata& load_arguments()
    {
        return argument_metadata_;
    }

    /**
     * Load environment variable definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_environment(system::options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        (
            /* This composes with the command line options. */
            BX_CONFIG_VARIABLE,
            value<boost::filesystem::path>()
                ->composing()->default_value(config_default_path()),
            "The path to the configuration settings file."
        );
    }

    /**
     * Load parameter fallbacks from file or input as appropriate.
     * @param[in]  input      The input stream for loading the parameters.
     * @param[in]  variables  The loaded variables.
     */
    BCX_API virtual void load_fallbacks(std::istream& input,
        po::variables_map& variables)
    {
    }

    /**
     * Load command option definitions.
     * BUGBUG: see boost bug/fix: svn.boost.org/trac/boost/ticket/8009
     * @return  The loaded option definitions.
     */
    virtual system::options_metadata& load_options()
    {
        return option_metadata_;
    }

    /**
     * Load configuration setting definitions.
     * @param[out] definitions  The defined program argument definitions.
     */
    virtual void load_settings(system::options_metadata& definitions)
    {
        using namespace po;
        definitions.add_options()
        (
            "wallet.witness_version",
            value<explorer::config::byte>(&setting_.wallet.witness_version),
            "The witness version, defaults to 0."
        )
        (
            "wallet.witness_address_prefix",
            value<std::string>(&setting_.wallet.witness_address_prefix)->default_value("bc"),
            "The witness address prefix, defaults to 'bc'."
        )
        (
            "wallet.wif_version",
            value<explorer::config::byte>(&setting_.wallet.wif_version)->default_value(128),
            "The wallet import format (WIF) key version, defaults to 128."
        )
        (
            "wallet.hd_public_version",
            value<uint32_t>(&setting_.wallet.hd_public_version)->default_value(76067358),
            "The hierarchical deterministic (HD) public key version, defaults to 76067358."
        )
        (
            "wallet.hd_secret_version",
            value<uint32_t>(&setting_.wallet.hd_secret_version)->default_value(76066276),
            "The hierarchical deterministic (HD) private key version, defaults to 76066276."
        )
        (
            "wallet.pay_to_public_key_hash_version",
            value<explorer::config::byte>(&setting_.wallet.pay_to_public_key_hash_version)->default_value(0),
            "The pay-to-public-key-hash address version, defaults to 0."
        )
        (
            "wallet.pay_to_script_hash_version",
            value<explorer::config::byte>(&setting_.wallet.pay_to_script_hash_version)->default_value(5),
            "The pay-to-script-hash address version, defaults to 5."
        )
        (
            "wallet.transaction_version",
            value<uint32_t>(&setting_.wallet.transaction_version)->default_value(1),
            "The transaction version, defaults to 1."
        )
        (
            "wallet.rule_fork_flags",
            value<uint32_t>(&setting_.wallet.rule_fork_flags)->default_value(4294967295),
            "The rule fork flags, defaults to all (4294967295)."
        )
        (
            "network.identifier",
            value<uint32_t>(&setting_.network.identifier)->default_value(3652501241),
            "The magic number for message headers, defaults to 3652501241."
        )
        (
            "network.connect_retries",
            value<explorer::config::byte>(&setting_.network.connect_retries)->default_value(0),
            "The number of times to retry contacting a node, defaults to 0."
        )
        (
            "network.connect_timeout_seconds",
            value<uint32_t>(&setting_.network.connect_timeout_seconds)->default_value(5),
            "The time limit for connection establishment, defaults to 5."
        )
        (
            "network.channel_handshake_seconds",
            value<uint32_t>(&setting_.network.channel_handshake_seconds)->default_value(30),
            "The time limit to complete the connection handshake, defaults to 30."
        )
        (
            "network.hosts_file",
            value<boost::filesystem::path>(&setting_.network.hosts_file)->default_value("hosts.cache"),
            "The peer hosts cache file path, defaults to 'hosts.cache'."
        )
        (
            "network.debug_file",
            value<boost::filesystem::path>(&setting_.network.debug_file)->default_value("debug.log"),
            "The debug log file path, defaults to 'debug.log'."
        )
        (
            "network.error_file",
            value<boost::filesystem::path>(&setting_.network.error_file)->default_value("error.log"),
            "The error log file path, defaults to 'error.log'."
        )
        (
            "network.seed",
            value<std::vector<system::config::endpoint>>(&setting_.network.seeds),
            "A seed node for initializing the host pool, multiple entries allowed."
        )
        (
            "server.url",
            value<system::config::endpoint>(&setting_.server.url)->default_value({ "tcp://mainnet.libbitcoin.net:9091" }),
            "The URL of the Libbitcoin query service."
        )
        (
            "server.block_url",
            value<system::config::endpoint>(&setting_.server.block_url)->default_value({ "tcp://mainnet.libbitcoin.net:9093" }),
            "The URL of the Libbitcoin block service."
        )
        (
            "server.transaction_url",
            value<system::config::endpoint>(&setting_.server.transaction_url)->default_value({ "tcp://mainnet.libbitcoin.net:9094" }),
            "The URL of the Libbitcoin transaction service."
        )
        (
            "server.socks_proxy",
            value<system::config::authority>(&setting_.server.socks_proxy)->default_value({ "0.0.0.0:0" }),
            "The address of a SOCKS5 proxy to use, defaults to none."
        )
        (
            "server.connect_retries",
            value<explorer::config::byte>(&setting_.server.connect_retries)->default_value(0),
            "The number of times to retry contacting a server, defaults to 0."
        )
        (
            "server.connect_timeout_seconds",
            value<uint16_t>(&setting_.server.connect_timeout_seconds)->default_value(5),
            "The time limit for connection establishment, defaults to 5."
        )
        (
            "server.server_public_key",
            value<protocol::zmq::sodium>(&setting_.server.server_public_key),
            "The Base85 encoded public key of the server."
        )
        (
            "server.client_private_key",
            value<protocol::zmq::sodium>(&setting_.server.client_private_key),
            "The Base85 encoded private key of the client."
        );
    }

    /**
     * Load streamed value as parameter fallback.
     * @param[in]  input      The input stream for loading the parameter.
     * @param[in]  variables  The loaded variables.
     */
    virtual void load_stream(std::istream& input, po::variables_map& variables)
    {
    }

    /**
     * Set variable defaults from configuration variable values.
     * @param[in]  variables  The loaded variables.
     */
    virtual void set_defaults_from_config(po::variables_map& variables)
    {
    }

    /**
     * Write the help for this command to the specified stream.
     * @param[out] output  The output stream.
     */
    virtual void write_help(std::ostream& output)
    {
        const auto& options = get_option_metadata();
        const auto& arguments = get_argument_metadata();
        system::config::printer help(options, arguments, BX_PROGRAM_NAME,
            description(), name());
        help.initialize();
        help.commandline(output);
    }

    /* Properties */

    /**
     * Get command line argument metadata.
     */
    virtual system::arguments_metadata& get_argument_metadata()
    {
        return argument_metadata_;
    }

    /**
     * Get command line option metadata.
     */
    virtual system::options_metadata& get_option_metadata()
    {
        return option_metadata_;
    }

    /**
     * Get the value of the wallet.witness_version setting.
     */
    virtual explorer::config::byte get_wallet_witness_version_setting() const
    {
        return setting_.wallet.witness_version;
    }

    /**
     * Set the value of the wallet.witness_version setting.
     */
    virtual void set_wallet_witness_version_setting(explorer::config::byte value)
    {
        setting_.wallet.witness_version = value;
    }

    /**
     * Get the value of the wallet.witness_address_prefix setting.
     */
    virtual std::string get_wallet_witness_address_prefix_setting() const
    {
        return setting_.wallet.witness_address_prefix;
    }

    /**
     * Set the value of the wallet.witness_address_prefix setting.
     */
    virtual void set_wallet_witness_address_prefix_setting(std::string value)
    {
        setting_.wallet.witness_address_prefix = value;
    }

    /**
     * Get the value of the wallet.wif_version setting.
     */
    virtual explorer::config::byte get_wallet_wif_version_setting() const
    {
        return setting_.wallet.wif_version;
    }

    /**
     * Set the value of the wallet.wif_version setting.
     */
    virtual void set_wallet_wif_version_setting(explorer::config::byte value)
    {
        setting_.wallet.wif_version = value;
    }

    /**
     * Get the value of the wallet.hd_public_version setting.
     */
    virtual uint32_t get_wallet_hd_public_version_setting() const
    {
        return setting_.wallet.hd_public_version;
    }

    /**
     * Set the value of the wallet.hd_public_version setting.
     */
    virtual void set_wallet_hd_public_version_setting(uint32_t value)
    {
        setting_.wallet.hd_public_version = value;
    }

    /**
     * Get the value of the wallet.hd_secret_version setting.
     */
    virtual uint32_t get_wallet_hd_secret_version_setting() const
    {
        return setting_.wallet.hd_secret_version;
    }

    /**
     * Set the value of the wallet.hd_secret_version setting.
     */
    virtual void set_wallet_hd_secret_version_setting(uint32_t value)
    {
        setting_.wallet.hd_secret_version = value;
    }

    /**
     * Get the value of the wallet.pay_to_public_key_hash_version setting.
     */
    virtual explorer::config::byte get_wallet_pay_to_public_key_hash_version_setting() const
    {
        return setting_.wallet.pay_to_public_key_hash_version;
    }

    /**
     * Set the value of the wallet.pay_to_public_key_hash_version setting.
     */
    virtual void set_wallet_pay_to_public_key_hash_version_setting(explorer::config::byte value)
    {
        setting_.wallet.pay_to_public_key_hash_version = value;
    }

    /**
     * Get the value of the wallet.pay_to_script_hash_version setting.
     */
    virtual explorer::config::byte get_wallet_pay_to_script_hash_version_setting() const
    {
        return setting_.wallet.pay_to_script_hash_version;
    }

    /**
     * Set the value of the wallet.pay_to_script_hash_version setting.
     */
    virtual void set_wallet_pay_to_script_hash_version_setting(explorer::config::byte value)
    {
        setting_.wallet.pay_to_script_hash_version = value;
    }

    /**
     * Get the value of the wallet.transaction_version setting.
     */
    virtual uint32_t get_wallet_transaction_version_setting() const
    {
        return setting_.wallet.transaction_version;
    }

    /**
     * Set the value of the wallet.transaction_version setting.
     */
    virtual void set_wallet_transaction_version_setting(uint32_t value)
    {
        setting_.wallet.transaction_version = value;
    }

    /**
     * Get the value of the wallet.rule_fork_flags setting.
     */
    virtual uint32_t get_wallet_rule_fork_flags_setting() const
    {
        return setting_.wallet.rule_fork_flags;
    }

    /**
     * Set the value of the wallet.rule_fork_flags setting.
     */
    virtual void set_wallet_rule_fork_flags_setting(uint32_t value)
    {
        setting_.wallet.rule_fork_flags = value;
    }

    /**
     * Get the value of the network.identifier setting.
     */
    virtual uint32_t get_network_identifier_setting() const
    {
        return setting_.network.identifier;
    }

    /**
     * Set the value of the network.identifier setting.
     */
    virtual void set_network_identifier_setting(uint32_t value)
    {
        setting_.network.identifier = value;
    }

    /**
     * Get the value of the network.connect_retries setting.
     */
    virtual explorer::config::byte get_network_connect_retries_setting() const
    {
        return setting_.network.connect_retries;
    }

    /**
     * Set the value of the network.connect_retries setting.
     */
    virtual void set_network_connect_retries_setting(explorer::config::byte value)
    {
        setting_.network.connect_retries = value;
    }

    /**
     * Get the value of the network.connect_timeout_seconds setting.
     */
    virtual uint32_t get_network_connect_timeout_seconds_setting() const
    {
        return setting_.network.connect_timeout_seconds;
    }

    /**
     * Set the value of the network.connect_timeout_seconds setting.
     */
    virtual void set_network_connect_timeout_seconds_setting(uint32_t value)
    {
        setting_.network.connect_timeout_seconds = value;
    }

    /**
     * Get the value of the network.channel_handshake_seconds setting.
     */
    virtual uint32_t get_network_channel_handshake_seconds_setting() const
    {
        return setting_.network.channel_handshake_seconds;
    }

    /**
     * Set the value of the network.channel_handshake_seconds setting.
     */
    virtual void set_network_channel_handshake_seconds_setting(uint32_t value)
    {
        setting_.network.channel_handshake_seconds = value;
    }

    /**
     * Get the value of the network.hosts_file setting.
     */
    virtual boost::filesystem::path get_network_hosts_file_setting() const
    {
        return setting_.network.hosts_file;
    }

    /**
     * Set the value of the network.hosts_file setting.
     */
    virtual void set_network_hosts_file_setting(boost::filesystem::path value)
    {
        setting_.network.hosts_file = value;
    }

    /**
     * Get the value of the network.debug_file setting.
     */
    virtual boost::filesystem::path get_network_debug_file_setting() const
    {
        return setting_.network.debug_file;
    }

    /**
     * Set the value of the network.debug_file setting.
     */
    virtual void set_network_debug_file_setting(boost::filesystem::path value)
    {
        setting_.network.debug_file = value;
    }

    /**
     * Get the value of the network.error_file setting.
     */
    virtual boost::filesystem::path get_network_error_file_setting() const
    {
        return setting_.network.error_file;
    }

    /**
     * Set the value of the network.error_file setting.
     */
    virtual void set_network_error_file_setting(boost::filesystem::path value)
    {
        setting_.network.error_file = value;
    }

    /**
     * Get the value of the network.seed settings.
     */
    virtual std::vector<system::config::endpoint> get_network_seeds_setting() const
    {
        return setting_.network.seeds;
    }

    /**
     * Set the value of the network.seed settings.
     */
    virtual void set_network_seeds_setting(std::vector<system::config::endpoint> value)
    {
        setting_.network.seeds = value;
    }

    /**
     * Get the value of the server.url setting.
     */
    virtual system::config::endpoint get_server_url_setting() const
    {
        return setting_.server.url;
    }

    /**
     * Set the value of the server.url setting.
     */
    virtual void set_server_url_setting(system::config::endpoint value)
    {
        setting_.server.url = value;
    }

    /**
     * Get the value of the server.block_url setting.
     */
    virtual system::config::endpoint get_server_block_url_setting() const
    {
        return setting_.server.block_url;
    }

    /**
     * Set the value of the server.block_url setting.
     */
    virtual void set_server_block_url_setting(system::config::endpoint value)
    {
        setting_.server.block_url = value;
    }

    /**
     * Get the value of the server.transaction_url setting.
     */
    virtual system::config::endpoint get_server_transaction_url_setting() const
    {
        return setting_.server.transaction_url;
    }

    /**
     * Set the value of the server.transaction_url setting.
     */
    virtual void set_server_transaction_url_setting(system::config::endpoint value)
    {
        setting_.server.transaction_url = value;
    }

    /**
     * Get the value of the server.socks_proxy setting.
     */
    virtual system::config::authority get_server_socks_proxy_setting() const
    {
        return setting_.server.socks_proxy;
    }

    /**
     * Set the value of the server.socks_proxy setting.
     */
    virtual void set_server_socks_proxy_setting(system::config::authority value)
    {
        setting_.server.socks_proxy = value;
    }

    /**
     * Get the value of the server.connect_retries setting.
     */
    virtual explorer::config::byte get_server_connect_retries_setting() const
    {
        return setting_.server.connect_retries;
    }

    /**
     * Set the value of the server.connect_retries setting.
     */
    virtual void set_server_connect_retries_setting(explorer::config::byte value)
    {
        setting_.server.connect_retries = value;
    }

    /**
     * Get the value of the server.connect_timeout_seconds setting.
     */
    virtual uint16_t get_server_connect_timeout_seconds_setting() const
    {
        return setting_.server.connect_timeout_seconds;
    }

    /**
     * Set the value of the server.connect_timeout_seconds setting.
     */
    virtual void set_server_connect_timeout_seconds_setting(uint16_t value)
    {
        setting_.server.connect_timeout_seconds = value;
    }

    /**
     * Get the value of the server.server_public_key setting.
     */
    virtual protocol::zmq::sodium get_server_server_public_key_setting() const
    {
        return setting_.server.server_public_key;
    }

    /**
     * Set the value of the server.server_public_key setting.
     */
    virtual void set_server_server_public_key_setting(protocol::zmq::sodium value)
    {
        setting_.server.server_public_key = value;
    }

    /**
     * Get the value of the server.client_private_key setting.
     */
    virtual protocol::zmq::sodium get_server_client_private_key_setting() const
    {
        return setting_.server.client_private_key;
    }

    /**
     * Set the value of the server.client_private_key setting.
     */
    virtual void set_server_client_private_key_setting(protocol::zmq::sodium value)
    {
        setting_.server.client_private_key = value;
    }

protected:

    /**
     * This base class is abstract but not pure virtual, so prevent direct
     * construction here.
     */
    command()
    {
    }

private:

    /**
     * Command line argument metadata.
     */
    system::arguments_metadata argument_metadata_;

    /**
     * Command line option metadata.
     */
    system::options_metadata option_metadata_;

    /**
     * Environment variable bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct environment
    {
        environment()
        {
        }

    } environment_;

    /**
     * Configuration setting file bound variables.
     * Uses cross-compiler safe constructor-based zeroize.
     * Zeroize for unit test consistency with program_options initialization.
     */
    struct setting
    {
        struct wallet
        {
            wallet()
              : witness_version(),
                witness_address_prefix(),
                wif_version(),
                hd_public_version(),
                hd_secret_version(),
                pay_to_public_key_hash_version(),
                pay_to_script_hash_version(),
                transaction_version(),
                rule_fork_flags()
            {
            }

            explorer::config::byte witness_version;
            std::string witness_address_prefix;
            explorer::config::byte wif_version;
            uint32_t hd_public_version;
            uint32_t hd_secret_version;
            explorer::config::byte pay_to_public_key_hash_version;
            explorer::config::byte pay_to_script_hash_version;
            uint32_t transaction_version;
            uint32_t rule_fork_flags;
        } wallet;

        struct network
        {
            network()
              : identifier(),
                connect_retries(),
                connect_timeout_seconds(),
                channel_handshake_seconds(),
                hosts_file(),
                debug_file(),
                error_file(),
                seeds()
            {
            }

            uint32_t identifier;
            explorer::config::byte connect_retries;
            uint32_t connect_timeout_seconds;
            uint32_t channel_handshake_seconds;
            boost::filesystem::path hosts_file;
            boost::filesystem::path debug_file;
            boost::filesystem::path error_file;
            std::vector<system::config::endpoint> seeds;
        } network;

        struct server
        {
            server()
              : url(),
                block_url(),
                transaction_url(),
                socks_proxy(),
                connect_retries(),
                connect_timeout_seconds(),
                server_public_key(),
                client_private_key()
            {
            }

            system::config::endpoint url;
            system::config::endpoint block_url;
            system::config::endpoint transaction_url;
            system::config::authority socks_proxy;
            explorer::config::byte connect_retries;
            uint16_t connect_timeout_seconds;
            protocol::zmq::sodium server_public_key;
            protocol::zmq::sodium client_private_key;
        } server;

        setting()
          : wallet(),
            network(),
            server()
        {
        }
    } setting_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
