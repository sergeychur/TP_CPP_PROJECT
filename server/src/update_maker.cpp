//
// Created by sergey on 19.10.18.
//

#include "update_maker.hpp"

UpdateMaker::~UpdateMaker() {
    delete update;
}

void UpdateMaker::handle_event(UpdateLine& line) {
    update->updates.push_back(line);
}

Update UpdateMaker::get_update() {
    return *update;
}

void UpdateMaker::delete_update() {
    update->updates.clear();
}
