//
// pch.cpp
//

#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

class Bitset {
    vector<bool> bits;

public:
    Bitset(int n) : bits(n) {}

    //чи м≥ститьс€
    bool contains(int x) const {
        return bits[x];
    }

    //додаванн€
    void add(int x) {
        bits[x] = true;
    }

    //видаленн€
    void remove(int x) {
        bits[x] = false;
    }

    //об'Їднанн€
    void union_with(Bitset& other) {
        for (int i = 0; i < bits.size(); i++) {
            bits[i] = bits[i] || other.bits[i];
        }
    }

    //перетин
    void intersect_with(Bitset& other) {
        for (int i = 0; i < bits.size(); i++) {
            bits[i] = bits[i] && other.bits[i];
        }
    }

    //р≥зниц€
    void difference_with(Bitset& other) {
        for (int i = 0; i < bits.size(); i++) {
            bits[i] = bits[i] && !other.bits[i];
        }
    }

    //розщепленн€
    Bitset split(int x) const {
        Bitset result(bits.size());

        for (int i = 0; i < x; i++) {
            result.bits[i] = bits[i];
        }

        for (int i = x; i < bits.size(); i++) {
            result.bits[i] = false;
        }

        return result;
    }

    //найменший елемент
    int smallest_element(int start = 0) const {
        for (int i = start; i < bits.size(); i++) {
            if (bits[i]) {
                return i;
            }
        }

        return -1;
    }

    //розм≥рн≥сть
    int size() const {
        return bits.size();
    }
};

int test() {
    Bitset set(10);

    set.add(3);
    set.add(5);
    set.add(7);

    cout << "Set contains 5: " << set.contains(5) << endl;
    cout << "Set contains 6: " << set.contains(6) << endl;

    set.remove(5);

    Bitset other_set(10);
    other_set.add(2);
    other_set.add(3);
    other_set.add(7);

    set.union_with(other_set);
    cout << "Union with {2, 3, 7}: ";
    for (int i = 0; i < set.size(); i++) {
        cout << set.contains(i) << " ";
    }
    cout << endl;

    set.intersect_with(other_set);
    cout << "Intersection with {2, 3, 7}: ";
    for (int i = 0; i < set.size(); i++) {
        cout << set.contains(i) << " ";
    }
    cout << endl;

    set.difference_with(other_set);
    cout << "Difference with {2, 3, 7}: ";
    for (int i = 0; i < set.size(); i++) {
        cout << set.contains(i) << " ";
    }
    cout << endl;

    Bitset split_set = set.split(3);
    cout << "Split at 3: ";
    for (int i = 0; i < set.size(); i++) {
        cout << set.contains(i) << " ";
    }
    cout << endl;
    cout << "Resulting split set: ";
    for (int i = 0; i < split_set.size(); i++) {
        cout << split_set.contains(i) << " ";
    }
    cout << endl;

    cout << "Smallest element: " << set.smallest_element() << endl;

    return 0;
}


TEST(BitsetTest, Contains) {
    Bitset b(10);
    b.add(3);
    b.add(7);
    EXPECT_TRUE(b.contains(3));
    EXPECT_TRUE(b.contains(7));
    EXPECT_FALSE(b.contains(5));
}

TEST(BitsetTest, AddRemove) {
    Bitset b(10);
    b.add(3);
    b.add(7);
    EXPECT_TRUE(b.contains(3));
    EXPECT_TRUE(b.contains(7));
    b.remove(3);
    EXPECT_FALSE(b.contains(3));
    EXPECT_TRUE(b.contains(7));
}

TEST(BitsetTest, Union) {
    Bitset b1(10);
    Bitset b2(10);
    b1.add(3);
    b1.add(7);
    b2.add(5);
    b2.add(7);
    b1.union_with(b2);
    EXPECT_TRUE(b1.contains(3));
    EXPECT_TRUE(b1.contains(5));
    EXPECT_TRUE(b1.contains(7));
}

TEST(BitsetTest, Intersection) {
    Bitset b1(10);
    Bitset b2(10);
    b1.add(3);
    b1.add(7);
    b2.add(5);
    b2.add(7);
    b1.intersect_with(b2);
    EXPECT_FALSE(b1.contains(3));
    EXPECT_FALSE(b1.contains(5));
    EXPECT_TRUE(b1.contains(7));
}

TEST(BitsetTest, Difference) {
    Bitset b1(10);
    Bitset b2(10);
    b1.add(3);
    b1.add(7);
    b2.add(5);
    b2.add(7);
    b1.difference_with(b2);
    EXPECT_TRUE(b1.contains(3));
    EXPECT_FALSE(b1.contains(5));
    EXPECT_FALSE(b1.contains(7));
}


TEST(BitsetTest, Split) {
    Bitset b(5);
    b.add(1);
    b.add(3);

    Bitset b1 = b.split(2);
    Bitset b2 = b.split(4);

    EXPECT_TRUE(b1.contains(1));
    EXPECT_FALSE(b1.contains(3));
    EXPECT_TRUE(b2.contains(1));
    EXPECT_TRUE(b2.contains(3));
}

TEST(BitsetTest, SmallestElement) {
    Bitset b(5);
    b.add(1);
    b.add(3);

    int smallest1 = b.smallest_element();
    int smallest2 = b.smallest_element(2);

    EXPECT_EQ(smallest1, 1);
    EXPECT_EQ(smallest2, 3);
}

TEST(BitsetTest, Size) {
    Bitset b(10);
    EXPECT_EQ(b.size(), 10);
    b.add(3);
    b.add(7);
    EXPECT_EQ(b.size(), 10);
}
