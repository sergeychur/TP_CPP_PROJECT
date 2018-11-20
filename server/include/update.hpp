//
// Created by sergey on 19.10.18.
//

/*
    here are necessary things to know for all the clients
*/

#ifndef SERVER_UPDATE_HPP
#define SERVER_UPDATE_HPP

#include <vector>

struct UpdateLine {
    UpdateLine(const size_t&_player_id, const size_t&_unit_id, const int& _new_HP, const int& _new_x, const int& _new_y,
            const int& _new_angle, const bool& _is_alive):
                player_id(_player_id), unit_id(_unit_id), new_HP(_new_HP), new_x(_new_x),
                new_y(_new_y), new_angle(_new_angle), is_alive(_is_alive) {}
    size_t player_id;
    size_t unit_id;
    int new_HP;
    int new_x;
    int new_y;
    int new_angle;
    bool is_alive;
};

bool operator== (const UpdateLine&, const UpdateLine&);

struct Update {
    std::vector<UpdateLine> updates;
};

#endif //SERVER_UPDATE_HPP
