//
// Created by sergey on 22.11.18.
//

#include <update.hpp>
#include "update.hpp"

bool operator== (const UpdateLine& first, const UpdateLine& second) {
    return first.player_id == second.player_id && first.unit_id == second.unit_id &&
           first.new_HP == second.new_HP &&
           first.new_x == second.new_x &&
           first.new_y == second.new_y &&
           first.new_angle == second.new_angle &&
           first.is_alive == second.is_alive;
}

void Update::serialize(boost::archive::text_iarchive &ar, const unsigned int version) {
    serialize<boost::archive::text_iarchive>(ar, version);
}

void Update::serialize(boost::archive::text_oarchive &ar, const unsigned int version) {
    serialize<boost::archive::text_oarchive>(ar, version);
}

std::ostream& operator<< (std::ostream& output, const UpdateLine& line) {
    output << line.player_id << " " << line.unit_id << line.new_HP << " "
    << line.new_x << " " << line.new_y  << " " << line.new_angle << " "
    << line.is_alive;
    return output;
}

std::ostream& operator<< (std::ostream& output, const Update& upd) {
    for(auto& update : upd.updates) {
        output << update << std::endl;
    }
    return output;
}
