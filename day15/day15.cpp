#include "day15.hpp"
#include <set>

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

set<pair<int, int>> wideBoxes;

bool doMoveWideBox(pair<int, int> leftEdge, char dir) {
    // Calculate new position of the box
    pair<int, int> newLeft, newRight;
    if (dir == '<') {
        newLeft = {leftEdge.first - 1, leftEdge.second};
        newRight = {leftEdge.first, leftEdge.second};
    } else if (dir == '>') {
        newLeft = {leftEdge.first + 1, leftEdge.second};
        newRight = {leftEdge.first + 2, leftEdge.second};
    } else if (dir == '^') {
        newLeft = {leftEdge.first, leftEdge.second - 1};
        newRight = {leftEdge.first + 1, leftEdge.second - 1};
    } else if (dir == 'v') {
        newLeft = {leftEdge.first, leftEdge.second + 1};
        newRight = {leftEdge.first + 1, leftEdge.second + 1};
    } else {
        throw runtime_error("Invalid direction");
    }

    // Check if the move hits a wall
    if (walls.find(newLeft) != walls.end() || walls.find(newRight) != walls.end()) {
        return false;
    }

    // Check if there’s another box in the way
    if (wideBoxes.find(newLeft) != wideBoxes.end() || wideBoxes.find(newRight) != wideBoxes.end()) {
        pair<int, int> nextBox = (wideBoxes.find(newLeft) != wideBoxes.end()) ? newLeft : newRight;
        if (!doMoveWideBox(nextBox, dir)) {
            return false;
        }
    }

    // Perform the move
    wideBoxes.erase(leftEdge); 
    wideBoxes.insert(newLeft); 
    return true;
}

void moveRobotWide(char dir) {
    pair<int, int> newPos;
    pair<int, int> boxPos;

    if (dir == '<') {
        newPos = {robot.first - 1, robot.second};
        boxPos = {robot.first - 2, robot.second};
    } else if (dir == '>') {
        newPos = {robot.first + 1, robot.second};
        boxPos = {robot.first + 1, robot.second};
    } else if (dir == '^') {
        newPos = {robot.first, robot.second - 1};
        boxPos = {robot.first, robot.second - 1};
    } else if (dir == 'v') {
        newPos = {robot.first, robot.second + 1};
        boxPos = {robot.first, robot.second + 1};
    } else {
        throw runtime_error("Invalid direction");
    }

    // Check if the move hits a wall
    if (walls.find(newPos) != walls.end()) {
        return;
    }

    // Check if there’s a box in the way
    if (wideBoxes.find(boxPos) != wideBoxes.end()) {
        if (!doMoveWideBox(boxPos, dir)) {
            return; // Could not move the box
        }
    }

    // Move the robot
    robot = newPos;
}

void printWideGrid() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (robot.first == x && robot.second == y) {
                cout << "@";
            } else if (wideBoxes.find({x, y}) != wideBoxes.end()) {
                cout << "[]";
                x++; // Skip the next position for the wide box
            } else if (walls.find({x, y}) != walls.end()) {
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
    cout << endl;
}

long long part2(std::istream &in)
{
    //clear all global stuffs
    GRID_WIDTH = 0;
    GRID_HEIGHT = 0;
    boxes.clear();
    walls.clear();
    wideBoxes.clear();
    robot = {0, 0};

     // Parse input
    string line;
    while (getline(in, line) && line.size() > 0) {
        int x = 0;
        GRID_WIDTH = line.size() * 2;
        for (char c : line) {
            if (c == 'O') {
                wideBoxes.insert({{x, GRID_HEIGHT}, {x + 1, GRID_HEIGHT}});
                x += 2;
            } else if (c == '@') {
                robot = {x, GRID_HEIGHT};
                x += 2;
            } else if (c == '#') {
                walls.insert({x, GRID_HEIGHT});
                walls.insert({x + 1, GRID_HEIGHT});
                x += 2;
            } else if (c == '.') {
                x += 2;
            }
        }
        GRID_HEIGHT++;
    }

    printWideGrid();

    // read in moves
    while (getline(in, line))
    {
        cout << "Line: " << line << endl;
        for (int i = 0; i < line.size(); i++)
        {
            moveRobotWide(line[i]);
            printWideGrid();
        }
    }

    long long sum = 0;
    for (auto &box : wideBoxes)
    {
        cout << box.first << " + 100* " << box.second << endl;
        sum += (box.first) + (100 *box.second);
        cout << "Sum: " << sum << endl;
    }
    return sum;
}