#include "day10.hpp"
#include <queue>
#include <set>

using namespace std;

const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

//starts at trailhead x,y and searchs for all 9s it can reach
int bfs(vector<vector<char>> &map, int x, int y) {
    int rows = map.size();
    int cols = map[0].size();
    queue<pair<int, int>> q;
    set<pair<int, int>> visited;
    int foundNines = 0;

    q.push({x, y}); //add the start to the queue
    visited.insert({x, y}); //mark as visited

    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        int val = map[x][y] - '0';
        //if this is a 9, its a trail end
        if(val == 9) {
            foundNines++;
        }

        //check all neighbors IF they are 1+current
        for(auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            //check if out of bounds
            if(nx < 0 || nx >= rows || ny < 0 || ny >= cols) {
                continue;
            }
            
            int newVal = map[nx][ny] - '0';
            if(newVal != val + 1) {
                continue;
            }

            //check if visited
            if(visited.count({nx, ny})) {
                continue;
            }

            //mark as visited
            visited.insert({nx, ny});
            q.push({nx, ny});
        }
    }
    return foundNines;
}

int part1(std::istream &in)
{
    //2d grid of ints for map
    vector<vector<char>> map;
    // parse input
    string line;
    while (in >> line)
    {
        vector<char> row;
        for(int i = 0; i < line.size(); i++) {
           row.push_back(line[i]);
        }
        map.push_back(row);
    }
    int totalScore = 0;
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            if(map[i][j] == '0') {
                totalScore += bfs(map, i, j);
                //cout << "total score: " << totalScore << endl;
            }
        }
    }
    return totalScore;
}

//bfs allowing revisits
int bfs_revist(vector<vector<char>> &map, int x, int y) {
    int rows = map.size();
    int cols = map[0].size();
    queue<pair<int, int>> q;
    set<pair<int, int>> visited;
    int foundNines = 0;

    q.push({x, y}); //add the start to the queue

    while(!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        int val = map[x][y] - '0';
        //if this is a 9, its a trail end
        if(val == 9) {
            foundNines++;
            continue;
        }

        //check all neighbors IF they are 1+current
        for(auto [dx, dy] : directions) {
            int nx = x + dx;
            int ny = y + dy;
            //check if out of bounds
            if(nx < 0 || nx >= rows || ny < 0 || ny >= cols) {
                continue;
            }
            
            int newVal = map[nx][ny] - '0';
            if(newVal != val + 1) {
                continue;
            }
            
            q.push({nx, ny});
        }
    }
    return foundNines;
}
int part2(std::istream &in)
{
    //2d grid of ints for map
    vector<vector<char>> map;
    // parse input
    string line;
    while (in >> line)
    {
        vector<char> row;
        for(int i = 0; i < line.size(); i++) {
           row.push_back(line[i]);
        }
        map.push_back(row);
    }
    int totalScore = 0;
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            if(map[i][j] == '0') {
                totalScore += bfs_revist(map, i, j);
                cout << "total score: " << totalScore << endl;
            }
        }
    }
    return totalScore;
}