#pragma once
#include "LFSR.h"

#include <string>

namespace Encryption {
	class GeffeGenerator {
		LFSR lfsr1;
		LFSR lfsr2;
		LFSR lfsr3;
	public:
		GeffeGenerator(const LFSR &lfsr1, const LFSR &lfsr2, const LFSR &lfsr3);

		bool step();
	};
};