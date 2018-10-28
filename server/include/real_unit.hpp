//
// Created by sergey on 28.10.18.
//

/*
    the part of a unit, that has coordinates
    from this base and unit derived
*/

#ifndef SERVER_REAL_UNIT_HPP
#define SERVER_REAL_UNIT_HPP

class RealUnit {
    public:
        RealUnit(const int& _id, const int& _HP, const int _unit_x,
                const int& _unit_y): id(_id), HP(_HP),
                unit_x(_unit_x), unit_y(_unit_y) {}
    protected:
        int id;
        int HP;
        int unit_x;
        int unit_y;
};

#endif //SERVER_REAL_UNIT_HPP
