#include <iostream>
#include <cmath>
#include <vector>
#include <assert.h>

using namespace std;

/// integer power
long powi(long x, long y)
{
    if(y < 1 ) return 1;
    if(y == 1) return x;
    return x * powi(x,y-1);
}

unsigned getNumberLength(unsigned number)
{
    return floor(log10(number)) + 1;
}

int getNthDigit(int number, int position)
{
    int size = getNumberLength(number);
    position = size - position - 1;
    int t1, ret;
    t1 = powi(10, position+1);
    ret = number % t1;
    ret /= powi(10,position);
    return ret;
}

bool twoDigitsAreTheSame(unsigned number)
{
    auto length=getNumberLength(number);
    for(int i = 0; i!=length - 1; ++i)
    {
        if (getNthDigit(number,i) == getNthDigit(number,i +1)) return true;
    }
    return false;
}

bool digitsNeverDecrease(unsigned number)
{
    auto length=getNumberLength(number);
    unsigned last = 0;
    for(int i = 0; i!=length; ++i)
    {
        auto current = getNthDigit(number,i);
        if (current < last) return false;
        last = current;
    }
    return true;
}

vector<unsigned> getPasswordsMatchingCriteria(unsigned lowerBound, unsigned upperBound)
{
    vector<unsigned> ret;
    for(auto i=lowerBound; i!=upperBound; ++i)
    {
        if(!twoDigitsAreTheSame(i)) continue;
        if(!digitsNeverDecrease(i)) continue;
        ret.push_back(i);
    }
    return ret;
}

void runTests()
{
    assert( getNthDigit(12345,1) == 2 );
    assert( twoDigitsAreTheSame(126667));
    assert(!twoDigitsAreTheSame(123457));
    assert( digitsNeverDecrease(123457));
    assert(!digitsNeverDecrease(666555));
}

int main(int argc, char ** argv)
{
    runTests();
    if(argc != 3)
    {
        cout << "You must specify the lower and upper bounds. Example:" << endl
             << argv[0] << " 146810 612564";
        return 1;
    }

    unsigned lowerBound = atoi(argv[1]);
    unsigned upperBound = atoi(argv[2]);

    auto passwords = getPasswordsMatchingCriteria(lowerBound, upperBound);
    cout << "The following passwords were found:";
    for (const auto & e : passwords)
    {
        cout << " -" <<  e << endl;
    }
    cout << "Number of passwords: " << passwords.size() << endl;
}