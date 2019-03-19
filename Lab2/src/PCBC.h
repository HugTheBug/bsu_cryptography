#pragma once

#include "Encryption.h"

namespace Encryption {
	std::pair<Bytes, bool> encryptPCBC(const Bytes &inKey, const Bytes &inIV, const Bytes &inPlainText);
	std::pair<Bytes, bool> decryptPCBC(const Bytes &inKey, const Bytes &inIV, const Bytes &inCipherText);
};