#include "day05.hpp"

using namespace std;


//map from # to nums they have to be before
unordered_map<int, unordered_set<int>> nums;

bool isLessThan(int lhs, int rhs)
{
    if(nums[lhs].find(rhs) != nums[lhs].end())
    {
        return true;
    }
    return false;
}

int part1(std::istream &in)
{
    nums.clear();
    // parse input until blank line
    string line;
    while (in >> line && line != "a")
    {
        //in format ##|##
        int num1 = stoi(line.substr(0, 2));
        int num2 = stoi(line.substr(3, 2));
        nums[num1].insert(num2);
    }
    //now parsing the ordering
    int sum = 0;
    while (in >> line)
    {
        //in format ##,##,##,##,...
        //make a vector of the numbers
        vector<int> order;
        for(int i = 0; i < line.length(); i+=3)
        {
            order.push_back(stoi(line.substr(i, 2)));
        }
        vector<int> preSort = order;
        //use custom less than to sort
        sort(order.begin(), order.end(), isLessThan);
        //sum += middle element
        if(preSort == order)
        {
            sum += order[order.size()/2];
        }
    }
    return sum;
}


int part2(std::istream &in)
{
    nums.clear();
    // parse input until blank line
    string line;
    while (in >> line && line != "a")
    {
        //in format ##|##
        int num1 = stoi(line.substr(0, 2));
        int num2 = stoi(line.substr(3, 2));
        nums[num1].insert(num2);
    }
    //now parsing the ordering
    int sum = 0;
    while (in >> line)
    {
        //in format ##,##,##,##,...
        //make a vector of the numbers
        vector<int> order;
        for(int i = 0; i < line.length(); i+=3)
        {
            order.push_back(stoi(line.substr(i, 2)));
        }
        vector<int> preSort = order;
        //use custom less than to sort
        sort(order.begin(), order.end(), isLessThan);
        //sum += middle element
        if(preSort != order)
        {
            sum += order[order.size()/2];
        }
    }
    return sum;
}