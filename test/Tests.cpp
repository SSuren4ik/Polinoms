#include "Lexema.h"

#include <gtest.h>

TEST(Lexema, correct_Calculate)
{
    Queue<Lexema> res = lex("(123 + 10* 2- 3)/ 20\n");
    vector <Lexema> polka = Reverse_Polska(res);
    EXPECT_EQ(Calculate(polka), (123.0 + 10.0* 2.0 - 3.0) / 20.0);
}

TEST(Lexema, none_closed_parenthesis)
{
    Queue<Lexema> res = lex("(123 + 10* 2- 3/ 20\n");
    vector <Lexema> polka;
    ASSERT_ANY_THROW(Reverse_Polska(res));
}

TEST(Lexema, none_opend_parenthesis)
{
    Queue<Lexema> res = lex("(123 + 10* 2- 3))/ 20\n");
    vector <Lexema> polka;
    ASSERT_ANY_THROW(Reverse_Polska(res));
}

TEST(Lexema, many_operations)
{
    Queue<Lexema> res = lex("123 +*/ 10* 2- 3/ 20\n");
    vector <Lexema> polka = Reverse_Polska(res);
    ASSERT_ANY_THROW(Calculate(polka));
}