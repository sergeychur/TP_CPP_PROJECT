//
// Created by sergey on 19.10.18.
//

/*
    interface for entity that should look for changes on changing side
*/

#ifndef SERVER_NEWS_TAKER_HPP
#define SERVER_NEWS_TAKER_HPP

class NewsTaker {
    // handle with happened event on changing side
public:
    virtual void handle_event() = 0;
    virtual ~NewsTaker() = default;
};

#endif //SERVER_NEWS_TAKER_HPP
