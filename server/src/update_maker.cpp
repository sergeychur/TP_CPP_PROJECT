//
// Created by sergey on 19.10.18.
//

#include <iostream>
#include <memory>
#include "update_maker.hpp"

UpdateMaker::UpdateMaker() {
    update = std::make_unique<Update>();
}

UpdateMaker::~UpdateMaker() {
    update.reset();
}

void UpdateMaker::handle_event(UpdateLine& line) {
    if(!update) {
        update = std::make_unique<Update>();
    }
    update->updates.push_back(line);
}

std::unique_ptr<Update> UpdateMaker::get_update() {
    if(!update) {
        throw(std::runtime_error("No update"));
    }
    return std::move(update);
}

