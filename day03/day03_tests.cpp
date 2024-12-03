#include "day03.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

//assume input is input.txt
TEST(part1)
{
    try
    {
        ifstream file("input.txt");

        auto p1 = part1(file);
        cout << "Part1: " << p1 << '\n';
    }
    catch (std::exception &e)
    {
        cout << e.what();
    }
}

TEST(part2)
{
    try
    {
        ifstream file("input.txt");

        auto p1 = part2(file);
        cout << "Part1: " << p1 << '\n';
    }
    catch (std::exception &e)
    {
        cout << e.what();
    }
}

TEST(example)
{
    istringstream in("");
    ASSERT_EQUAL(part1(in), 0);
    //ASSERT_EQUAL(part2(in), 0);
}
TEST_MAIN();