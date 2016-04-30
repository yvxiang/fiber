//          Copyright Nat Goodspeed 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_ASIO_DETAIL_BROADCAST_HPP
#define BOOST_FIBERS_ASIO_DETAIL_BROADCAST_HPP

#include <boost/assert.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/signals2/connection.hpp>

#include <boost/fiber/all.hpp>

#include <mutex>                    // std::unique_lock

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace asio {
namespace detail {

template < typename Signature >
class broadcast {
public:
    typedef boost::signals2::signal< Signature > signal;
    typedef typename signal::slot_type slot_type;
    typedef boost::signals2::connection connection;
    typedef boost::signals2::scoped_connection scoped_connection;

    static connection connect(const slot_type& slot) {
        return get_signal().connect(slot);
    }

    template < typename ... Args >
    static typename signal::result_type notify( Args && ... args) {
        // To avoid any slot function causing deadlock on any signals2 mutex,
        // a signal releases its mutexes during slot calls. Its documentation
        // states that it is therefore possible for simultaneous operator()
        // calls on different threads to invoke slots concurrently. Eliminate
        // that possibility.
        std::unique_lock< std::mutex > lk( get_mutex());
        return get_signal()( std::forward< Args >( args) ... );
    }

private:
    static signal& get_signal() {
        static signal signal_s;
        return signal_s;
    }

    static std::mutex& get_mutex() {
        static std::mutex mutex_s;
        return mutex_s;
    }
};

}}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_ASIO_DETAIL_BROADCAST_HPP
