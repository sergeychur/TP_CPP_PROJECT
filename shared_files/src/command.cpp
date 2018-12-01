//
// Created by sergey on 22.11.18.
//

#include "command.hpp"

bool operator== (const Command& first, const Command& second) {
    return first.player_id == second.player_id &&
           first.unit_id == second.unit_id &&
           first.command_name == second.command_name &&
           first.parameters == second.parameters;
}

void Command::serialize(boost::archive::text_iarchive &ar, const unsigned int version) {
    serialize<boost::archive::text_iarchive>(ar, version);
}

void Command::serialize(boost::archive::text_oarchive &ar, const unsigned int version) {
    serialize<boost::archive::text_oarchive>(ar, version);
}
