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
    UpdateLine(const int&_player_id, const int&_unit_id, const int& _new_HP, const int& _new_x, const int& _new_y,
            const int& _new_angle):
                player_id(_player_id), unit_id(_unit_id), new_HP(_new_HP), new_x(_new_x),
                new_y(_new_y), new_angle(_new_angle) {}
    int player_id;
    int unit_id;
    int new_HP;
    int new_x;
    int new_y;
    int new_angle;
};

bool operator== (const UpdateLine&, const UpdateLine&);

struct Update {
    std::vector<UpdateLine> updates;
};

#endif //SERVER_UPDATE_HPP
