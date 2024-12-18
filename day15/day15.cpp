#include "day15.hpp"
#include <set>
#include <map>

using namespace std;

// width and height include #s
int GRID_WIDTH = 0;
int GRID_HEIGHT = 0;
set<pair<int, int>> boxes;
set<pair<int, int>> walls;
pair<int, int> robot = {0, 0}; // robot location

// MODIFIES: boxes
// EFFECTS: moves the box in the direction dir if possible
//          and recursively moves any boxes that are in the way
//          returns true if the box was moved
bool doMoveBox(pair<int, int> box, char dir)
{
    // base case there is no box in the way
    if (boxes.find(box) == boxes.end())
    {
        return true;
    }

    // first base case there is a wall in the way
    // second base case NO box in the way, move one over and return true
    // or do recursive call
    if (dir == '<')
    {
        pair<int, int> left = {box.first - 1, box.second};
        if(walls.find(left) != walls.end())
        {
            return false;
        }
        if (boxes.find(left) == boxes.end())
        {
            boxes.erase(box);
            box.first--;
            boxes.insert(box);
            return true;
        }
        if (doMoveBox(left, '<'))
        {
            boxes.erase(box);
            box.first--;
            boxes.insert(box);
            return true;
        }
        // couldn't move box
        return false;
    }
    if (dir == '>')
    {
        pair<int, int> right = {box.first + 1, box.second};
        if(walls.find(right) != walls.end())
        {
            return false;
        }
        if (boxes.find(right) == boxes.end())
        {
            boxes.erase(box);
            box.first++;
            boxes.insert(box);
            return true;
        }

        if (doMoveBox(right, '>'))
        {
            boxes.erase(box);
            box.first++;
            boxes.insert(box);
            return true;
        }
        // couldn't move box
        return false;
    }
    if (dir == '^')
    {
        pair<int, int> up = {box.first, box.second - 1};
        if(walls.find(up) != walls.end())
        {
            return false;
        }
        if (boxes.find(up) == boxes.end())
        {
            boxes.erase(box);
            box.second--;
            boxes.insert(box);
            return true;
        }
        if (doMoveBox(up, '^'))
        {
            boxes.erase(box);
            box.second--;
            boxes.insert(box);
            return true;
        }
        // couldn't move box
        return false;
    }
    if (dir == 'v')
    {
        pair<int, int> down = {box.first, box.second + 1};
        if(walls.find(down) != walls.end())
        {
            return false;
        }
        if (boxes.find(down) == boxes.end())
        {
            boxes.erase(box);
            box.second++;
            boxes.insert(box);
            return true;
        }
        if (doMoveBox(down, 'v'))
        {
            boxes.erase(box);
            box.second++;
            boxes.insert(box);
            return true;
        }
        // couldn't move box
        return false;
    }

    throw std::runtime_error("Invalid direction");
    return false;
}

void moveRobot(char dir)
{
   // cout << "Robot: " << robot.first << " " << robot.second << endl;
    //cout << "Dir: " << dir << endl;
    if (dir == '<')
    {
        pair<int, int> left = {robot.first - 1, robot.second};
        if(walls.find(left) != walls.end())
        {
            return;
        }
        if (boxes.find(left) == boxes.end())
        {
            robot = left;
        }
        else
        {
            if (doMoveBox(left, '<'))
            {
                robot = left;
            }
        }
    }
    if (dir == '>')
    {
        pair<int, int> right = {robot.first + 1, robot.second};
        if(walls.find(right) != walls.end())
        {
            return;
        }
        if (boxes.find(right) == boxes.end())
        {
            robot = right;
        }
        else
        {
            if (doMoveBox(right, '>'))
            {
                robot = right;
            }
        }
    }
    if (dir == '^')
    {
        pair<int, int> up = {robot.first, robot.second - 1};
        if(walls.find(up) != walls.end())
        {
            return;
        }
        if (boxes.find(up) == boxes.end())
        {
            robot = up;
        }
        else
        {
            if (doMoveBox(up, '^'))
            {
                robot = up;
            }
        }
    }
    if (dir == 'v')
    {
        pair<int, int> down = {robot.first, robot.second + 1};
        if(walls.find(down) != walls.end())
        {
            return;
        }   
        if (boxes.find(down) == boxes.end())
        {
            robot = down;
        }
        else
        {
            if (doMoveBox(down, 'v'))
            {
                robot = down;
            }
        }
    }
}

void printGrid()
{
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (robot.first == x && robot.second == y)
            {
                cout << "@";
            }
            else if (boxes.find({x, y}) != boxes.end())
            {
                cout << "O";
            }
            else if (walls.find({x, y}) != walls.end())
            {
                cout << "#";
            }
            else
            {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}

long long part1(std::istream &in)
{
    // parse input
    string line;
    // read in grid
    while (getline(in, line) && line.size() > 0)
    {
        cout << "Line: " << line << endl;
        GRID_WIDTH = line.size();
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == 'O')
            {
                boxes.insert({i, GRID_HEIGHT});
            }
            if (line[i] == '@')
            {
                robot = {i, GRID_HEIGHT};
            }
            if(line[i] == '#')
            {
                walls.insert({i, GRID_HEIGHT});
            }
        }
        
        GRID_HEIGHT++;
    }

    printGrid();

    // read in moves
    while (getline(in, line))
    {
        cout << "Line: " << line << endl;
        for (int i = 0; i < line.size(); i++)
        {
            moveRobot(line[i]);
           // printGrid();
        }
    }

    long long sum = 0;
    for (auto &box : boxes)
    {
        cout << box.first << " + 100* " << box.second << endl;
        sum += (box.first) + (100 *box.second);
        cout << "Sum: " << sum << endl;
    }
    return sum;
}

