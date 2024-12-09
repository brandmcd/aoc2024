#include "day08.hpp"
#include <map>

using namespace std;

int part1(std::istream &in)
{
    // map from freq to vector of locations
    map<char, vector<pair<int, int>>> freqs;
    int row = 0;
    int col = 0;
    int maxRow = 0;
    int maxCol = 0;
    // parse input
    string line;
    while (in >> line)
    {
        for (auto c : line)
        {
            if (c != '.')
            {
                freqs[c].push_back({row, col});
            }
            col++;
        }
        row++;
        maxRow = row;
        maxCol = col;
        col = 0;
    }

    //print out the freqs
    for (auto f : freqs)
    {
        cout << f.first << ": ";
        for (auto l : f.second)
        {
            cout << "(" << l.first << "," << l.second << ") ";
        }
        cout << '\n';
    }
    //"row,col"
    unordered_set<string> anti_nodes;
    for (auto f : freqs)
    {
        for (int i = 0; i < f.second.size(); i++)
        {
            for (int j = i+1; j < f.second.size(); j++)
            {
                //find distance from i to j
                int rowDiff = f.second[i].first - f.second[j].first;
                int colDiff = f.second[i].second - f.second[j].second;
                //apply in reverse to get anti-node
                int antiRow = f.second[j].first - rowDiff;
                int antiCol = f.second[j].second - colDiff;
                if (antiRow >= 0 && antiRow < maxRow && antiCol >= 0 && antiCol < maxCol)
                {
                    anti_nodes.insert(to_string(antiRow) + "," + to_string(antiCol));
                }
                //do it the other way
                antiRow = f.second[i].first + rowDiff;
                antiCol = f.second[i].second + colDiff;
                if (antiRow >= 0 && antiRow < maxRow && antiCol >= 0 && antiCol < maxCol)
                {
                    anti_nodes.insert(to_string(antiRow) + "," + to_string(antiCol));
                }
            }
        }
    }
    //print out the anti-nodes
    for (auto a : anti_nodes)
    {
        cout << a << '\n';
    }
    return anti_nodes.size();
}

int part2(std::istream &in)
{
      // map from freq to vector of locations
    map<char, vector<pair<int, int>>> freqs;
    int row = 0;
    int col = 0;
    int maxRow = 0;
    int maxCol = 0;
    // parse input
    string line;
    while (in >> line)
    {
        for (auto c : line)
        {
            if (c != '.')
            {
                freqs[c].push_back({row, col});
            }
            col++;
        }
        row++;
        maxRow = row;
        maxCol = col;
        col = 0;
    }
    //"row,col"
    unordered_set<string> anti_nodes;
    for (auto f : freqs)
    {
        for (int i = 0; i < f.second.size(); i++)
        {
            for (int j = i+1; j < f.second.size(); j++)
            {
                //find distance from i to j
                int rowDiff = f.second[i].first - f.second[j].first;
                int colDiff = f.second[i].second - f.second[j].second;
                //make this is the "slope"
                //add up until can't
                int antiRow = f.second[j].first;
                int antiCol = f.second[j].second;
                while (antiRow >= 0 && antiRow < maxRow && antiCol >= 0 && antiCol < maxCol)
                {
                    anti_nodes.insert(to_string(antiRow) + "," + to_string(antiCol));
                    antiRow += rowDiff;
                    antiCol += colDiff;
                }
                //do it the other way
                antiRow = f.second[j].first;
                antiCol = f.second[j].second;
                while (antiRow >= 0 && antiRow < maxRow && antiCol >= 0 && antiCol < maxCol)
                {
                    anti_nodes.insert(to_string(antiRow) + "," + to_string(antiCol));
                    antiRow -= rowDiff;
                    antiCol -= colDiff;
                }
            }

        }
    }
    return anti_nodes.size();
}