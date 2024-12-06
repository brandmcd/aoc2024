#include "day06.hpp"

using namespace std;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int part1(std::istream &in)
{
    //guard tracking  
   int curRow = 0; int curCol = 0;
   int row = 0; int col = 0;
   Direction dir = UP;
    // parse input
   vector<vector<char>> map;
   vector<vector<char>> traveled;
    string line;
    while (in >> line)
    {
        vector<char> curline;
        curRow++;
        for (char c : line)
        {
            if(c == '^')
            {
                row = curRow;
                col = curCol;
            }
            curCol++;
            curline.push_back(c);
        }
        curCol = 0;
        map.push_back(curline);
    }
    traveled = map;
    cout << "row: " << row << " col: " << col << endl;
    //set of seen locations
    unordered_set<string> seen;
    //while in bounds
    while(row >= 0 && row < map.size() && col >= 0 && col < map[0].size())
    {
        seen.insert(to_string(row) + "," + to_string(col));
        traveled[row][col] = 'X';
        if(dir == UP)
        {
            //attempt to move up
            if(row-1 >= 0 && map[row-1][col] == '#')
            {
                cout << "FAIL UP --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = RIGHT;
            }
            else
            {
                cout << "UP --- row: " << row << " col: " << col << endl;
                //move up
                row--;
            }
        }
        else if(dir == DOWN)
        {
            
            //attempt to move down
            if(row+1 < map.size() && map[row+1][col] == '#')
            {
                cout << "FAIL DOWN --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = LEFT;
            }
            else
            {
                cout << "DOWN --- row: " << row << " col: " << col << endl;
                //move down
                row++;
            }
        }
        else if(dir == LEFT)
        {
            //attempt to move left
            if(col-1 >= 0 && map[row][col-1] == '#')
            {
                cout << "FAIL LEFT --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = UP;
            }
            else
            {
                cout << "LEFT --- row: " << row << " col: " << col << endl;
                //move left
                col--;
            }
        }
        else if(dir == RIGHT)
        {
            
            //attempt to move right
            if(col+1 < map[0].size() && map[row][col+1] == '#')
            {
                cout << "FAIL RIGHT --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = DOWN;
            }
            else
            {
                cout << "RIGHT --- row: " << row << " col: " << col << endl;
                //move right
                col++;
            }
        }
    }

    //print traveled
    /*
    for(int i = 0; i < traveled.size(); i++)
    {
        for(int j = 0; j < traveled[0].size(); j++)
        {
            cout << traveled[i][j];
        }
        cout << endl;
    }
    */
    return seen.size(); //considering the starting location
}

bool isLoop(const vector<vector<char>> &map, int startRow, int startCol)
{
    Direction dir = UP;
    int row = startRow;
    int col = startCol;
    unordered_set<string> seen;
    while(row >= 0 && row < map.size() && col >= 0 && col < map[0].size())
    {
        //if weve been in this place and direction before return true
        if(seen.find(to_string(row) + "," + to_string(col) + "," + to_string(dir)) != seen.end())
        {
            return true;
        }
        seen.insert(to_string(row) + "," + to_string(col) + "," + to_string(dir));
        if(dir == UP)
        {
            //attempt to move up
            if(row-1 >= 0 && map[row-1][col] == '#')
            {
                //turn 90
                dir = RIGHT;
            }
            else
            {
                //move up
                row--;
            }
        }
        else if(dir == DOWN)
        {
            
            //attempt to move down
            if(row+1 < map.size() && map[row+1][col] == '#')
            {
                //turn 90
                dir = LEFT;
            }
            else
            {
                //move down
                row++;
            }
        }
        else if(dir == LEFT)
        {
            //attempt to move left
            if(col-1 >= 0 && map[row][col-1] == '#')
            {
                //turn 90
                dir = UP;
            }
            else
            {
                //move left
                col--;
            }
        }
        else if(dir == RIGHT)
        {
            
            //attempt to move right
            if(col+1 < map[0].size() && map[row][col+1] == '#')
            {
                //turn 90
                dir = DOWN;
            }
            else
            {
                //move right
                col++;
            }
        }
    }
    //escaped the loop
    return false;
}


int part2(std::istream &in)
{
     //guard tracking  
   int curRow = 0; int curCol = 0;
   int row = 0; int col = 0;
   int startRow = 0; int startCol = 0;
   Direction dir = UP;
    // parse input
   vector<vector<char>> map;
   vector<vector<char>> traveled;
    string line;
    while (in >> line)
    {
        vector<char> curline;
        curRow++;
        for (char c : line)
        {
            if(c == '^')
            {
                row = curRow;
                startRow = curRow;
                col = curCol;
                startCol = curCol;
            }
            curCol++;
            curline.push_back(c);
        }
        curCol = 0;
        map.push_back(curline);
    }
    traveled = map;
    cout << "row: " << row << " col: " << col << endl;
    //set of seen locations
    unordered_set<string> seen;
    int loops = 0;
    //while in bounds
    while(row >= 0 && row < map.size() && col >= 0 && col < map[0].size())
    {
        //if a new location
        if(seen.find(to_string(row) + "," + to_string(col)) == seen.end())
        {
            traveled[row][col] = '#';
            cout << "testing for loop at: " << row << " " << col << endl;
            if(isLoop(traveled, startRow, startCol))
            {
                cout << "found loop at: " << row << " " << col << endl;
                loops++;
            }
            cout << "no loop at: " << row << " " << col << endl;
            //reset traveled
            traveled[row][col] = map[row][col];
        }
        seen.insert(to_string(row) + "," + to_string(col));
        if(dir == UP)
        {
            //attempt to move up
            if(row-1 >= 0 && map[row-1][col] == '#')
            {
               // cout << "FAIL UP --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = RIGHT;
            }
            else
            {
               // cout << "UP --- row: " << row << " col: " << col << endl;
                //move up
                row--;
            }
        }
        else if(dir == DOWN)
        {
            
            //attempt to move down
            if(row+1 < map.size() && map[row+1][col] == '#')
            {
                //cout << "FAIL DOWN --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = LEFT;
            }
            else
            {
                //cout << "DOWN --- row: " << row << " col: " << col << endl;
                //move down
                row++;
            }
        }
        else if(dir == LEFT)
        {
            //attempt to move left
            if(col-1 >= 0 && map[row][col-1] == '#')
            {
                //cout << "FAIL LEFT --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = UP;
            }
            else
            {
               // cout << "LEFT --- row: " << row << " col: " << col << endl;
                //move left
                col--;
            }
        }
        else if(dir == RIGHT)
        {
            
            //attempt to move right
            if(col+1 < map[0].size() && map[row][col+1] == '#')
            {
               // cout << "FAIL RIGHT --- row: " << row << " col: " << col << endl;
                //turn 90
                dir = DOWN;
            }
            else
            {
              //  cout << "RIGHT --- row: " << row << " col: " << col << endl;
                //move right
                col++;
            }
        }
    }
    return loops;
}