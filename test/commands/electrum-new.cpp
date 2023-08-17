/////**
//// * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
//// *
//// * This file is part of libbitcoin.
//// *
//// * This program is free software: you can redistribute it and/or modify
//// * it under the terms of the GNU Affero General Public License as published by
//// * the Free Software Foundation, either version 3 of the License, or
//// * (at your option) any later version.
//// *
//// * This program is distributed in the hope that it will be useful,
//// * but WITHOUT ANY WARRANTY; without even the implied warranty of
//// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//// * GNU Affero General Public License for more details.
//// *
//// * You should have received a copy of the GNU Affero General Public License
//// * along with this program.  If not, see <http://www.gnu.org/licenses/>.
//// */
////
////#include "command.hpp"
////
////BX_USING_NAMESPACES()
////
////BOOST_AUTO_TEST_SUITE(offline)
////BOOST_AUTO_TEST_SUITE(electrum_new__invoke)
////
////#ifdef WITH_ICU
////
////BOOST_AUTO_TEST_CASE(electrum_new__invoke__17_bytes__okay_output)
////{
////    BX_DECLARE_COMMAND(electrum_new);
////    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
////    BX_REQUIRE_OKAY(command.invoke(output, error));
////    BX_REQUIRE_OUTPUT("giggle crush argue inflict wear defy combine evolve tiger spatial crumble fury\n");
////}
////
////BOOST_AUTO_TEST_CASE(electrum_new__invoke__en_dictionary_prefix__okay_output)
////{
////    BX_DECLARE_COMMAND(electrum_new);
////    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
////    command.set_language_option({ "en" });
////    command.set_prefix_option({ "standard" });
////    BX_REQUIRE_OKAY(command.invoke(output, error));
////    BX_REQUIRE_OUTPUT("giggle crush argue inflict wear defy combine evolve tiger spatial crumble fury\n");
////}
////
////BOOST_AUTO_TEST_CASE(electrum_new__invoke__es_dictionary_prefix__okay_output)
////{
////    BX_DECLARE_COMMAND(electrum_new);
////    command.set_entropy_argument({ "05e669b4270f4e25bce6fc3736170d423c" });
////    command.set_language_option({ "es" });
////    command.set_prefix_option({ "standard" });
////    BX_REQUIRE_OKAY(command.invoke(output, error));
////    BX_REQUIRE_OUTPUT("gráfico codo ámbar insecto verbo cráter celoso entrar tarjeta sala coco frito\n");
////}
////
////BOOST_AUTO_TEST_CASE(electrum_new__invoke__32_bytes__okay_output)
////{
////    BX_DECLARE_COMMAND(electrum_new);
////    command.set_entropy_argument({ "b0756302179e800b182514c729f1d6814c377ff06097569ef540e6c1f1950f08" });
////    BX_REQUIRE_OKAY(command.invoke(output, error));
////    BX_REQUIRE_OUTPUT("divide february web hire limb run reject nuclear army zone brick below public ladder deer below again cluster divorce ketchup aerobic flee lonely absent\n");
////}
////
////#endif
////
////BOOST_AUTO_TEST_SUITE_END()
////BOOST_AUTO_TEST_SUITE_END()
