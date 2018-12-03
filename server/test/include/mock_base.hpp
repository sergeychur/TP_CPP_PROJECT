//
// Created by sergey on 16.11.18.
//

#ifndef SERVER_MOCK_BASE_HPP
#define SERVER_MOCK_BASE_HPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "abstract_base.hpp"



class MockBase : public AbstractBase {
    public:
        MockBase() : AbstractBase(nullptr) {};
        ~MockBase() = default;
        MOCK_METHOD1(start_making, void(std::vector<int>&));
        MOCK_METHOD0(is_ready, bool());
        MOCK_METHOD0(get_unit, std::shared_ptr<Unit>());
        MOCK_METHOD2(interact, bool(const std::string&, std::vector<int>&));
        MOCK_METHOD0(notify, void());
        MOCK_METHOD1(add, void(std::shared_ptr<NewsTaker>));
        MOCK_METHOD0(remove, void());
        MOCK_METHOD1(act, bool(Command&));
    private:
        MOCK_METHOD0(is_alive, bool());


};

#endif //SERVER_MOCK_BASE_HPP
