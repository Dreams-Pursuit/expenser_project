#include "hash.h"
#include <sstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/hkdf.h>
#include <cryptopp/filters.h>
#include <cryptopp/sha.h>



std::string Hash::hashYourData(std::string plaintext, std::string salt_selected){
	size_t plen = plaintext.length();
	
	CryptoPP::byte* passwd = (unsigned char*)plaintext.c_str();
	
    CryptoPP::byte* salt = (unsigned char*)salt_selected.c_str();
	size_t slen = strlen((const char*)salt);
	
	CryptoPP::byte info[] = "HKDF key derivation";
	size_t ilen = strlen((const char*)info);
	
	CryptoPP::byte derived[CryptoPP::SHA512::DIGESTSIZE];
    CryptoPP::SHA512 * hash = new CryptoPP::SHA512;
    CryptoPP::HKDF<CryptoPP::SHA512> * hdsf = new CryptoPP::HKDF<CryptoPP::SHA512>;
	CryptoPP::HKDF<CryptoPP::SHA512> hkdf;
	hkdf.DeriveKey(derived, sizeof(derived), passwd, plen, salt, slen, info, ilen);
	
	std::string result;
	CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(result));
	
	encoder.Put(derived, sizeof(derived));
	encoder.MessageEnd();
	std::cout << "Result of the hashYourData function: " << result << std::endl; 
	return result;
}