#include "./Base64EncDec.h"

std::string Base64EncDec::getBase64(std::string convertTo) {
    std::string encoded;
    CryptoPP::StringSource ss(convertTo, true, 
    new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded)));

    return encoded;
}

std::string Base64EncDec::decodeBase64(std::string convertFrom) {
    std::string encoded = convertFrom;
    std::string decoded;
    
    CryptoPP::StringSource ss(encoded, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink(decoded)
        ) // Base64Decoder
    ); // StringSource

    return decoded;
}

