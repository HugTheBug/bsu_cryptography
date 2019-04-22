#pragma once

#include <string>

namespace Encryption {
	class LFSR {
		using state_type = uint32_t;

		state_type mask;
		state_type polynomial;
		state_type state;

	public:
		LFSR(const state_type polynomial, const state_type initialState, const int length);

		bool shift();
	};
};
