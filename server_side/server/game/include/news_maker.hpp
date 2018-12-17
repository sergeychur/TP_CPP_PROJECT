//
// Created by sergey on 19.10.18.
//

/*
    Interface for some entity, that should say some other entity, what it has done
*/

#ifndef SERVER_NEWS_MAKER_HPP
#define SERVER_NEWS_MAKER_HPP

#include "news_taker.hpp"

class NewsMaker {
 public:
	virtual void add(std::shared_ptr<NewsTaker> news_taker) = 0;    // add somebody, who this should notify
	virtual void remove() = 0;      // remove observing smth
	virtual void notify() = 0;      // notify observing smth
	virtual ~NewsMaker() = default;
};

#endif        //  SERVER_NEWS_MAKER_HPP
