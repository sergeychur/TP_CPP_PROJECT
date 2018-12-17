//
// Created by sergey on 19.10.18.
//

#include <iostream>
#include <memory>
#include <chrono>
#include "update_maker.hpp"

UpdateMaker::~UpdateMaker() {
	update.clear();
}

void UpdateMaker::handle_event(const UpdateLine &line) {
	if(update.find({line.player_id, line.unit_id}) != update.end()) {
		update.erase({line.player_id, line.unit_id});
	}
	update[{line.player_id, line.unit_id}] = line;
}

std::unique_ptr<Update> UpdateMaker::get_update() {
	if(update.empty()) {
		throw(std::runtime_error("No update"));
	}
	std::unique_ptr<Update> update_to_return;
	for(auto& it : update) {
		update_to_return->updates.push_back(it.second);
	}
	return update_to_return;
}

