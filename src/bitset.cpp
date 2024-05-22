#include "../include/bitset.h"

using namespace std;



BitArray::BitArray() = default;
BitArray::~BitArray() = default;

// Builds a bitset containing a specified amount of bits,
// first sizeof(long) bits may be initialised using value parameter
BitArray::BitArray(int num_bits, unsigned long value) {
	bitArray.resize(num_bits, value);
}

// Swaps values of 2 bitsets
void BitArray::swap(BitArray& b) {
	std::swap(bitArray, b.bitArray);
}

// Copies and moves bitset bits
BitArray::BitArray(const BitArray& b) {
	bitArray = b.bitArray;
}
BitArray& BitArray::operator=(const BitArray &b) {
	bitArray = b.bitArray;
	return *this;
}

// Copies and moves bitset bits (MOVE SEMANTICS)
BitArray::BitArray(BitArray&& b) noexcept {
	bitArray = std::move(b.bitArray);
}
BitArray& BitArray::operator=(BitArray&& b) noexcept {
	bitArray = std::move(b.bitArray);
	return *this;
}

// Changes bitset size,
// initializes new bits with value if bitset exapnds
void BitArray::resize(int num_bits, bool value) {
	bitArray.resize(num_bits, value);
}
// Clears bitset
void BitArray::clear() {
	bitArray.clear();
}
// Adds a bit in the end of bitset
void BitArray::push_back(bool bit) {
	bitArray.push_back(bit);
}

// Bitwise bitset operations,
// only work on 2 bitsets of the same size
BitArray& BitArray::operator&=(const BitArray& b) {
	if (bitArray.size() != b.bitArray.size()) {
		perror("BitArray sizes must be the same for bitwise AND.");
	}
	else {
		for (int i = 0; i < bitArray.size(); i++) {
			bitArray[i] = bitArray[i] && b.bitArray[i];
		}
	}
	return *this;
}
BitArray& BitArray::operator|=(const BitArray& b) {
	if (bitArray.size() != b.bitArray.size()) {
		perror("BitArray sizes must be the same for bitwise OR.");
	}
	else {
		for (int i = 0; i < bitArray.size(); i++) {
			bitArray[i] = bitArray[i] || b.bitArray[i];
		}
	}
	return *this;
}
BitArray& BitArray::operator^=(const BitArray& b) {
	if (bitArray.size() != b.bitArray.size()) {
		perror("BitArray sizes must be the same for bitwise XOR.");
	}
	else {
		for (int i = 0; i < bitArray.size(); i++) {
			bitArray[i] = (bitArray[i] != b.bitArray[i]);
		}
	}
	return *this;
}

// Bitshift with zero fill operations
BitArray& BitArray::operator<<=(int n) {
	for (int i = 0; i < bitArray.size() - n; i++) {
		bitArray[i + n] = bitArray[i];
	}
	for (int j = 0; j < n; j++) {
		bitArray[j + bitArray.size() - n] = false;
	}
	return *this;
}
BitArray& BitArray::operator>>=(int n) {
	for (int i = bitArray.size() - n - 1; i > 0; i--) {
		bitArray[i + n] = bitArray[i];
	}
	for (int j = 0; j < n; j++) {
		bitArray[j] = false;
	}
	return *this;
}
BitArray BitArray::operator<<(int n) {
	BitArray newBitArray(*this);
	newBitArray <<= n;
	return newBitArray;
}
BitArray BitArray::operator>>(int n) {
	BitArray newBitArray(*this);
	newBitArray >>= n;
	return newBitArray;
}

// Sets nth bit of bitset to val
BitArray& BitArray::set(int n, bool val) {
	if (n < 0 || n >= bitArray.size()) {
		perror("Bit index out of range.");
	}
	else {
		bitArray[n] = val;
	}
	return *this;
}
// Fills whole bitset with true
BitArray& BitArray::set() {
	for (int i = 0; i < bitArray.size(); i++) {
		bitArray[i] = true;
	}
	return *this;
}

// Sets nth bit of bitset to false
BitArray& BitArray::reset(int n) {
	if (n < 0 || n >= bitArray.size()) {
		perror("Bit index out of range.");
	}
	else {
		bitArray[n] = false;
	}
	return *this;
}
// Fills whole bitset with false
BitArray& BitArray::reset() {
	for (int i = 0; i < bitArray.size(); i++) {
		bitArray[i] = false;
	}
	return *this;
}

// true, if bitset contains a true bit
bool BitArray::any() const {
	for (int i = 0; i < bitArray.size(); i++) {
		if (bitArray[i]) {
			return true;
		}
	}
	return false;
}
// true, if all bitset bits are false
bool BitArray::none() const {
	for (int i = 0; i < bitArray.size(); i++) {
		if (bitArray[i]) {
			return false;
		}
	}
	return true;
}
// Bit inversion
BitArray BitArray::operator~() const {
	BitArray newBitArray(bitArray.size());
	for (int i = 0; i < bitArray.size(); i++) {
		newBitArray.set(i, !bitArray[i]);
	}
	return newBitArray;
}
// Counts amount of non-zero bits
int BitArray::count() const {
	int count = 0;
	for (int i = 0; i < bitArray.size(); i++) {
		if (bitArray[i]) {
			count++;
		}
	}
	return count;
}

// Returns bit value by index i
bool BitArray::operator[](int i) const {
	if (i < 0 || i >= bitArray.size()) {
		perror("Bit index out of range.");
	}
	return bitArray[i];
}

// Returns bitset size
int BitArray::size() const {
	return bitArray.size();
}
// Returns whether the bitset's size is zero
bool BitArray::empty() const {
	return bitArray.empty();
}

// Returns string representation of a bitset
std::string BitArray::to_string() const {
	std::string bitArrayAsString;
	for (int i = 0; i < bitArray.size(); i++) {
		bitArrayAsString += (char)('0' + bitArray[i] * 1);
	}
	return bitArrayAsString;
}

// Checks whether 2 bitsets are equals
bool operator==(const BitArray& a, const BitArray& b) {
	return a.to_string() == b.to_string();
}
// Checks whether 2 bitsets are not equals
bool operator!=(const BitArray& a, const BitArray& b) {
	return a.to_string() != b.to_string();
}

// Inline bitset operators, work the same as bitset operators from above
BitArray operator&(const BitArray& b1, const BitArray& b2) {
	BitArray newBitArray(b1.size());

	if (b1.size() != b2.size()) {
		perror("BitArray sizes must be the same for bitwise AND.");
	}
	else {
		for (int i = 0; i < b1.size(); i++) {
			newBitArray.set(i, b1[i] && b2[i]);
		}
	}
	return newBitArray;
}
BitArray operator|(const BitArray& b1, const BitArray& b2) {
	BitArray newBitArray(b1.size());

	if (b1.size() != b2.size()) {
		perror("BitArray sizes must be the same for bitwise OR.");
	}
	else {
		for (int i = 0; i < b1.size(); i++) {
			newBitArray.set(i, b1[i] || b2[i]);
		}
	}
	return newBitArray;
}
BitArray operator^(const BitArray& b1, const BitArray& b2) {
	BitArray newBitArray(b1.size());

	if (b1.size() != b2.size()) {
		perror("BitArray sizes must be the same for bitwise XOR.");
	}
	else {
		for (int i = 0; i < b1.size(); i++) {
			newBitArray.set(i, b1[i] != b2[i]);
		}
	}
	return newBitArray;
}
