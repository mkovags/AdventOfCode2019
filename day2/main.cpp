#include <iostream>
#include <assert.h>
#include <fstream>
#include <cctype>
#include <vector>
#include <sstream>

#define NDEBUG

using namespace std;

vector<int> load_opcodes(const string & filename)
{
    vector<int> opcodes;
    ifstream infile(filename);
    ostringstream ss;
    char c;

    while (infile >> c)
    {
        if(c == ',')
        {
            opcodes.push_back(stoll(ss.str()));
            ss.str("");
        }
        else
        {
            ss << c;
        }
    }
    return opcodes;
}

void run_machine(vector<int> & opcodes)
{
    int pos = 0;
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

int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "Please specify the a file with the list of modules to calculate the fuel requirements" << endl;
        return 1;
    }

    auto opcodes=load_opcodes(argv[1]);
    opcodes[1]=12;
    opcodes[2]=2;
    run_machine(opcodes);

    cout << opcodes[0] << endl;
}