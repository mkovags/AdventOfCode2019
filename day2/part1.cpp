#include "common.h"

using namespace std;


int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        cout << "Please specify the a file with the comma-separated opcodes" << endl;
        return 1;
    }

    auto opcodes=load_opcodes(argv[1]);
    opcodes[1]=12;
    opcodes[2]=2;
    run_machine(opcodes);

    cout << opcodes[0] << endl;
}