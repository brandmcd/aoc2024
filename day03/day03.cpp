#include "day03.hpp"

using namespace std;

int part1(std::istream &in)
{
    // convert to string
    string line;
    string input;
    while (in >> line)
    {
        input += line;
    }
    int sum = 0;
    // go char by char
    //looking for mul(num1,num2)
    for (int i = 0; i < input.length(); i++)
    {
        try
        {
            // check if its ("mult("
            if (input.substr(i, 4) != "mul(")
            {
                throw std::invalid_argument("Not a mult");
            }

            // is mult
            i += 4;
            // if next are numbers
            string num1;
            while (isdigit(input[i]))
            {
                num1 += input[i];
                i++;
            }
            // if wasnt a num break
            if (num1 == "")
            {
                throw std::invalid_argument("Not a number");
            }
            // if next is a comma
            if (input[i] != ',')
            {
                throw std::invalid_argument("Not a comma");
            }
            i++;
            // if next are numbers
            string num2;
            while (isdigit(input[i]))
            {
                num2 += input[i];
                i++;
            }
            // if wasnt a num break
            if (num2 == "")
            {
                throw std::invalid_argument("Not a number");
            }
            //if next is a ')'
            if (input[i] != ')')
            {
                throw std::invalid_argument("Not a )");
            }
            //everything was good! mult the numbs and add to sum
            cout << "Num1: " << num1 << " Num2: " << num2 << '\n';
            sum += stoi(num1) * stoi(num2);
        }
        catch (std::exception &e)
        {
            //cout << "At i: "<< input[i] << " " << e.what() << '\n';
            // ignore these lol
        }
    }
    return sum;
}

int part2(std::istream &in)
{
    // convert to string
    string line;
    string input;
    while (in >> line)
    {
        input += line;
    }
    int sum = 0;
    // go char by char
    //looking for mul(num1,num2)
    bool enabled = true;
    for (int i = 0; i < input.length(); i++)
    {
        try
        {
            //first check do/don't
            if (input.substr(i, 7) == "don't()")
            {
                enabled = false;
                i += 7;
            }
            else if(input.substr(i,4) == "do()")
            {
                enabled = true;
                i += 4;
            }

            if (!enabled)
            {
                throw std::invalid_argument("Not enabled");
            }
            // check if its ("mult("
            if (input.substr(i, 4) != "mul(")
            {
                throw std::invalid_argument("Not a mult");
            }

            // is mult
            i += 4;
            // if next are numbers
            string num1;
            while (isdigit(input[i]))
            {
                num1 += input[i];
                i++;
            }
            // if wasnt a num break
            if (num1 == "")
            {
                throw std::invalid_argument("Not a number");
            }
            // if next is a comma
            if (input[i] != ',')
            {
                throw std::invalid_argument("Not a comma");
            }
            i++;
            // if next are numbers
            string num2;
            while (isdigit(input[i]))
            {
                num2 += input[i];
                i++;
            }
            // if wasnt a num break
            if (num2 == "")
            {
                throw std::invalid_argument("Not a number");
            }
            //if next is a ')'
            if (input[i] != ')')
            {
                throw std::invalid_argument("Not a )");
            }
            //everything was good! mult the numbs and add to sum
            cout << "Num1: " << num1 << " Num2: " << num2 << '\n';
            sum += stoi(num1) * stoi(num2);
        }
        catch (std::exception &e)
        {
            //cout << "At i: "<< input[i] << " " << e.what() << '\n';
            // ignore these lol
        }
    }
    return sum;
}