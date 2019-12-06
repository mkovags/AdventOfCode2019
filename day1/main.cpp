#include <iostream>
#include <assert.h>
#include <fstream>
#include <cctype>
#include <locale>

#define NDEBUG

using namespace std;

long fuel_needed_for_a_module(long mass)
{
    return mass/3 - 2;
}

long long calculate_fuel_requirements(const string & filename)
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
    assert( fuel_needed_for_a_module(12) == 2 );
    assert( fuel_needed_for_a_module(14) == 2 );
    assert( fuel_needed_for_a_module(1969) == 654 );
    assert( fuel_needed_for_a_module(100756) == 33583 );
    if(argc != 2)
    {
        cout << "Please specify the a file with the list of modules to calculate the fuel requirements" << endl;
        return 1;
    }

    cout << "Fuel requirements: " << calculate_fuel_requirements(argv[1]) << endl;
}