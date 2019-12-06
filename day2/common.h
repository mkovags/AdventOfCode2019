#ifndef ADVENTOFCODE2019_COMMON_H
#define ADVENTOFCODE2019_COMMON_H

#include <iostream>
#include <assert.h>
#include <fstream>
#include <cctype>
#include <vector>
#include <sstream>

using namespace std;

vector<long> load_opcodes(const string & filename)
{
    vector<long> opcodes;
    ifstream infile(filename);
    ostringstream ss;
    char c;

    while (infile >> c)
    {
        if(c == ',')
        {
            opcodes.push_back(stol(ss.str()));
            ss.str("");
        }
        else
        {
            ss << c;
        }
    }
    return opcodes;
}

void run_machine(vector<long> & opcodes)
{
    long pos = 0;
    while(true)
    {
        if(opcodes[pos]==1)
        {
            opcodes[opcodes[pos+3]] = opcodes[opcodes[pos+1]] + opcodes[opcodes[pos+2]];
        }
        else if(opcodes[pos]==2)
        {
            opcodes[opcodes[pos+3]] = opcodes[opcodes[pos+1]] * opcodes[opcodes[pos+2]];
        }
        else if(opcodes[pos]==99)
        {
            return;
        }

        pos+=4;
    }
}

#endif //ADVENTOFCODE2019_COMMON_H
