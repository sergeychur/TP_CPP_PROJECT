//
// Created by sergey on 03.12.18.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "manager.hpp"

TEST(Manager, find_file) {
    Manager manager;
    boost::filesystem::path path1 = manager.get_file_path(2);
    boost::filesystem::path path2("maps/2/0.xml");
    EXPECT_EQ(path1, path2);
}

