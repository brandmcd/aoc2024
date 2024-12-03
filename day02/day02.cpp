#include "day02.hpp"
#include <sstream>
#include <algorithm>

using namespace std;

bool isSafe(vector<int> &level)
{
     bool isSafe = true;
        //check if Any two adjacent levels differ by at least one and at most three.
         for (int j = 0; j < level.size() - 1; j++) {
            int diff = abs(level[j] - level[j + 1]);
            if (diff < 1 || diff > 3) {
                return false;
            }
        }

        //check if strictly increasing
        for (int j = 0; j < level.size() - 1; j++) {
            if (level[j] >= level[j + 1]) {
                isSafe = false;
                break;
            }
        }

        if (!isSafe) {
            isSafe = true;
           //check if strictly decreasing
            for (int j = 0; j < level.size() - 1; j++) {
                if (level[j] <= level[j + 1]) {
                    isSafe = false;
                    break;
                }
            }
        }
        
        return isSafe;
    }

int part2(std::istream &in)
{
    //brute force solution
    string line;
    vector<vector<int>> levels;
    int safe = 0;
    while (std::getline(in, line)) {
        vector<int> level;
        istringstream lineStream(line);
        int i = -1;
        while (lineStream >> i) {
            level.push_back(i);
        }
        levels.push_back(level);
    }
    // Determine all levels that are considered safe.
    for (int i = 0; i < levels.size(); i++) {
        vector<int> level = levels[i];
        for(int j = 0; j < level.size(); j++) {
            vector<int> temp = level;
            level.erase(level.begin() + j);
            if (isSafe(level)) {
                safe++;
                break;
            }
            level = temp;
        }
    }
    return safe;
}

int part1(std::istream &in)
{
    // parse input
    string line;
    int safe = 0;
    while (std::getline(in, line)) {
        vector<int> level;
        istringstream lineStream(line);
        int i = -1;
        while (lineStream >> i) {
            level.push_back(i);
        }
        if(isSafe(level)) {
            safe++;
        }
    }
    return safe;
}

/*
int part2(std::istream &in)
{
    // parse input
    string line;
    vector<vector<int>> levels;
    int safe = 0;
    while (std::getline(in, line)) {
        vector<int> level;
        istringstream lineStream(line);
        int i = -1;
        while (lineStream >> i) {
            level.push_back(i);
        }
        levels.push_back(level);
    }
    // Determine all levels that are considered safe.
    for (int i = 0; i < levels.size(); i++) {
        vector<int> level = levels[i];
        bool isSafe = true;
        bool removed = false;
        //check if Any two adjacent levels differ by at least one and at most three.
         for (int j = 0; j < level.size() - 1; j++) {
            int diff = abs(level[j] - level[j + 1]);
            if ((diff < 1 || diff > 3) && !removed) {
                //remove the j+1 element
                level.erase(level.begin() + j + 1);
                j--;
                removed = true;
                cout << "Removed during adj check\n";   
            }
            else if ((diff < 1 || diff > 3) && removed) {
                isSafe = false;
                break;
            }
        }
        vector<int> temp = level;
        //failed prev means CAN'T be safe
        if (isSafe) {
        //check if strictly increasing
        for (int j = 0; j < level.size() - 1; j++) {
            if (level[j] >= level[j + 1] && !removed) {
                level.erase(level.begin() + j + 1);
                j--;
                removed = true;
                cout << "Removed during increasing check\n";
            }
            else if (level[j] >= level[j + 1] && removed) {
                isSafe = false;
                break;
            }
        }
        //was not strictly increasing
        if (!isSafe) {
            //reset level to what it was after adjance check
            level = temp;
            isSafe = true;
           //check if strictly decreasing
            for (int j = 0; j < level.size() - 1; j++) {
                if (level[j] <= level[j + 1] && !removed) {
                    //remove the j+1 element
                    level.erase(level.begin() + j + 1);
                    j--;
                    removed = true;
                    cout << "Removed during decreasing check\n";
                }
                else if (level[j] <= level[j + 1] && removed) {
                    isSafe = false;
                    break;
                }
            }
        }
        }
        if (isSafe) {
            safe++;
        }
    }
    return safe;
}
*/