//
// Created by sergey on 28.10.18.
//

/*
     look abstract_building.hpp
*/

#ifndef SERVER_BUILDING_HPP
#define SERVER_BUILDING_HPP

#include <vector>

#include "abstract_building.hpp"

class Building : AbstractBuilding{
    public:
        Building() = default;
        Building(const std::vector<Vertex>& vertices);
        Building(const Building&) = delete;
        Building(const Building&&) = delete;
        Building& operator=(const Building&) = delete;
        Building&& operator=(const Building&&) = delete;
        void add(const Vertex&) override;
        bool if_inner(const Vertex& vert) override;
    private:
        std::vector<Vertex> vertices;
};

#endif //SERVER_BUILDING_HPP
