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
#ifndef SX_CALLBACK_STATE_HPP
#define SX_CALLBACK_STATE_HPP

#include <iostream>
#include <string>
#include <boost/thread/lockable_adapter.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/strict_lock.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Shared state wrapper to manage reentrant thread-safe and non-global shared 
 * call state. Each instance of this class is internally locking.
 */
class callback_state
    : public boost::lockable_adapter<boost::recursive_mutex>
{
public:

    /**
     * Construct an instance of the callback_state class. The class is
     * initialized with a reference count of zero (0). If the streams
     * references passed here are used elsewhere or in another instance
     * on another thread then stream interleaving cannot be prevented.
     * @param[in]  error   The error stream for the callback handler.
     * @param[in]  output  The output stream for the callback handler.
     */
    callback_state(std::ostream& error, std::ostream& output)
        : error_(error), output_(output), refcount_(0), stopped_(true),
        result_(console_result::okay)
    {
    }

    /**
     * Write a line to the error stream. The stream must be flushed before 
     * returning on order to prevent interleaving on the shared stream.
     * @param[in]  message  The unterminated error message to write.
     */
    void error(const boost::basic_format<char>& message)
    {
        // std::endl adds "/n" and flushes the stream.
        boost::strict_lock<callback_state> guard(*this);
        error_ << message << std::endl;
    }
   
    /**
     * Write a line to the error stream. The stream must be flushed before 
     * returning on order to prevent interleaving on the shared stream.
     * @param[in]  message  The unterminated error message to write.
     */
    void error(const std::string& message)
    {
        error(format(message));
    }

    /**
     * Write a line to the output stream. The stream must be flushed before 
     * returning on order to prevent interleaving on the shared stream.
     * @param[in]  message  The unterminated output message to write.
     */
    void output(const boost::basic_format<char>& message)
    {
        // std::endl adds "/n" and flushes the stream.
        boost::strict_lock<callback_state> guard(*this);
        output_ << message << std::endl;
    }

    /**
     * Write a line to the output stream. The stream must be flushed before 
     * returning on order to prevent interleaving on the shared stream.
     * @param[in]  message  The unterminated output message to write.
     */
    void output(const std::string& message)
    {
        output(format(message));
    }
    
    /**
     * Set the callback refcount to one and reset result to okay.
     */
    void start()
    {
        boost::strict_lock<callback_state> guard(*this);
        refcount_ = 1;
        stopped_ = false;
        result_ = console_result::okay;
    }
    
    /**
     * Set the callback refcount to zero and assign the result.
     * This overrides any outstanding callback references.
     * @param[in]  result  The desired callback result code, defaults to okay.
     */
    void stop(console_result result=console_result::okay)
    {
        boost::strict_lock<callback_state> guard(*this);
        refcount_ = 0;
        stopped_ = true;
        result_ = result;
    }
    
    /**
     * Get a value indicating whether the callback reference count is zero.
     * @return  True if the reference count is zero.
     */
    bool& stopped()
    {
        return stopped_;
    }

    /**
     * Get the callback result code.
     */
    const console_result get_result()
    {
        return result_;
    }

    /**
     * Set the callback result code.
     */
    void set_result(console_result result)
    {
        boost::strict_lock<callback_state> guard(*this);
        result_ = result;
    }
    
    /**
     * Increment the callback synchronization reference count.
     * @return  The callback synchronization counter value.
     */
    size_t increment()
    {
        boost::strict_lock<callback_state> guard(*this);

        if (++refcount_ != 0)
            stopped_ = false;

        return refcount_;
    }

    /**
     * Decrement the callback synchronization reference count.
     * @return  The callback synchronization counter value.
     */
    size_t decrement()
    {
        boost::strict_lock<callback_state> guard(*this);

        if (--refcount_ == 0)
            stopped_ = true;

        return refcount_;
    }

    /**
     * Overload numeric cast to return the reference count.
     */
    operator size_t() const
    {
        return refcount_;
    }

    /**
     * Overload ++ operator to increment the reference count.
     */
    callback_state& operator++()
    {
        boost::strict_lock<callback_state> guard(*this);
        increment();
        return *this;
    }

    /**
     * Overload ++ operator to decrement the reference count.
     */
    callback_state& operator--()
    {
        boost::strict_lock<callback_state> guard(*this);
        decrement();
        return *this;
    }

private:
    bool stopped_;
    size_t refcount_;
    console_result result_;
    std::ostream& error_;
    std::ostream& output_;
};

} // sx

#endif
