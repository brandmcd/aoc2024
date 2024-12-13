#include "day13.hpp"

using namespace std;

struct Button
{
    int x;
    int y;
};

class ClawMachine
{
private:
    Button buttonA;
    Button buttonB;
    pair<long long, long long> prizeLocation;

    // bool returns if the machine is possible (if not pair is 0,0)
    // pair returns how many times the buttons need to be pressed
    pair<bool, pair<int, int>> runMachine()
    {
        int Px = prizeLocation.first;
        int Py = prizeLocation.second;

        int det = buttonA.x * buttonB.y - buttonA.y * buttonB.x;
        if (det == 0)
        {
            // determinant is 0, the buttons are parallel
            return {false, {0, 0}};
        }

        // presses = (Py * Ax - Px * Ay) / det
        double bPresses = (Py * buttonA.x - Px * buttonA.y) / (double)det;
        double aPresses = (Px * buttonB.y - Py * buttonB.x) / (double)det;

        // Check if both moves are integers (this solution is possible)
        if (aPresses == static_cast<int>(aPresses) && bPresses == static_cast<int>(bPresses))
        {
            // check both are under 100
            if (aPresses < 0 || aPresses > 100 || bPresses < 0 || bPresses > 100)
            {
                return {false, {0, 0}};
            }
            return {true, {static_cast<int>(aPresses), static_cast<int>(bPresses)}};
        }

        return {false, {0, 0}};
    }

    
    //does not check if the presses are under 100
    pair<bool, pair<long long, long long>> runMachineNoCap()
    {
        long long Px = prizeLocation.first;
        long long Py = prizeLocation.second;

        long long det = buttonA.x * buttonB.y - buttonA.y * buttonB.x;
        if (det == 0)
        {
            // determinant is 0, the buttons are parallel
            return {false, {0, 0}};
        }

        // presses = (Py * Ax - Px * Ay) / det
        double bPresses = (Py * buttonA.x - Px * buttonA.y) / (double)det;
        double aPresses = (Px * buttonB.y - Py * buttonB.x) / (double)det;

        // Check if both moves are integers (this solution is possible)
        if (aPresses == static_cast<long long>(aPresses) && bPresses == static_cast<long long>(bPresses))
        {
            return {true, {static_cast<long long>(aPresses), static_cast<long long>(bPresses)}};
        }

        return {false, {0, 0}};
    }


    long long getMachineCost()
    {
        auto [possible, presses] = runMachine();
        if (!possible)
        {
            return 0;
        }
        return 3 * presses.first + presses.second;
    }

public:
    ClawMachine(int xA, int yA, int xB, int yB, long long prizeX, long long prizeY)
    {
        buttonA.x = xA;
        buttonA.y = yA;
        buttonB.x = xB;
        buttonB.y = yB;
        prizeLocation = {prizeX, prizeY};
    }

    int getCost()
    {
        return getMachineCost();
    }

    long long getMaxCost()
    {
        auto [possible, presses] = runMachineNoCap();
        if (!possible)
        {
            return 0;
        }
        return 3 * presses.first + presses.second;
    }
    void print()
    {
        cout << "Button A: X+" << buttonA.x << ", Y+" << buttonA.y << endl;
        cout << "Button B: X+" << buttonB.x << ", Y+" << buttonB.y << endl;
        cout << "Prize: X=" << prizeLocation.first << ", Y=" << prizeLocation.second << endl;
    }
};

long long part1(std::istream &in)
{
    vector<ClawMachine> machines;
    // parse input
    string line;
    while (getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }

        int xA, yA, xB, yB, prizeX, prizeY;
        sscanf(line.c_str(), "Button A: X+%d, Y+%d", &xA, &yA);
        getline(in, line);
        sscanf(line.c_str(), "Button B: X+%d, Y+%d", &xB, &yB);
        getline(in, line);
        sscanf(line.c_str(), "Prize: X=%d, Y=%d", &prizeX, &prizeY);

        ClawMachine machine(xA, yA, xB, yB, prizeX, prizeY);
        machines.push_back(machine);
        // Skip the blank line between machines
        getline(in, line);
    }

    long long sum = 0;
    for (auto machine : machines)
    {
      // cout << "Machine cost: " << machine.getCost() << endl;
       sum += machine.getCost();
    }
    return sum;
}

long long part2(std::istream &in)
{
    vector<ClawMachine> machines;
    // parse input
    string line;
    while (getline(in, line))
    {
        if (line.empty())
        {
            continue;
        }

        int xA, yA, xB, yB, prizeX, prizeY;
        sscanf(line.c_str(), "Button A: X+%d, Y+%d", &xA, &yA);
        getline(in, line);
        sscanf(line.c_str(), "Button B: X+%d, Y+%d", &xB, &yB);
        getline(in, line);
        sscanf(line.c_str(), "Prize: X=%d, Y=%d", &prizeX, &prizeY);

        ClawMachine machine(xA, yA, xB, yB,(prizeX+10000000000000), (prizeY+10000000000000));
        machines.push_back(machine);
        // Skip the blank line between machines
        getline(in, line);
    }

    long long sum = 0;
    for (auto machine : machines)
    {
       // machine.print();
      // cout << "Machine cost: " << machine.getCost() << endl;
       sum += machine.getMaxCost();
    }
    return sum;
}