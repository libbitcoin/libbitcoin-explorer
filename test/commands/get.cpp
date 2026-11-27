/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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

#include "command.hpp"

BX_USING_NAMESPACES()

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(get__invoke)

#define GET_TX "0200000000010140d43a99926d43eb0e619bf0b3d83b4a31f60c176beecfb9d35bf45e54d0f7420100000017160014a4b4ca48de0b3fffc15404a1acdc8dbaae226955ffffffff0100e1f5050000000017a9144a1154d50b03292b3024370901711946cb7cccc387024830450221008604ef8f6d8afa892dee0f31259b6ce02dd70c545cfcfed8148179971876c54a022076d771d6e91bed212783c9b06e0de600fab2d518fad6f15a2b191d7fbd262a3e0121039d25ab79f41f75ceaf882411fd41fa670a4c672c23ffaf0e361a969cde0692e800000000"
#define GET_HEADER "0100000000000000000000000000000000000000000000000000000000000000000000003ba3edfd7a7b12b27ac72c3e67768f617fc81bc3888a51323a9fb8aa4b1e5e4a29ab5f49ffff001d1dac2b7c"
#define GET_PREVIOUS "42f7d0545ef45bd3b9cfee6b170cf6314a3bd8b3f09b610eeb436d92993ad440"
#define GET_POINT "{\"hash\":\"" GET_PREVIOUS "\",\"index\":1}"
#define GET_INPUT_SCRIPT "[0014a4b4ca48de0b3fffc15404a1acdc8dbaae226955]"
#define GET_WITNESS "[30450221008604ef8f6d8afa892dee0f31259b6ce02dd70c545cfcfed8148179971876c54a022076d771d6e91bed212783c9b06e0de600fab2d518fad6f15a2b191d7fbd262a3e01] [039d25ab79f41f75ceaf882411fd41fa670a4c672c23ffaf0e361a969cde0692e8]"
#define GET_INPUT "{\"point\":" GET_POINT ",\"script\":\"" GET_INPUT_SCRIPT "\",\"witness\":\"" GET_WITNESS "\",\"sequence\":4294967295}"
#define GET_OUTPUT_SCRIPT "hash160 [4a1154d50b03292b3024370901711946cb7cccc3] equal"
#define GET_OUTPUT "{\"value\":100000000,\"script\":\"" GET_OUTPUT_SCRIPT "\"}"
#define GET_WRAPPER "{\"wrapper\":{\"checksum\":2743498322,\"payload\":\"b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\",\"version\":0}}"
#define GET_BECH32 "{\"bech32\":{\"prefix\":\"tb\",\"program\":\"751e\",\"version\":16}}"
#define GET_URI "{\"uri\":{\"address\":\"1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\",\"amount\":42,\"label\":\"l\",\"message\":\"m\",\"scheme\":\"bitcoin\"}}"

static chain::transaction segwit_tx()
{
    return { base16_chunk(GET_TX), true };
}

static chain::header genesis_header()
{
    return { base16_chunk(GET_HEADER) };
}

static std::string tx_json()
{
    return json::serialize(json::value_from(segwit_tx()));
}

static std::string header_json()
{
    return json::serialize(json::value_from(genesis_header()));
}

static std::string block_json()
{
    return json::serialize(json::value_from(chain::block{ genesis_header(), { segwit_tx() } }));
}

// transaction

BC_AUTO_TEST_CASE(get_version__invoke__transaction__okay_output)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument(tx_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2\n");
}

BC_AUTO_TEST_CASE(get_hash__invoke__transaction__okay_output)
{
    BX_DECLARE_COMMAND(get_hash);
    command.set_json_argument(tx_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("c586389e5e4b3acb9d6c8be1c19ae8ab2795397633176f5a6442a261bbdefc3a\n");
}

BC_AUTO_TEST_CASE(get_locktime__invoke__transaction__okay_output)
{
    BX_DECLARE_COMMAND(get_locktime);
    command.set_json_argument(tx_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0\n");
}

BC_AUTO_TEST_CASE(get_input__invoke__transaction__okay_output)
{
    BX_DECLARE_COMMAND(get_input);
    command.set_index_argument(0);
    command.set_json_argument(tx_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_INPUT "\n");
}

BC_AUTO_TEST_CASE(get_input__invoke__index_out_of_range__failure_error)
{
    BX_DECLARE_COMMAND(get_input);
    command.set_index_argument(1);
    command.set_json_argument(tx_json());
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_JSON_OUT_OF_RANGE "\n");
}

BC_AUTO_TEST_CASE(get_output__invoke__transaction__okay_output)
{
    BX_DECLARE_COMMAND(get_output);
    command.set_index_argument(0);
    command.set_json_argument(tx_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_OUTPUT "\n");
}

// input

BC_AUTO_TEST_CASE(get_point__invoke__input__okay_output)
{
    BX_DECLARE_COMMAND(get_point);
    command.set_json_argument(GET_INPUT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_POINT "\n");
}

BC_AUTO_TEST_CASE(get_script__invoke__input__okay_output)
{
    BX_DECLARE_COMMAND(get_script);
    command.set_json_argument(GET_INPUT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_INPUT_SCRIPT "\n");
}

BC_AUTO_TEST_CASE(get_witness__invoke__input__okay_output)
{
    BX_DECLARE_COMMAND(get_witness);
    command.set_json_argument(GET_INPUT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_WITNESS "\n");
}

BC_AUTO_TEST_CASE(get_sequence__invoke__input__okay_output)
{
    BX_DECLARE_COMMAND(get_sequence);
    command.set_json_argument(GET_INPUT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("4294967295\n");
}

// point

BC_AUTO_TEST_CASE(get_hash__invoke__point__okay_output)
{
    BX_DECLARE_COMMAND(get_hash);
    command.set_json_argument(GET_POINT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_PREVIOUS "\n");
}

BC_AUTO_TEST_CASE(get_index__invoke__point__okay_output)
{
    BX_DECLARE_COMMAND(get_index);
    command.set_json_argument(GET_POINT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1\n");
}

// output

BC_AUTO_TEST_CASE(get_value__invoke__output__okay_output)
{
    BX_DECLARE_COMMAND(get_value);
    command.set_json_argument(GET_OUTPUT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("100000000\n");
}

BC_AUTO_TEST_CASE(get_script__invoke__output__okay_output)
{
    BX_DECLARE_COMMAND(get_script);
    command.set_json_argument(GET_OUTPUT);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(GET_OUTPUT_SCRIPT "\n");
}

// header

BC_AUTO_TEST_CASE(get_hash__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_hash);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f\n");
}

BC_AUTO_TEST_CASE(get_version__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1\n");
}

BC_AUTO_TEST_CASE(get_previous__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_previous);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0000000000000000000000000000000000000000000000000000000000000000\n");
}

BC_AUTO_TEST_CASE(get_merkle_root__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_merkle_root);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b\n");
}

BC_AUTO_TEST_CASE(get_timestamp__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_timestamp);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1231006505\n");
}

