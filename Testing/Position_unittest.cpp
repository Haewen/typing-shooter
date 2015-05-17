#include <gtest/gtest.h>
#include "Position.h"

TEST(Position, settersGetters) {
    Position a;
    
    a.setX(10);
    EXPECT_FLOAT_EQ(10, a.getX());
    a.setY(20);
    EXPECT_FLOAT_EQ(20, a.getY());
    
    a.set(30, 40);
    EXPECT_FLOAT_EQ(30, a.getX());
    EXPECT_FLOAT_EQ(40, a.getY());
}

TEST(Position, distance) {
    Position a = Position(10,0);
    Position b = Position(10,10);
    EXPECT_FLOAT_EQ(10.0, a.distance(b));
}