#include "day07.hpp"

using namespace std;

unordered_set<long> solveEquation(unordered_set<long> &prevSols, long next)
{
    unordered_set<long>  newVals;
    for(auto val : prevSols)
    {
        newVals.insert(val + next);
        newVals.insert(val * next);
    }
    return newVals;
}

bool isEquationPossible(long sum, vector<long> &vals)
{
    //hard code first 2
    if(vals.size() == 0)
    {
        return false;
    }

    if(vals.size() == 1)
    {
        return vals[0] == sum;
    }

    // recursively solve the equation
    unordered_set<long> solutions;
    solutions.insert(vals[0] + vals[1]);
    solutions.insert(vals[0] * vals[1]);
    for (int i = 2; i < vals.size(); i++)
    {
        solutions = solveEquation(solutions, vals[i]);
    }
    if (solutions.find(sum) != solutions.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int part1(std::istream &in)
{
    // sum -> vals
    vector<pair<long, vector<long>>> equations;
    int curEq = -1;
    // parse input
    string line;
    while (in >> line)
    {
        if (line.find(':') != string::npos)
        {
            // get the first number (before the :)
            long sum = stol(line.substr(0, line.find(':')));
            equations.push_back({sum, {}});
            curEq++;
        }
        else
        {
            equations[curEq].second.push_back(stol(line));
        }
    }

    long sum = 0;
    for (auto eq : equations)
    {
        // determine if eq is solvable
        if (isEquationPossible(eq.first, eq.second))
        {
            cout << "Equation " << eq.first << " is possible\n";
            sum += eq.first;
        }
        else
        {
            cout << "Equation " << eq.first << " is not possible\n";
        }
    }
    return sum;
}

int part2(std::istream &in)
{
    // parse input
    string line;
    while (in >> line)
    {
        // do something with line
    }
    return -1;
}