#include "PCBC.h"

#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <iterator>

using namespace Encryption;
using namespace std;

void mainDialog();
Bytes readFromFile(const string& message);

int main()
{
	mainDialog();
	return 0;
}

Bytes readFromFile(const string& message)
{
	cout << message;
	string filePath;
	cin >> filePath;
	ifstream inFile(filePath, ios::binary | std::ios::ate);
	if (!inFile.is_open())
	{
		cout << "Failed to open the file" << endl;
		return Bytes();
	}
	auto size = inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	
	Bytes buffer(size);
	inFile.read(reinterpret_cast<char *>(buffer.data()), size);
	return buffer;
}

void mainDialog()
{
	const auto text = readFromFile("Input path to the file with the encrypted(decrypted) text: ");
	if (text.empty())
	{
		cout << "Failed to read the text" << endl;
		return;
	}

	const auto key = readFromFile("Input path to the file with the key: ");
	if (key.empty())
	{
		cout << "Failed to read the key" << endl;
		return;
	}

	const auto iv = readFromFile("Input path to the file with the initialization vector: ");
	if (iv.empty())
	{
		cout << "Failed to read the initialization vector" << endl;
		return;
	}

	cout << "Choose operation:" << endl
		<< "    (E)ncrypt" << endl
		<< "    (D)ecrypt" << endl;
	char operation;
	cin >> operation;

	bool result;
	Bytes processedText;
	switch (toupper(operation))
	{
	case 'E':	
		tie(processedText, result) = encryptPCBC(key, iv, text);
		break;
	case 'D':
		tie(processedText, result) = decryptPCBC(key, iv, text);
		break;
	default:
		cout << "Unknown operation." << endl;
		return;
	}

	if (!result)
	{
		cout << "The operation failed" << endl;
		return;
	}

	cout << "Input path to the output file" << endl;
	string path;
	cin >> path;
	ofstream outFile(path, ios::binary);
	copy(processedText.cbegin(), processedText.cend(), ostream_iterator<Bytes::value_type>(outFile));
	outFile.close();
	cout << "Finished processing" << endl;
}
