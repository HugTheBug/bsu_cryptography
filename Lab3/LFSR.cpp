#include "LFSR.h"

using namespace std;
using namespace Encryption;

LFSR::LFSR(const state_type polynomial, const state_type initialState, const int length)
	: polynomial{ polynomial }, state{ initialState }, mask{ 1u << (length - 1) }{
}

bool LFSR::shift() {
	if (state & 1) {
		state = ((state ^ polynomial) >> 1) | mask;
		return 1;
	}
	else {
		state >>= 1;
		return 0;
	}
}