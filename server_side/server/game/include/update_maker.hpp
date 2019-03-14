//
// Created by sergey on 19.10.18.
//

#ifndef SERVER_UPDATE_MAKER_HPP
#define SERVER_UPDATE_MAKER_HPP

#include <map>

#include "news_taker.hpp"
#include "update.hpp"

class UpdateMaker : public NewsTaker {
 public:
	UpdateMaker() = default;

	void handle_event(const UpdateLine &) override;

	std::unique_ptr<Update> get_update() override;

	~UpdateMaker() override;

 private:
	std::unique_ptr<Update> update;
};

#endif        //  SERVER_UPDATE_MAKER_HPP
