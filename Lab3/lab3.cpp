// lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "LFSR.h"
#include "GeffeGenerator.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace Encryption;

int main()
{
	LFSR lfsr1{ 0b10101000000000000000001u, 0x63E283u, 23 };
	LFSR lfsr2{ 0b11010000000000000000000000001u, 0x18854530u, 29 };
	LFSR lfsr3{ 0b1110000000000000000000000000001u, 0x73995D0Eu, 31 };
	GeffeGenerator gen{ lfsr1, lfsr2, lfsr3 };

	ofstream out("bin.txt", ios_base::binary);
	const size_t file_size = 10e7;

	size_t bit = 7;
	char value = 0;
	for (size_t i = 0; i < file_size; i++) {
		value |= gen.step() << bit;
		if (!bit) {
			out.write(&value, 1);
			bit = 7;
			value = 0;
		}
		else {
			bit--;
		}
	}
	if (value) {
		out.write(&value, 1);
	}
	out.close();
}
