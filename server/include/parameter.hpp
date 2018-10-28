//
// Created by sergey on 19.10.18.
//

/*
    Unnecessary, remove
*/

#ifndef SERVER_PARAMETER_HPP
#define SERVER_PARAMETER_HPP

class Parameter {
    public:
        explicit Parameter(void* _data) : data(_data) {}
        Parameter() = default;
        Parameter(const Parameter&) = delete;
        Parameter(const Parameter&&) = delete;
        Parameter& operator=(const Parameter&) = delete;
        Parameter&& operator=(const Parameter&&) = delete;

        bool IsEmpty() const {return !data;}
        inline void* get_data() {return data;};

    private:
        void* data;
};

#endif //SERVER_PARAMETER_HPP
