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


std::string JWT::JWTHeader::getBase64Encoded() {
    return getBase64(alg + typ);
}

std::string JWT::Payload::getBase64Encoded() {
    return getBase64(username + std::to_string(issuedAt) + std::to_string(expiredAt));
}


std::string JWT::Token::generateJWTToken() {
    std::string headerBase64 = header.getBase64Encoded();
    std::string payloadBase64 = payload.getBase64Encoded();

    std::string hashed = Hash::hashYourData(header.getBase64Encoded() + "." + payload.getBase64Encoded());
    return headerBase64 + "." + payloadBase64 + "." + hashed;
}

bool JWT::verifyToken(std::string jwt) {
    int end = jwt.find(".");
    std::vector<std::string> jwtSeparated;
    while (end != -1) {
        jwtSeparated.push_back(jwt.substr(0, end));
        jwt.erase(jwt.begin(), jwt.begin() + end + 1);
        end = jwt.find(".");
    }
    jwtSeparated.push_back(jwt.substr(0, end));
    if (jwtSeparated.size() < 3) return false;

    std::string hashed = Hash::hashYourData(jwtSeparated[0] + "." + jwtSeparated[1]);
    std::cout << "Are tokens equal: " << (hashed == jwtSeparated[2]) << std::endl;
    return hashed == jwtSeparated[2];
}

// JWT::JWTTokens JWT::issueNewTokens(JWT::Payload payload) {
//     const std::time_t issuedAt = std::time(nullptr);
//     const std::time_t expiredAt = std::time(nullptr) + JWT::Token::TOKEN_LIVE_TIME;
//     std::cout << "Issued at: " << issuedAt << " and expired at: " << expiredAt << std::endl;

//     JWT::Payload jwtPayload = JWT::Payload(row.EMAIL, issuedAt, expiredAt);
//     JWT::Token token = JWT::Token(jwtPayload);
//     return JWTTokens();
// };