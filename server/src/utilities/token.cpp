#include "token.h"
#include "hash.h"
#include <iostream>
#include <vector>
#include <ctime>

int JWT::Token::TOKEN_LIVE_TIME = 3600;


std::string getBase64(std::string convertTo) {
    std::string encoded;
    CryptoPP::StringSource ss(convertTo, true, 
    new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded)));

    return encoded;
}

std::string decodeBase64(std::string convertFrom) {
    std::string encoded;
    // CryptoPP::StringSource ss(convertTo, true, 
    // new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded)));

    return encoded;
}


std::string JWT::JWTHeader::getBase64Encoded() {
    return getBase64(alg + typ);
}

std::string JWT::Payload::getBase64Encoded() {
    return getBase64(username + std::to_string(issuedAt) + std::to_string(expiredAt));
}


std::string JWT::Token::generateJWTToken(std::string selected_salt) {
    std::string headerBase64 = header.getBase64Encoded();
    std::string payloadBase64 = payload.getBase64Encoded();

    std::string hashed = Hash::hashYourData(header.getBase64Encoded() + "." + payload.getBase64Encoded(), selected_salt);
    return headerBase64 + "." + payloadBase64 + "." + hashed;
}

bool JWT::verifyToken(std::string jwt, std::string selected_salt) {
    int end = jwt.find(".");
    std::vector<std::string> jwtSeparated;
    while (end != -1) {
        jwtSeparated.push_back(jwt.substr(0, end));
        jwt.erase(jwt.begin(), jwt.begin() + end + 1);
        end = jwt.find(".");
    }
    jwtSeparated.push_back(jwt.substr(0, end));
    if (jwtSeparated.size() < 3) return false;
    if (selected_salt == CREDENTIAL_SALT::ACCESS_TOKEN_SALT) {
    }
    std::string hashed = Hash::hashYourData(jwtSeparated[0] + "." + jwtSeparated[1], selected_salt);
    std::cout << "Are tokens equal: " << (hashed == jwtSeparated[2]) << std::endl;
    return hashed == jwtSeparated[2];
}
