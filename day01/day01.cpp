#include "day01.hpp"
#include <set>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

int part1(std::istream &in)
{
    std::vector<int> right;
    std::vector<int> left;
    // parse input
    string line;
    while (in >> line)
    {
        left.push_back(stoi(line));
        in >> line;
        right.push_back(stoi(line));
    }
    //"Line up smallest"
    //get smallest index for both
    int leftIndex = 0;
    int rightIndex = 0;
    for (int i = 0; i < left.size(); i++)
    {
        if (left[i] < left[leftIndex])
        {
            leftIndex = i;
        }
        if (right[i] < right[rightIndex])
        {
            rightIndex = i;
        }
    }
    int distance = 0;
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    for(int i = 0; i < left.size(); i++)
    {
        distance += abs(left[i] - right[i]);
    }
    return distance;
}

int part2(std::istream &in)
{
      std::vector<int> right;
    std::vector<int> left;
    // parse input
    string line;
    while (in >> line)
    {
        left.push_back(stoi(line));
        in >> line;
        right.push_back(stoi(line));
    }
    //"Line up smallest"
    //get smallest index for both
    int leftIndex = 0;
    int rightIndex = 0;
    for (int i = 0; i < left.size(); i++)
    {
        if (left[i] < left[leftIndex])
        {
            leftIndex = i;
        }
        if (right[i] < right[rightIndex])
        {
            rightIndex = i;
        }
    }
     
    //map from number to amount of times it appears
    std::map<int, int> rightMap;
    for(int i = 0; i < right.size(); i++)
    {
        rightMap[right[i]] += 1;
    }
    int simularityScore = 0;
    //count all diffs
    for(int i = 0; i < left.size(); i++)
    {
        if(rightMap[left[i]] > 0)
        {
             simularityScore += (rightMap[left[i]] * left[i]);
        }
    }
    return simularityScore;
}