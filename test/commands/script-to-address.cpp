/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(script_to_address__invoke)

BOOST_AUTO_TEST_CASE(script_to_address__invoke__mainnet__expected_output)
{
    BX_DECLARE_COMMAND(script_to_address);
    command.set_version_option(5);
    const std::string script("dup hash160 [89abcdefabbaabbaabbaabbaabbaabbaabbaabba] equalverify checksig");
    command.set_script_argument({ script });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3F6i6kwkevjR7AsAd4te2YB2zZyASEm1HM\n");
}

BOOST_AUTO_TEST_CASE(script_to_address__invoke__testnet__expected_output)
{
    BX_DECLARE_COMMAND(script_to_address);
    command.set_version_option(196);
    const std::string script("dup hash160 [89abcdefabbaabbaabbaabbaabbaabbaabbaabba] equalverify checksig");
    command.set_script_argument({ script });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2N6evAVsnGPEmJxViJCWWeVAJCvBLFehT7L\n");
}

// Vector: www.reddit.com/r/Bitcoin/comments/2h4ic8/why_dont_rbitcoin_community_donate_towards/
BOOST_AUTO_TEST_CASE(script_to_address__invoke__multisig_mainnet__expected_output)
{
    BX_DECLARE_COMMAND(script_to_address);
    command.set_version_option(5);
    command.set_script_argument(
    { 
        {
            "2",
            "[048cdce248e9d30838a2b31ad7162195db0ef4c20517916fa371fd04b153c214eeb644dcda76a98d33b0180a949d521df1d75024587a28ef30f2906c266fbb360e]",
            "[04d34775baab521d7ba2bd43997312d5f663633484ae1a4d84246866b7088297715a049e2288ae16f168809d36e2da1162f03412bf23aa5f949f235eb2e7141783]",
            "[04534072a9a62226252917f3011082a429900bbc5d1e11386b16e64e1dc985259c1cbcea0bad66fa6f106ea617ddddb6de45ac9118a3dcfc29c0763c167d56290e]",
            "3",
            "checkmultisig"
        }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("3CS58tZGJtjz4qBFyNgQRtneKaWUjeEZVM\n");
}

BOOST_AUTO_TEST_CASE(script_to_address__invoke__multisig_testnet__expected_output)
{
    BX_DECLARE_COMMAND(script_to_address);
    command.set_version_option(196);
    command.set_script_argument(
    {
        {
            "2",
            "[048cdce248e9d30838a2b31ad7162195db0ef4c20517916fa371fd04b153c214eeb644dcda76a98d33b0180a949d521df1d75024587a28ef30f2906c266fbb360e]",
            "[04d34775baab521d7ba2bd43997312d5f663633484ae1a4d84246866b7088297715a049e2288ae16f168809d36e2da1162f03412bf23aa5f949f235eb2e7141783]",
            "[04534072a9a62226252917f3011082a429900bbc5d1e11386b16e64e1dc985259c1cbcea0bad66fa6f106ea617ddddb6de45ac9118a3dcfc29c0763c167d56290e]",
            "3",
            "checkmultisig"
        }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("2N3zHCdVHvMFLGcooeWJH3qmuXvieWfEFKG\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
