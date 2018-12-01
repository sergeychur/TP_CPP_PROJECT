//
// Created by sergey on 19.10.18.
//

/*
    interface for entity that should look for changes on changing side
*/

#ifndef SERVER_NEWS_TAKER_HPP
#define SERVER_NEWS_TAKER_HPP

#include "update.hpp"

class NewsTaker {
    // handle with happened event on changing side
public:
    virtual void handle_event(UpdateLine&) = 0;
    virtual std::shared_ptr<Update>&& get_update() = 0;
    virtual void delete_update() = 0;
    virtual ~NewsTaker() = default;
};

#endif //SERVER_NEWS_TAKER_HPP
