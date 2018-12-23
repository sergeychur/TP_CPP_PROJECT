//
// Created by sergey on 22.11.18.
//

#include <map>
#include "../include/command.hpp"

bool operator== (const Command& first, const Command& second) {
    return first.player_id == second.player_id &&
           first.unit_id == second.unit_id &&
           first.command_name == second.command_name &&
           first.parameters == second.parameters;
}


void Command::deserialize(boost::archive::text_iarchive& ar) {
    ar >> *this;
}

void Command::serialize(boost::archive::text_oarchive& ar) {
    ar << *this;
}


std::istream& operator>> (std::istream& input, Command& com) {
    input >> com.player_id >> com.unit_id >> com.command_name;
    std::map<std::string, int> param_col = {
            {"check", 4},
            {"move", 2},
            {"kick", 2},
            {"create_unit", 7}
    };
    int i = 0;
    while(i < param_col[com.command_name]) {
        int elem = 0;
        input >> elem;
        com.parameters.push_back(elem);
        ++i;
    }
    return input;
}

std::ostream& operator<< (std::ostream& output, const Command& com) {
    output << com.player_id << " " << com.unit_id << " " << com.command_name << " ";
    for(auto& it : com.parameters) {
        output << it << " ";
    }
    output << std::endl;
    return output;
}