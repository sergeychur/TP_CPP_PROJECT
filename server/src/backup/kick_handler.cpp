//
// Created by sergey on 13.12.18.
//

#include "kick_handler.hpp"

bool KickHandler::handle(Command command) {
    auto unit_to_act = unit.lock();
    return unit_to_act->kick(command.parameters);
}
