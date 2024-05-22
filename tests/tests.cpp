#include "../include/bitset.h"
#include <assert.h>

using namespace std;



void doTests() {
	BitArray test1;
	assert(test1.empty());

	BitArray test2(5, true);
	assert(!test2.empty());
	assert(test2.size() == 5);
	assert(test2.to_string() == "11111");

	BitArray test3(test2);
	assert(test3 == test2);

	test3.resize(8, false);
	assert(test3.size() == 8);
	assert(test3.to_string() == "11111000");
	test3.set(5, true);
	assert(test3.to_string() == "11111100");
	test3.reset(4);
	test3.reset(5);
	assert(test3.to_string() == "11110000");

	test3.resize(5);
	assert((test2 & test3).to_string() == "11110");
	assert((test2 | test3).to_string() == "11111");
	assert((test2 ^ test3).to_string() == "00001");
	assert((~test3).to_string() == "00001");

	assert((test3 << 3).to_string() == "11000");
	assert((test3 >> 2).to_string() == "00111");

	assert(test2 == test2);
	assert(test2 != test3);

	BitArray test4(29);
	test4.set();
	assert(test4.any() == true);
	assert(test4.none() == false);
	test4.reset();
	assert(test4.any() == false);
	assert(test4.none() == true);

	test4.set(2);
	test4.set(3);
	test4.set(6);
	test4.set(8);
	assert(test3.count() == 4);

	test1.push_back(true);
	assert(test1.size() == 1);
	assert(test1.to_string() == "1");

	test1.clear();
	assert(test1.size() == 0);

	BitArray test5(3, true);
	test5.resize(100);
	test5.set();
	assert(test5.to_string() == "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
	test5.reset();
	assert(test5.to_string() == "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
	BitArray test6(100, true);
	for (int t = 0; t < 100; t+=3) {
		test6.set(t, false);
		test5.set(t/2, true);
	}
	assert((test6 & test5).to_string() == "0100100100100100100100100100100100100100100100100100000000000000000000000000000000000000000000000000");
	assert((test6 | test5).to_string() == "1111111111111111111111111111111111111111111111111110110110110110110110110110110110110110110110110110");
	assert((test6 ^ test5).to_string() == "1011011011011011011011011011011011011011011011011010110110110110110110110110110110110110110110110110");
}


int main() {
    doTests();

	return 0; // All tests completed successfully!
}
