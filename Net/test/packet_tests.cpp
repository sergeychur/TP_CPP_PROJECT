//
// Created by alex on 29.10.18.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Packet.h"

TEST(packet_update_test, convert_extract)
{
    Packet packet;
    Update before();
    packet.convert<Update>(before);
    Update after=packet.extract<Update>();
    EXPECT_EQ(before, after);
}

TEST(packet_command_test, convert_extract)
{
    Packet packet;
    Command before();
    packet.convert<Command>(before);
    Command after=packet.extract<Command>();
    EXPECT_EQ(before, after);
}