#include "GeffeGenerator.h"

using namespace std;
using namespace Encryption;

GeffeGenerator::GeffeGenerator(const LFSR &lfsr1, const LFSR &lfsr2, const LFSR &lfsr3)
	: lfsr1{ lfsr1 }, lfsr2{ lfsr2 }, lfsr3{ lfsr3 } {}

bool GeffeGenerator::step() {
	const bool s1 = lfsr1.shift();
	const bool s2 = lfsr2.shift();
	const bool s3 = lfsr3.shift();

	return (s1 & s2) ^ ((1 ^ s1) & s3);
}