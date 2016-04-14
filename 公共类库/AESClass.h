#pragma once
#include <string>
#include <aes.h>
#include <modes.h>
#include <filters.h>
class AESClass
{
public:
	AESClass();
	~AESClass();
	std::string encryp(std::string plain_text);
	std::string decryp(std::string cipher_text);

private:
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
};

