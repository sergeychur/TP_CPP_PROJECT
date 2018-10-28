//
// Created by sergey on 28.10.18.
//

#ifndef SERVER_VERTEX_HPP
#define SERVER_VERTEX_HPP

#include <vector>

struct Vertex {
    public:
        Vertex(const int& _x, const int& _y): vertex_x(_x), vertex_y(_y) {}
        Vertex(const Vertex& other) = default;
        int vertex_x;
        int vertex_y;
};

#endif //SERVER_VERTEX_HPP
