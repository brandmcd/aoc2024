#include "dayXX.hpp"
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
TEST_MAIN();