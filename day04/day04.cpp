#include "day04.hpp"

using namespace std;

int part1(std::istream &in)
{
    // parse input
    //2d array of chars
    int row = 0;
    string line;
    char arr[140][140];
    while (in >> line)
    {
         for(int i = 0; i < line.length(); i++)
         {
           arr[row][i] = line[i];
         }
         row++;
    }
    int XMAScount = 0;
    //look for "XMAS" in every way
    for(int i = 0; i < line.length(); i++)
    {
        for(int j = 0; j < line.length(); j++)
        {
            //check horiz norm
            if(arr[i][j] == 'X' && j<line.length()-3)
            {
            if(arr[i][j+1] == 'M' && arr[i][j+2] == 'A' && arr[i][j+3] == 'S')
            {
                cout << "found horiz norm at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check horiz backward
            if(arr[i][j] == 'X' && j>=3)
            {
            if(arr[i][j-1] == 'M' && arr[i][j-2] == 'A' && arr[i][j-3] == 'S')
            {
                cout << "found horiz backward at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check vert down
            if(arr[i][j] == 'X' && i<line.length()-3)
            {
            if(arr[i+1][j] == 'M' && arr[i+2][j] == 'A' && arr[i+3][j] == 'S')
            {
                cout << "found vert down at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check vert up
            if(arr[i][j] == 'X' && i>=3)
            {
            if(arr[i-1][j] == 'M' && arr[i-2][j] == 'A' && arr[i-3][j] == 'S')
            {
                cout << "found vert up at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check horiz down-right
            if(arr[i][j] == 'X' && j<line.length()-3 && i<line.length()-3)
            {
            if(arr[i+1][j+1] == 'M' && arr[i+2][j+2] == 'A' && arr[i+3][j+3] == 'S')
            {
                cout << "found horiz down-right at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check horiz up-right
            if(arr[i][j] == 'X' && j<line.length()-3 && i>=3)
            {
            if(arr[i-1][j+1] == 'M' && arr[i-2][j+2] == 'A' && arr[i-3][j+3] == 'S')
            {
                cout << "found horiz up-right at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check horiz down-left
            if(arr[i][j] == 'X' && j>=3 && i<line.length()-3)
            {
            if(arr[i+1][j-1] == 'M' && arr[i+2][j-2] == 'A' && arr[i+3][j-3] == 'S')
            {
                cout << "found horiz down-left at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
            //check horiz up-left
            if(arr[i][j] == 'X' && j>=3 && i>=3)
            {
            if(arr[i-1][j-1] == 'M' && arr[i-2][j-2] == 'A' && arr[i-3][j-3] == 'S')
            {
                cout << "found horiz up-left at: " << i << " " << j << endl;
                XMAScount++;
            }
            }
        }
    }
    return XMAScount;
}

int part2(std::istream &in)
{
    // parse input
    //2d array of chars
    int row = 0;
    string line;
    char arr[140][140];
    while (in >> line)
    {
         for(int i = 0; i < line.length(); i++)
         {
           arr[row][i] = line[i];
         }
         row++;
    }
    int XMAScount = 0;
    //either has M . S or S . M or M . M or S . S
    //           . A .    . A .    . A .    . A .
    //           M . S    S . M    S . S    M . M
    for(int i = 0; i < line.length() -2; i++)
    {
        for(int j = 0; j < line.length()-2; j++) //stop 2 before end of row
        {
            if(arr[i+1][j+1] == 'A')
            {
                if(arr[i][j] == 'M' && arr[i][j+2] == 'S' && arr[i+2][j] == 'M' && arr[i+2][j+2] == 'S')
                {
                    XMAScount++;
                }
                else if(arr[i][j] == 'S' && arr[i][j+2] == 'M' && arr[i+2][j] == 'S' && arr[i+2][j+2] == 'M')
                {
                    XMAScount++;
                }
                else if(arr[i][j] == 'M' && arr[i][j+2] == 'M' && arr[i+2][j] == 'S' && arr[i+2][j+2] == 'S')
                {
                    XMAScount++;
                }
                else if(arr[i][j] == 'S' && arr[i][j+2] == 'S' && arr[i+2][j] == 'M' && arr[i+2][j+2] == 'M')
                {
                    XMAScount++;
                }
            }
        }
    }
    return XMAScount;
}