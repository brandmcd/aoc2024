#include "day12.hpp"
#include <queue>
#include <set>

using namespace std;

const vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
set<pair<int, int>> visited;

//return area,perimeter
pair<int, int> floodFill(char c, vector<string> &grid, int x, int y)
{
   //x,y is the starting point
    int area = 1; //count the starting point
    int perimeter = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        
        //try to go in each direction, if its not 'c' then its a perimeter
        for(auto dir : directions)
        {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if(nx < 0 || nx >= grid.size() || ny < 0 || ny >= grid[0].size() || grid[nx][ny] != c)
            {
                perimeter++;
            }
            else if(grid[nx][ny] == c && visited.find({nx, ny}) == visited.end())
            {
                area++;
                q.push({nx, ny});
                visited.insert({nx, ny});
            }
        }
        q.pop();
    }
    return {area, perimeter};
}

long long part1(std::istream &in)
{
    vector<string> grid;
    // parse input
    string line;
    while (in >> line)
    {
       grid.push_back(line);
    }

    long long cost = 0;
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            //point not visited
            if(visited.find({i, j}) == visited.end())
            {
                visited.insert({i, j});
                auto [area, perimeter] = floodFill(grid[i][j], grid, i, j);
                cost += area * perimeter;
                cout << "Plant " << grid[i][j] << " Area: " << area << " Perimeter: " << perimeter << endl;
            }
        }
    }
    return cost;
}

bool isBorder(int x, int y, vector<string> &grid, char c)
{
    if(x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] != c)
    {
        return true;
    }
    return false;
}

int getNumberOfInteriorCorners(char c, vector<string> &grid, int x, int y)
{
    //an interior corner is 
    /*
        RRR      RRR      XRR      RRX
        RRR      RRR      RRR      RRR
        XRR      RRX      RRR      RRR
    */
    //where X,y is the center
    int cornerCount = 0;
    //check bottom left case
    if(isBorder(x - 1, y - 1, grid, c) && (!isBorder(x, y - 1, grid, c) && !isBorder(x - 1, y, grid, c)))
    {
        cornerCount++;
    }
    //check bottom right case
    if(isBorder(x - 1, y + 1, grid, c) && (!isBorder(x, y + 1, grid, c) && !isBorder(x - 1, y, grid, c)))
    {
        cornerCount++;
    }
    //check top left case
    if(isBorder(x + 1, y - 1, grid, c) && (!isBorder(x, y - 1, grid, c) && !isBorder(x + 1, y, grid, c)))
    {
        cornerCount++;
    }
    //check top right case
    if(isBorder(x + 1, y + 1, grid, c) && (!isBorder(x, y + 1, grid, c) && !isBorder(x + 1, y, grid, c)))
    {
        cornerCount++;
    }
    return cornerCount;
}
pair<int,int> getCornerCount(char c, vector<string> &grid, int x, int y)
{
    //x,y is the starting point
    int area = 1; //count the starting point
    int cornerCount = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        
        //find how many corners this block has
        //if two of these spots are taken then a corner exists on this block
        pair<int, int> up = {x - 1, y};
        pair<int, int> down = {x + 1, y};
        pair<int, int> left = {x, y - 1};
        pair<int, int> right = {x, y + 1};

        if(isBorder(up.first, up.second, grid, c) && isBorder(left.first, left.second, grid, c))
        {
            cornerCount++;
        }
        if(isBorder(up.first, up.second, grid, c) && isBorder(right.first, right.second, grid, c))
        {
            cornerCount++;
        }
        if(isBorder(down.first, down.second, grid, c) && isBorder(left.first, left.second, grid, c))
        {
            cornerCount++;
        }
        if(isBorder(down.first, down.second, grid, c) && isBorder(right.first, right.second, grid, c))
        {
            cornerCount++;
        }

        cornerCount += getNumberOfInteriorCorners(c, grid, x, y);
        
        //area stuff
        for(auto dir : directions)
        {
            int nx = x + dir.first;
            int ny = y + dir.second;
            if(isBorder(nx, ny, grid, c))
            {
                //do nothing
            }
            else if(grid[nx][ny] == c && visited.find({nx, ny}) == visited.end())
            {
                area++;
                q.push({nx, ny});
                visited.insert({nx, ny});
            }
        }
        q.pop();
    }
    return {area, cornerCount};
}
long long part2(std::istream &in)
{
    visited.clear();
   vector<string> grid;
    // parse input
    string line;
    while (in >> line)
    {
       grid.push_back(line);
    }
    long long cost = 0;
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            //point not visited
            if(visited.find({i, j}) == visited.end())
            {
                visited.insert({i, j});
                auto [area, corners] = getCornerCount(grid[i][j], grid, i, j);
                //# of walls = # of corners
                cost += area * corners;
                cout << "Plant " << grid[i][j] << " Area: " << area << " Walls: " << corners << endl;
            }
        }
    }
    return cost;
}