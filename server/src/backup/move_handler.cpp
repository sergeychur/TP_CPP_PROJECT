//
// Created by sergey on 13.12.18.
//

#include "move_handler.hpp"

bool MoveHandler::handle(Command command) {
    auto unit_to_act = unit.lock();
    return unit_to_act->move(command.parameters);
}

