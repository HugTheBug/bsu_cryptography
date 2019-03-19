#include "PCBC.h"

extern "C" {
	#include "aes.h"
}

#include <algorithm>
#include <random>

using namespace Encryption;
using namespace std;

namespace {
	const size_t roundKeySize = AES_ROUND_KEY_SIZE;
	const size_t blockSize = AES_BLOCK_SIZE;
	const size_t keySizePCBC = AES_BLOCK_SIZE;

	const auto xorFunc = [](const auto a, const auto b) { return a ^ b; };

	template <class ForwardIterator>
	void randomNumbers(ForwardIterator first, ForwardIterator last)
	{
		random_device device;
		mt19937 engine(device());
		uniform_int_distribution<unsigned short> dist(numeric_limits<Bytes::value_type>::min(), numeric_limits<Bytes::value_type>::max());

		generate(first, last, [&engine, &dist]() {
			return dist(engine);
		});
	}
}

pair<Bytes, bool> Encryption::encryptPCBC(const Bytes &key, const Bytes &iv, const Bytes &plainText)
{
	if (key.size() != keySizePCBC || 
		iv.size() != blockSize)
	{
		return make_pair(Bytes(), false);
	}
	if (plainText.empty())
	{
		return make_pair(Bytes(), true);
	}

	Bytes roundKeys(roundKeySize);
	aes_key_schedule_128(key.data(), roundKeys.data());

	const auto extraSize = plainText.size() % blockSize;
	const auto encryptedSize = plainText.size() - extraSize + blockSize;
	Bytes encryptedText(encryptedSize);

	Bytes block(blockSize);
	Bytes ivCopy(iv);
	
	Bytes::size_type index = 0;
	for (; index + blockSize <= plainText.size(); index += blockSize)
	{
		const auto plainBegin = plainText.cbegin() + index;
		const auto plainEnd = plainBegin + blockSize;
		transform(plainBegin, plainEnd, ivCopy.cbegin(), block.begin(), xorFunc);
		aes_encrypt_128(roundKeys.data(), block.data(), encryptedText.data() + index);
		transform(plainBegin, plainEnd, encryptedText.cbegin() + index, ivCopy.begin(), xorFunc);
	}

	Bytes paddedText(blockSize);
	if (extraSize)
	{
		copy(plainText.cbegin() + plainText.size() - extraSize, plainText.cend(), paddedText.begin());
	}
	randomNumbers(paddedText.begin() + extraSize, paddedText.end() - 1);
	paddedText.back() = extraSize ? blockSize - extraSize : blockSize;

	transform(paddedText.cbegin(), paddedText.cend(), ivCopy.cbegin(), block.begin(), xorFunc);
	aes_encrypt_128(roundKeys.data(), block.data(), encryptedText.data() + index);
	
	return make_pair(encryptedText, true);
}

pair<Bytes, bool> Encryption::decryptPCBC(const Bytes &key, const Bytes &iv, const Bytes &cipherText)
{
	if (key.size() != keySizePCBC ||
		iv.size() != blockSize ||
		cipherText.size() % blockSize)
	{
		return make_pair(Bytes(), false);
	}
	if (cipherText.empty())
	{
		return make_pair(Bytes(), true);
	}

	Bytes roundKeys(roundKeySize);
	aes_key_schedule_128(key.data(), roundKeys.data());

	Bytes decryptedText(cipherText.size());

	Bytes block(blockSize);
	Bytes ivCopy(iv);

	for (Bytes::size_type index = 0; index + blockSize <= cipherText.size(); index += blockSize)
	{
		aes_decrypt_128(roundKeys.data(), cipherText.data() + index, block.data());
		transform(ivCopy.cbegin(), ivCopy.cend(), block.cbegin(), decryptedText.begin() + index, xorFunc);
		transform(cipherText.cbegin() + index, cipherText.cbegin() + index + blockSize, decryptedText.cbegin() + index, ivCopy.begin(), xorFunc);
	}

	const auto padding = decryptedText.back();
	decryptedText.resize(decryptedText.size() - padding);

	return make_pair(decryptedText, true);
}