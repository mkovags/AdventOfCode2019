#include "common.h"

int main(int argc, char ** argv)
{
    if(argc != 3)
    {
        cout << "Please specify the a file with the comma-separated opcodes, and the expected output" << endl;
        return 1;
    }

    auto loaded_opcodes=load_opcodes(argv[1]);
    auto expected_output=atol(argv[2]);

    for(int verb=0; verb!=99; ++verb)
    {
        for(int noun=0; noun!=99; ++noun)
        {
            auto opcodes = loaded_opcodes;
            opcodes[1] = noun;
            opcodes[2] = verb;

            run_machine(opcodes);

            if(opcodes[0] == expected_output)
            {
                cout << "Found output for verb=" << verb << " noun=" << noun << endl
                << "Answer: " << 100 * noun + verb << endl;
                ;
                return 0;
            }
        }
    }

    cout << "No verb/noun found for expected output" << endl;
}