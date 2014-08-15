/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include <sx/callback_state.hpp>

#include <iostream>
#include <cstdint>
#include <string>
#include <boost/format.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/thread/strict_lock.hpp>
#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <sx/serializer/encoding.hpp>
#include <sx/define.hpp>
#include <sx/prop_tree.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace pt;

namespace sx {
    
callback_state::callback_state(std::ostream& error, std::ostream& output,
    const encoding_engine engine)
    : error_(error), output_(output), refcount_(0), stopped_(true),
    engine_(engine), result_(console_result::okay)
{
}

callback_state::callback_state(std::ostream& error, std::ostream& output)
    : callback_state(error, output, encoding_engine::native)
{
}

bool callback_state::handle_error(const std::error_code& code, 
    const std::string& format)
{
    if (code)
    {
        // May want to change the behavior to decrement vs. zeroizing refs.
        error(boost::format(format) % code.message());
        stop(console_result::failure);
        return false;
    }

    return true;
}

// std::endl adds "/n" and flushes the stream.
void callback_state::error(const ptree tree)
{
    state_locker guard(*this);
    write_stream(error_, tree, engine_);
    error_ << std::endl;
}

// std::endl adds "/n" and flushes the stream.
void callback_state::error(const format& message)
{
    state_locker guard(*this);
    error_ << message << std::endl;
}

void callback_state::error(const std::string& message)
{
    error(format(message));
}

// std::endl adds "/n" and flushes the stream.
void callback_state::output(const pt::ptree tree)
{
    state_locker guard(*this);
    write_stream(error_, tree, engine_);
    output_ << std::endl;
}

// std::endl adds "/n" and flushes the stream.
void callback_state::output(const format& message)
{
    state_locker guard(*this);
    output_ << message  << std::endl;
}

void callback_state::output(const std::string& message)
{
    output(format(message));
}

void callback_state::start()
{
    state_locker guard(*this);
    refcount_ = 1;
    stopped_ = false;
    result_ = console_result::okay;
}

void callback_state::stop(console_result result)
{
    state_locker guard(*this);
    refcount_ = 0;
    stopped_ = true;
    result_ = result;
}

bool& callback_state::stopped()
{
    return stopped_;
}

const encoding_engine callback_state::get_engine()
{
    return engine_;
}

const console_result callback_state::get_result()
{
    return result_;
}

void callback_state::set_result(console_result result)
{
    state_locker guard(*this);
    result_ = result;
}

size_t callback_state::increment()
{
    state_locker guard(*this);
    if (++refcount_ != 0)
        stopped_ = false;

    return refcount_;
}

size_t callback_state::decrement()
{
    state_locker guard(*this);
    if (--refcount_ == 0)
        stopped_ = true;

    return refcount_;
}

callback_state::operator size_t() const
{
    return refcount_;
}

callback_state& callback_state::operator++()
{
    state_locker guard(*this);
    increment();
    return *this;
}

callback_state& callback_state::operator--()
{
    state_locker guard(*this);
    decrement();
    return *this;
}

} // sx
