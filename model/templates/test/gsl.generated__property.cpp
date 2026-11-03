.template 0
###############################################################################
# Copyright (c) 2011-2023 libbitcoin developers (see COPYING).
#
# GSL generate libbitcoin-explorer source files.
# This file contains no localizable resources.
#
# This is a code generator built using the iMatix GSL code generation
# language. See https://github.com/imatix/gsl for details.
###############################################################################

function is_unquoted_type(type)
    return (my.type = "bool") | \
        (my.type = "size_t") | \
        (my.type = "uint8_t") | \
        (my.type = "uint16_t") | \
        (my.type = "uint32_t") | \
        (my.type = "uint64_t") | \
        (my.type = "explorer::config::byte")
endfunction

function sample_value(type)
    if (my.type = "bool")
        return "true"
    elsif (my.type = "size_t") | (my.type = "uint8_t") | \
        (my.type = "uint16_t") | (my.type = "uint32_t") | \
        (my.type = "uint64_t") | (my.type = "explorer::config::byte")
        return "42"
    elsif (my.type = "std::string")
        return "string"
    elsif (my.type = "explorer::config::address")
        return "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L"
    elsif (my.type = "explorer::config::algorithm")
        return "greedy"
    elsif (my.type = "explorer::config::btc")
        return "42.42"
    elsif (my.type = "explorer::config::bytes")
        return "baadf00d"
    elsif (my.type = "explorer::config::ec_private")
        return "4c721ccd679b817ea5e86e34f9d46abb1660a63955dde908702214eaab038475"
    elsif (my.type = "explorer::config::electrum")
        return "standard"
    elsif (my.type = "explorer::config::endorsement")
        return "3044022039a36013301597daef41fbe593a02cc513d0b55527ec2df1050e2e8ff49c85c202201035fe810e283bcf394485c6a9dfd117ad9f684cdd83d36453718f5d0491b9dd01"
    elsif (my.type = "explorer::config::hd_key")
        return "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi"
    elsif (my.type = "explorer::config::language")
        return "en"
    elsif (my.type = "explorer::config::sighash")
        return "all"
    elsif (my.type = "explorer::config::signature")
        return "HxQp3cXgOIhBEGXks27sfeSQHVgNUeYgl5i5wG/dOUYaSIRnnzXR6NcyH+AfNAHtkWcyOD9rX4pojqmuQyH79K4="
    elsif (my.type = "system::config::base16")
        return "baadf00d"
    elsif (my.type = "system::config::base32")
        return "MJQWCZDGGAYGI==="
    elsif (my.type = "system::config::base58")
        return "5mm7zk"
    elsif (my.type = "system::config::base64")
        return "YmFhZGYwMGQ="
    elsif (my.type = "system::config::base85")
        return "HelloWorld"
    elsif (my.type = "system::config::hash160")
        return "b472a266d0bd89c13706a4132ccfb16f7c3b9fcb"
    elsif (my.type = "system::config::hash256")
        return "000000000019d6689c085ae165831e934ff763ae46a2a6c172b3f1b60a8ce26f"
    elsif (my.type = "system::config::input")
        return "4a5e1e4baab89f3a32518a88c31bc87f618f76673e2cc77ab2127b7afdeda33b:0:4294967295"
    elsif (my.type = "system::config::output")
        return "[baadf00d]:42"
    elsif (my.type = "system::config::script")
        return "dup hash160 [001fa7459a6cfc64bdc178ba7e7a21603bb2568f] equalverify checksig"
    elsif (my.type = "system::config::transaction")
        return "0100000001b3807042c92f449bbf79b33ca59d7dfec7f4cc71096704a9c526dddf496ee0970100000000ffffffff01905f0100000000001976a91418c0bd8d1818f1bf99cb1df2269c645318ef7b7388ac00000000"
    elsif (my.type = "system::config::url")
        return "http://127.0.0.1:1"
    elsif (my.type = "system::wallet::bitcoin_uri")
        return "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L"
    elsif (my.type = "system::wallet::ec_private")
        return "KynK1v6fGwt2deK5axWUi4dStZzyuhrMbsYwk52kXM5LMivMMrQp"
    elsif (my.type = "system::wallet::ec_public")
        return "03ac9e60013853128b42a1324609bac2ccff6a0b4844b6301f1f552e15ee14c7a5"
    elsif (my.type = "system::wallet::ek_private")
        return "6PRVWUbkzzsbcVac2qwfssoUJAN1Xhrg6bNk8J7Nzm5H7kxEbn2Nh2ZoGg"
    elsif (my.type = "system::wallet::ek_public")
        return "cfrm38V8aXBn7JWA1ESmFMUn6erxeBGZGAxJPY4e36S9QWkzZKtaVqLNMgnifETYw7BPwWC9aPD"
    elsif (my.type = "system::wallet::ek_token")
        return "passphrasecpXbDpHuo8F7yuZqR49koDA9uQojPijjjZaxsar7Woo9pfHJbeWF3VMU9EPBqJ"
    elsif (my.type = "system::wallet::payment_address")
        return "1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa"
    elsif (my.type = "system::wallet::witness_address")
        return "bc1qw508d6qejxtdg4y5r3zarvary0c5xw7kv8f3t4"
    endif
    abort "No sample value for type '$(my.type)'."
endfunction
.endtemplate
.template 1
.echo "Generating test/generated__property.cpp..."
.output "../test/generated__property.cpp"
.copyleft()

#include <bitcoin/explorer.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

template <typename Value>
static std::string serial(const Value& value)
{
    std::ostringstream text;
    text << value;
    return text.str();
}

template <typename Value>
static std::string serial(const std::vector<Value>& values)
{
    std::ostringstream text;
    for (const auto& value: values)
        text << value;

    return text.str();
}

BC_AUTO_TEST_SUITE(generated)
BC_AUTO_TEST_SUITE(generated__property)
.for command by symbol
.   define has_properties = (count(command.argument) + count(command.option)) > 0
.   if (has_properties)

BC_AUTO_TEST_CASE(generated__property__$(symbol:c)__round_trips)
{
    $(symbol:c) command;
.       for argument
.           is_vector = !is_default(limit, 1)
.           cpp_type = normalize_type(!true(), !true(), type)
.           vtype = vectored_type(cpp_type, is_vector)
.           variable = "$(pluralize(name, is_vector):lower,c)_argument"
.           sample = sample_value(cpp_type)
.           if (is_vector)

    const $(vtype) $(variable){ { "$(sample)" } };
.           elsif (is_unquoted_type(cpp_type))

    const $(vtype) $(variable){ $(sample) };
.           else

    const $(vtype) $(variable){ "$(sample)" };
.           endif
    command.set_$(variable)($(variable));
    BC_REQUIRE_EQUAL(serial(command.get_$(variable)()), serial($(variable)));
.       endfor
.       for option
.           is_vector = is_xml_true(multiple)
.           cpp_type = normalize_type(true(), !true(), type)
.           vtype = vectored_type(cpp_type, is_vector)
.           variable = "$(pluralize(name, is_vector):lower,c)_option"
.           sample = sample_value(cpp_type)
.           if (is_vector)

    const $(vtype) $(variable){ { "$(sample)" } };
.           elsif (is_unquoted_type(cpp_type))

    const $(vtype) $(variable){ $(sample) };
.           else

    const $(vtype) $(variable){ "$(sample)" };
.           endif
    command.set_$(variable)($(variable));
    BC_REQUIRE_EQUAL(serial(command.get_$(variable)()), serial($(variable)));
.       endfor
}
.   endif
.endfor

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
.endtemplate
