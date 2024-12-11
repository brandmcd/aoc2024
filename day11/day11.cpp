#include "day11.hpp"
#include <list>

using namespace std;

int part1(std::istream &in)
{
    std::list<long long> stones;
    // split input by space
    string token;
    while (getline(in, token, ' '))
    {
        stones.push_back(stoll(token));
    }
    int iterations = 25;
    cout << "size: " << stones.size() << endl;
    for (int i = 0; i < iterations; i++)
    {
        for (auto it = stones.begin(); it != stones.end(); it++)
        {
            // if stone is 0 it becomes one
            if (*it == 0)
            {
                *it = 1;
            }
            // if stone has an even number of digits, split into two stones
            else if (to_string(*it).size() % 2 == 0)
            {
                string s = to_string(*it);
                int half = s.size() / 2;
                long long first = stoll(s.substr(0, half));
                long long second = stoll(s.substr(half, half));
                *it = first;
                stones.insert(it, second);
            }
            else
            {
                *it = *it * 2024;
            }
        }
        cout << "after " << i + 1 << " blinks " << stones.size() << endl;
    }
    return stones.size();
}

unordered_map<long long, long long> blink(const unordered_map<long long, long long> &stones)
{
    unordered_map<long long, long long> newStones;

    for (const auto &[stone, count] : stones)
    {
        if (stone == 0)
        {
            newStones[1] += count;
        }
        else if (to_string(stone).size() % 2 == 0)
        {
            string s = to_string(stone);
            int half = s.size() / 2;
            long long first = stoll(s.substr(0, half));
            long long second = stoll(s.substr(half, half));
            newStones[first] += count;
            newStones[second] += count;
        }
        else
        {
            newStones[stone * 2024] += count;
        }
    }
    return newStones;
}

int part2(std::istream &in)
{
    // map from stone # to amount of stones with that number
    std::unordered_map<long long, long long> stones;
    // split input by space
    string token;
    while (getline(in, token, ' '))
    {
        stones[stoll(token)] = 1;
    }
    int iterations = 75;
    for (int i = 0; i <= iterations; i++)
    {
        
        // sum up all stone values
        long long sum = 0;
        for (const auto &[stone, count] : stones)
        {
            sum += count;
        }
        cout << "after " << i << " blinks " << sum << endl;
        stones = blink(stones);
    }

    return 0;
}
