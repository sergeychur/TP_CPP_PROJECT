//
// Created by sergey on 19.10.18.
//

#include <iostream>
#include <memory>
#include <chrono>
#include "update_maker.hpp"

UpdateMaker::~UpdateMaker() {
	update.reset();
}

void UpdateMaker::handle_event(const UpdateLine &line) {
	if (!update) {
		update = std::make_unique<Update>();
	}
	for(int i = 0; i < update->updates.size(); ++i) {
		if(update->updates[i].player_id == line.player_id && update->updates[i].unit_id == line.unit_id) {
			update->updates[i] = line;
			return;
		}
	}
	update->updates.push_back(line);
}

std::unique_ptr<Update> UpdateMaker::get_update() {
	if(!update) {
		throw(std::runtime_error("No update"));
	}
	return std::move(update);
}

