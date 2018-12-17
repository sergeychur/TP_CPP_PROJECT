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
	std::map<std::pair<size_t, size_t>, UpdateLine> update;
};

#endif        //  SERVER_UPDATE_MAKER_HPP
