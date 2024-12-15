#include "day14.hpp"
#include <map>

using namespace std;

int GRID_WIDTH = 101;
int GRID_HEIGHT = 103;
class Robot
{
    private:
        pair<int, int> location;
        pair<int, int> velocity;

        void move()
        {
            location.first += velocity.first;
            location.second += velocity.second;

            //wrap around
            location.first = (location.first + GRID_WIDTH) % GRID_WIDTH;
            location.second = (location.second + GRID_HEIGHT) % GRID_HEIGHT;
        }

    public:
        Robot(int x, int y, int vx, int vy)
        {
            location = {x, y};
            velocity = {vx, vy};
        }

        void tick()
        {
            move();
        }

        pair<int, int> getLocation()
        {
            return location;
        }
};

void printGrid(vector<Robot> &robots)
{
     //map of robots on each tile
    map<pair<int, int>, int> grid; 
    for (auto &r : robots)
    {
        auto loc = r.getLocation();
        grid[loc]++;
    }

    //print grid
    for (int y = 0; y < GRID_HEIGHT; y++)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (grid[{x, y}] > 0)
            {
                cout << grid[{x, y}];
            }
            else
            {
                cout << ".";
            }
        }
        cout << endl;
    }

    //make a line at the bottom
    for(int i = 0; i < GRID_WIDTH; i++)
    {
        cout << "-";
    }
    cout << endl;
}

int getSafetyScore(vector<Robot> &robots)
{
    //map of robots on each tile
    map<pair<int, int>, int> grid; 
    for (auto &r : robots)
    {
        auto loc = r.getLocation();
        grid[loc]++;
    }

    //count the number of robots on each tile
    int scoreQ1 = 0;
    int scoreQ2 = 0;
    int scoreQ3 = 0;
    int scoreQ4 = 0;
    for (auto &tile : grid)
    {
        int x = tile.first.first;
        int y = tile.first.second;
        //Q1 
        if(x < GRID_WIDTH / 2 && y < GRID_HEIGHT / 2)
        {
            scoreQ1+= tile.second;
        }
        //Q2 
        if(x > GRID_WIDTH / 2 && y < GRID_HEIGHT / 2)
        {
            scoreQ2+= tile.second;
        }
        //Q3
        if(x < GRID_WIDTH / 2 && y > GRID_HEIGHT / 2)
        {
            scoreQ3+= tile.second;
        }
        //Q4
        if(x > GRID_WIDTH / 2 && y > GRID_HEIGHT / 2)
        {
            scoreQ4+= tile.second;
        }
    }

    cout << "Q1: " << scoreQ1 << endl;
    cout << "Q2: " << scoreQ2 << endl;
    cout << "Q3: " << scoreQ3 << endl;
    cout << "Q4: " << scoreQ4 << endl;
    return scoreQ1 * scoreQ2 * scoreQ3 * scoreQ4;
}

long long part1(std::istream &in)
{
    vector<Robot> robots;
    // parse input
    string line;
    while (getline(in, line))
    {
        int x, y, xV, yV;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &xV, &yV);
        Robot r(x, y, xV, yV);
        robots.push_back(r);
    }

    //printGrid(robots);

    //move robots 100 times
    for (int i = 0; i < 100; i++)
    {
        for (auto &r : robots)
        {
            r.tick();
        }
        //printGrid(robots);
    }

   // printGrid(robots);

    //get the safety scores 
    return getSafetyScore(robots);
}

bool checkForPicture(vector<Robot> &robots)
{
    //map of robots on each tile
    map<pair<int, int>, int> grid; 
    for (auto &r : robots)
    {
        auto loc = r.getLocation();
        grid[loc]++;
    }

    //if every robot is in a unique tile, then we have a picture?
    if(grid.size() == robots.size())
    {
        return true;
    }
    return false;
}

long long part2(std::istream &in)
{
    vector<Robot> robots;
    // parse input
    string line;
    while (getline(in, line))
    {
        int x, y, xV, yV;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &xV, &yV);
        Robot r(x, y, xV, yV);
        robots.push_back(r);
    }

    int count = 0;
    int time = 0;
    bool picture = false;
    while(count < 4)
    {
        picture = checkForPicture(robots);
        if(picture)
        {
            printGrid(robots);
            count++;
            cout << endl  << "Time: " << time << endl;
        }
        for (auto &r : robots)
        {
            r.tick();
        }
        time++;
    }

    printGrid(robots);

    return time;
}