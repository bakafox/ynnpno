#include <gtest/gtest.h>
#include "../include/bitset.h"

using namespace std;



TEST(bitset_test, my_test) {
    BitArray test1;
    ASSERT_TRUE(test1.empty());

    BitArray test2(5, true);
    ASSERT_FALSE(test2.empty());
    ASSERT_EQ(test2.size(), 5);
    ASSERT_EQ(test2.to_string(), "11111");

    BitArray test3(test2);
    ASSERT_EQ(test3, test2);

    test3.resize(8, false);
    ASSERT_EQ(test3.size(), 8);
    ASSERT_EQ(test3.to_string(), "11111000");
    test3.set(5, true);
    ASSERT_EQ(test3.to_string(), "11111100");
    test3.reset(4);
    test3.reset(5);
    ASSERT_EQ(test3.to_string(), "11110000");

    test3.resize(5);
    ASSERT_EQ((test2 & test3).to_string(), "11110");
    ASSERT_EQ((test2 | test3).to_string(), "11111");
    ASSERT_EQ((test2 ^ test3).to_string(), "00001");
    ASSERT_EQ((~test3).to_string(), "00001");

    ASSERT_EQ((test3 << 3).to_string(), "11000");
    ASSERT_EQ((test3 >> 2).to_string(), "00111");

    ASSERT_EQ(test2, test2);
    ASSERT_NE(test2, test3);

    BitArray test4(29);
    test4.set();
    ASSERT_TRUE(test4.any());
    ASSERT_FALSE(test4.none());
    test4.reset();
    ASSERT_FALSE(test4.any());
    ASSERT_TRUE(test4.none());

    test4.set(2);
    test4.set(3);
    test4.set(6);
    test4.set(8);
    ASSERT_EQ(test3.count(), 4);

    test1.push_back(true);
    ASSERT_EQ(test1.size(), 1);
    ASSERT_EQ(test1.to_string(), "1");

    test1.clear();
    ASSERT_EQ(test1.size(), 0);

    BitArray test5(3, true);
    test5.resize(100);
    test5.set();
    ASSERT_EQ(test5.to_string(), "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
    test5.reset();
    ASSERT_EQ(test5.to_string(), "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BitArray test6(100, true);
    for (int t = 0; t < 100; t += 3) {
        test6.set(t, false);
        test5.set(t / 2, true);
    }
    ASSERT_EQ((test6 & test5).to_string(), "0100100100100100100100100100100100100100100100100100000000000000000000000000000000000000000000000000");
    ASSERT_EQ((test6 | test5).to_string(), "1111111111111111111111111111111111111111111111111110110110110110110110110110110110110110110110110110");
    ASSERT_EQ((test6 ^ test5).to_string(), "1011011011011011011011011011011011011011011011011010110110110110110110110110110110110110110110110110");
}