////////////////PART 2////////////////
//adjusting https://git.sr.ht/~moshepiekarski/AoC/tree/master/item/2024/soko.c 
//my original soln had to many edge cases and broke :( 

bool move(vector<string> &grid, int x, int y, int dir, bool dry) {
    int x2 = x + ((dir % 2) ? 0 : (dir ? 1 : -1));
    int y2 = y + (!(dir % 2) ? 0 : (dir == 1 ? 1 : -1));

    if (grid[x][y] == '.') return true;
    if (grid[x2][y2] == '#' || grid[x][y] == '#') return false;

    if (!(dir % 2) &&
        ((grid[x][y] == '[' && grid[x][y + 1] == ']') ||
         (grid[x][y] == ']' && grid[x][y - 1] == '['))) {
        if (grid[x][y] == '[') {
            if (move(grid, x2, y2, dir, true) && move(grid, x2, y2 + 1, dir, true)) {
                if (!dry) {
                    move(grid, x2, y2, dir, false);
                    move(grid, x2, y2 + 1, dir, false);
                    grid[x2][y2] = grid[x][y];
                    grid[x2][y2 + 1] = grid[x][y + 1];
                    grid[x][y] = grid[x][y + 1] = '.';
                }
                return true;
            }
            return false;
        } else if (grid[x][y] == ']') {
            if (move(grid, x2, y2, dir, true) && move(grid, x2, y2 - 1, dir, true)) {
                if (!dry) {
                    move(grid, x2, y2, dir, false);
                    move(grid, x2, y2 - 1, dir, false);
                    grid[x2][y2] = grid[x][y];
                    grid[x2][y2 - 1] = grid[x][y - 1];
                    grid[x][y] = grid[x][y - 1] = '.';
                }
                return true;
            }
            return false;
        }
    }

    if (grid[x2][y2] == '.') {
        if (!dry) { 
            grid[x2][y2] = grid[x][y];
            grid[x][y] = '.';
            if (!(dir % 2)) {
                if (grid[x2][y2] == '[' && grid[x][y + 1] == ']')
                    move(grid, x, y + 1, dir, false);
                else if (grid[x2][y2] == ']' && grid[x][y - 1] == '[')
                    move(grid, x, y - 1, dir, false);
            }
        } else {
            if (grid[x][y] == '[' && grid[x][y + 1] == ']') {
                grid[x][y] = 'O';
                bool ret = move(grid, x, y + 1, dir, true);
                grid[x][y] = '[';
                return ret;
            } else if (grid[x][y] == ']' && grid[x][y - 1] == '[')
                return move(grid, x, y - 1, dir, true);
        }
        return true;
    } else {
        if (!move(grid, x2, y2, dir, dry)) return false;
        grid[x2][y2] = grid[x][y];
        grid[x][y] = '.';
        return true;
    }
}

void printGrid(const vector<string> &grid) {
    for (const string &line : grid) cout << line << endl;
    cout << endl;
}

void printGrid(vector<string> &grid) {
    for (string &line : grid) cout << line << endl;
    cout << endl;
}


long long part2(istream &in) {
    string line;
    vector<string> grid;
    int x = 0, y = 0, dir = 0;

    // Parse grid input
    while (getline(in, line) && !line.empty()) {
        string newLine;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == '@') {
                newLine.append("@.");
                x = grid.size();
                y = newLine.size() - 2;
            } else if (line[i] == '#') {
                newLine.append("##");
            } else if (line[i] == 'O') {
                newLine.append("[]");
            } else {
                newLine.append("..");
            }
        }
        grid.push_back(newLine);
    }

    printGrid(grid);

    // Parse and execute commands
    while (getline(in, line)) {
        for (char ch : line) {
            switch (ch) {
                case '^': dir = 0; break;
                case '>': dir = 1; break;
                case 'v': dir = 2; break;
                case '<': dir = 3; break;
                default: throw runtime_error("Bad direction: " + string(1, ch));
            }
            if (move(grid, x, y, dir, false)) {
                if (dir == 0) --x;
                else if (dir == 2) ++x;
                else if (dir == 1) ++y;
                else if (dir == 3) --y;
            }
            printGrid(grid);
        }
    }

    // Calculate result
    long long result = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == '[') {
                cout << "i: " << i << " j: " << j << endl;
                cout << "Result: " << (i * 100) + j << endl;  
                result += (i * 100) + j;
            }
        }
    }

    return result;
}