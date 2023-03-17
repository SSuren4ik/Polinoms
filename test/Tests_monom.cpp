#include "Monom.h"

#include <gtest.h>

TEST(Monom, correct_addition)
{
    Monom m1(1.0, 2, 4, 5);
    Monom m2(9.0, 2, 4, 5);
    Monom m3 = m1 + m2;
    EXPECT_EQ(10, m3.a);
}
TEST(Monom, correct_communication)
{
    Monom m1(1.0, 2, 4, 5);
    Monom m2(9.0, 2, 4, 5);
    Monom m3 = m1 * m2;
    int s = (2+2 + offset) + (4+4 + offset) * numbsystem + (5+5 + offset) * numbsystem * numbsystem;
    EXPECT_EQ(9, m3.a);
    EXPECT_EQ(s, m3.s);
}

TEST(Monom, incorrect_step)
{
    ASSERT_ANY_THROW(Monom(5, 15, 1, 1));
}

TEST(Monom, parsing_string)
{
    Monom m1(9.0, 2, 4, 5);
    Monom m2("9*x^2*y^4*z^5");
    EXPECT_EQ(m1.a, m2.a);
    EXPECT_EQ(m1.s, m2.s);
}
