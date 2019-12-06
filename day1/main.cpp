#include <iostream>
#include <fstream>
#include <cctype>
#include <locale>

using namespace std;

long calculate_fuel_for_fuel(long mass)
{
    auto fuel_needed = mass / 3 - 2;
    if (fuel_needed <= 0)
    {
        return 0;
    }
    else
    {
        fuel_needed += calculate_fuel_for_fuel(fuel_needed);
    }
    return fuel_needed;
}

long fuel_needed_for_a_module(long mass)
{
    auto fuel_needed = mass/3 - 2;
    return calculate_fuel_for_fuel(fuel_needed) + fuel_needed;
}

long calculate_fuel_requirements(const string & filename)
{
    long long sum;
    ifstream infile(filename);
    string line;
    while (getline(infile, line))
    {
        try
        {
            sum += fuel_needed_for_a_module(stoll(line));
        }
        catch(invalid_argument & err)
        {
            if(line.size())
            {
                cout << "Invalid number: " << line << endl;
            }
        }
    }
    return sum;
}

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "Please specify the a file with the list of modules to calculate the fuel requirements" << endl;
        return 1;
    }
    auto fuel_requirements =  calculate_fuel_requirements(argv[1]);
    cout << "Fuel requirements: " << fuel_requirements << endl;
}