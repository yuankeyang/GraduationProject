#include "AESClass.h"



AESClass::AESClass()
{
	memset(key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH);
	memset(iv, 0x00, CryptoPP::AES::BLOCKSIZE);
}


AESClass::~AESClass()
{
}


std::string AESClass::encryp(std::string plain_text)
{
	std::string ciphertext;
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plain_text.c_str()), plain_text.length() + 1);
	stfEncryptor.MessageEnd();
	return ciphertext;
}

std::string AESClass::decryp(std::string cipher_text)
{
	std::string decryptedtext;
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipher_text.c_str()), cipher_text.size());
	stfDecryptor.MessageEnd();
	return decryptedtext;
}
