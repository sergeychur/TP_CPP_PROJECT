//
// Created by sergey on 19.10.18.
//

/*
    The command, sent by client to server
 */

#ifndef SERVER_COMMAND_HPP
#define SERVER_COMMAND_HPP

#include <string>
#include <vector>

#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/access.hpp>

#include "Serializable.h"

struct Command : public Serializable{
    public:
        Command(size_t _player_id, size_t _unit_id,
                const std::string& _command_name, std::vector<int>& _parameters) :
                player_id(_player_id),
                unit_id(_unit_id), command_name(_command_name), parameters(_parameters) {};
        Command() = default;

        size_t player_id;
        size_t unit_id;
        std::string command_name;   // add_unit, move, kick etc.
        std::vector<int> parameters;    // args

        friend class boost::serialization::access;
        template<class Archive>
        inline void serialize(Archive& ar, const unsigned int version) {
            ar & player_id & unit_id & command_name & parameters;
        }

        void serialize(boost::archive::text_oarchive& ar) final;
        void deserialize(boost::archive::text_iarchive& ar) final;
};

bool operator== (const Command& first, const Command& second);

std::istream& operator>> (std::istream& input, Command& com);
std::ostream& operator<< (std::ostream& output, const Command& com);

#endif //SERVER_COMMAND_HPP
