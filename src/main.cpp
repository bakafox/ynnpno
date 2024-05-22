#include "../include/bitset.h"
#include <iostream>

using namespace std;



int main() {
    cout << '\n';

    BitArray smiley1(8);
    smiley1.set();
    smiley1.reset(0).reset(7);

    cout << (~smiley1).to_string() << '\n';
    cout << smiley1.to_string() << '\n';

    BitArray smiley2(smiley1);
    smiley2.reset(2).reset(7-2);

    cout << smiley2.to_string() << '\n';
    cout << smiley1.to_string() << '\n';

    smiley2.clear();
    smiley2.resize(8);
    smiley2.set(0).set(3).set(4).set(7);

    cout << (smiley1 & (~smiley2)).to_string() << '\n';

    smiley2 = smiley1;
    smiley1.reset(2).reset(7-2);

    cout << smiley1.to_string() << '\n';
    cout << smiley2.to_string() << '\n';
    cout << (~smiley2).to_string() << '\n';

    cout << '\n';
    return 0;
}
