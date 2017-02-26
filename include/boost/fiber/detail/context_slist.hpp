
//          Copyright Oliver Kowalke 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONTEXT_SLIST_H
#define BOOST_FIBERS_DETAIL_CONTEXT_SLIST_H

#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>

namespace boost {
namespace fibers {
namespace detail {

template< typename Context >
class context_slist {
private:
    Context *   head_{ nullptr };
    Context **  tail_{ & head_ };

public:
    bool empty() const noexcept {
        return nullptr == head_;
    }

    void push( Context * c) noexcept {
        if ( nullptr == ( * tail_) ) {
            * tail_ = c;
        } else {
            ( * tail_)->next = c;
            tail_ = & ( * tail_)->next;
        }
    }

    Context * pop() noexcept {
        Context * c = head_;
        if ( nullptr != head_) {
            head_ = head_->next;
        }
        return c;
    }

    void unlink( Context * c) noexcept {
        BOOST_ASSERT( nullptr != head_);
        Context ** indirect = & head_;
        while ( c != ( * indirect) ) {
            indirect = & ( * indirect)->next;
        }
        * indirect = c->next;
        c->next = nullptr;
    }
};

}}}

#endif //  BOOST_FIBERS_DETAIL_CONTEXT_SLIST_H