BC_AUTO_TEST_CASE(get_bits__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_bits);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("486604799\n");
}

BC_AUTO_TEST_CASE(get_nonce__invoke__header__okay_output)
{
    BX_DECLARE_COMMAND(get_nonce);
    command.set_json_argument(header_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2083236893\n");
}

// block

BC_AUTO_TEST_CASE(get_header__invoke__block__okay_output)
{
    BX_DECLARE_COMMAND(get_header);
    command.set_json_argument(block_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(header_json() + "\n");
}

BC_AUTO_TEST_CASE(get_tx__invoke__block__okay_output)
{
    BX_DECLARE_COMMAND(get_tx);
    command.set_index_argument(0);
    command.set_json_argument(block_json());
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(tx_json() + "\n");
}

BC_AUTO_TEST_CASE(get_hash__invoke__block__failure_error)
{
    BX_DECLARE_COMMAND(get_hash);
    command.set_json_argument(block_json());
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_JSON_MISSING "\n");
}

// wrapper

BC_AUTO_TEST_CASE(get_checksum__invoke__wrapper__okay_output)
{
    BX_DECLARE_COMMAND(get_checksum);
    command.set_json_argument(GET_WRAPPER);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2743498322\n");
}

BC_AUTO_TEST_CASE(get_payload__invoke__wrapper__okay_output)
{
    BX_DECLARE_COMMAND(get_payload);
    command.set_json_argument(GET_WRAPPER);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n");
}

BC_AUTO_TEST_CASE(get_version__invoke__wrapper__okay_output)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument(GET_WRAPPER);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("0\n");
}

// bech32

BC_AUTO_TEST_CASE(get_prefix__invoke__bech32__okay_output)
{
    BX_DECLARE_COMMAND(get_prefix);
    command.set_json_argument(GET_BECH32);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("tb\n");
}

BC_AUTO_TEST_CASE(get_program__invoke__bech32__okay_output)
{
    BX_DECLARE_COMMAND(get_program);
    command.set_json_argument(GET_BECH32);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("751e\n");
}

BC_AUTO_TEST_CASE(get_version__invoke__bech32__okay_output)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument(GET_BECH32);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("16\n");
}

// uri

BC_AUTO_TEST_CASE(get_address__invoke__uri__okay_output)
{
    BX_DECLARE_COMMAND(get_address);
    command.set_json_argument(GET_URI);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\n");
}

BC_AUTO_TEST_CASE(get_amount__invoke__uri__okay_output)
{
    BX_DECLARE_COMMAND(get_amount);
    command.set_json_argument(GET_URI);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("42\n");
}

BC_AUTO_TEST_CASE(get_label__invoke__uri__okay_output)
{
    BX_DECLARE_COMMAND(get_label);
    command.set_json_argument(GET_URI);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("l\n");
}

BC_AUTO_TEST_CASE(get_message__invoke__uri__okay_output)
{
    BX_DECLARE_COMMAND(get_message);
    command.set_json_argument(GET_URI);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("m\n");
}

BC_AUTO_TEST_CASE(get_scheme__invoke__uri__okay_output)
{
    BX_DECLARE_COMMAND(get_scheme);
    command.set_json_argument(GET_URI);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin\n");
}

// failures

BC_AUTO_TEST_CASE(get_version__invoke__invalid_json__failure_error)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument("{\"version\":");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_JSON_INVALID "\n");
}

BC_AUTO_TEST_CASE(get_version__invoke__array__failure_error)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument("[{\"version\":1}]");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_JSON_MISSING "\n");
}

BC_AUTO_TEST_CASE(get_input__invoke__not_list__failure_error)
{
    BX_DECLARE_COMMAND(get_input);
    command.set_json_argument("{\"inputs\":42}");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_JSON_NOT_LIST "\n");
}

BC_AUTO_TEST_CASE(get_version__invoke__surrounding_whitespace__okay_output)
{
    BX_DECLARE_COMMAND(get_version);
    command.set_json_argument(" {\"version\":7}\n");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("7\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
