//
// Created by sergey on 28.10.18.
//


/*
    probably the check of collisions
    will be made on client, so is unnecessary
*/
#ifndef SERVER_ABSTRACT_BUILDING_HPP
#define SERVER_ABSTRACT_BUILDING_HPP

#include "vertex.hpp"

class AbstractBuilding {
    public:
        bool virtual if_inner(const Vertex& vert) = 0;
        void virtual add(const Vertex&) = 0;
        virtual ~AbstractBuilding() {}
};

#endif //SERVER_ABSTRACT_BUILDING_HPP
