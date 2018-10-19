//
// Created by sergey on 19.10.18.
//

/*
    class, made to specify in some way the parameters of skill's act methods,
    remove in case of inventing smth cleverer
*/

#ifndef SERVER_PARAMETER_HPP
#define SERVER_PARAMETER_HPP

class Parameter {
    public:
        explicit Parameter(void* _data) : data(_data) {}
        Parameter() = delete;
        Parameter(const Parameter&) = delete;
        Parameter(const Parameter&&) = delete;
        Parameter& operator=(const Parameter&) = delete;
        Parameter&& operator=(const Parameter&&) = delete;

        inline void* get_data() {return data;};

    private:
        void* data;
};

#endif //SERVER_PARAMETER_HPP
