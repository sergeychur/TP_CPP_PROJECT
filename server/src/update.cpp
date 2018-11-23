//
// Created by sergey on 22.11.18.
//

#include "update.hpp"

bool operator== (const UpdateLine& first, const UpdateLine& second) {
    return first.player_id == second.player_id && first.unit_id == second.unit_id &&
           first.new_HP == second.new_HP &&
           first.new_x == second.new_x &&
           first.new_y == second.new_y &&
           first.new_angle == second.new_angle &&
           first.is_alive == second.is_alive;
}
