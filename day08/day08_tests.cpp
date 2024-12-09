#include "day08.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

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

TEST(part1_example)
{
    try
    {
        ifstream file("example_input.txt");

        auto p1 = part1(file);
        cout << "Part1: " << p1 << '\n';
    }
    catch (std::exception &e)
    {
        cout << e.what();
    }
}

TEST(part2_example)
{
    try
    {
        ifstream file("example_input.txt");

        auto p1 = part2(file);
        cout << "Part2: " << p1 << '\n';
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
        cout << "Part2: " << p1 << '\n';
    }
    catch (std::exception &e)
    {
        cout << e.what();
    }
}

TEST_MAIN();