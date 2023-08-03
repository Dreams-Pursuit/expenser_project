#include "token.h"
#include "hash.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "crow.h"
#include "./Base64EncDec.h"

int JWT::Token::TOKEN_LIVE_TIME = 3600;

std::string JWT::JWTHeader::getBase64Encoded() {
    return Base64EncDec::getBase64("{\"alg\":\"" + alg + "\",\"type:\"" + typ + "\"}");
}

std::string JWT::Payload::getBase64Encoded() {
    
    return Base64EncDec::getBase64("{\"username\":\"" + username + "\",\"userId\":\"" + std::to_string(userId) + "\",\"tokenPriviliges\":\"" + tokenPriviliges + "\",\"issuedAt\":"+ std::to_string(issuedAt) + ",\"expiredAt\":"+ std::to_string(expiredAt) + "}");
}


std::string JWT::Token::generateJWTToken(std::string selected_salt) {
    std::string headerBase64 = header.getBase64Encoded();
    std::string payloadBase64 = payload.getBase64Encoded();
    // std::cout << "Header: " + headerBase64;
    // std::cout << "Payload: " + payloadBase64;
    std::string hashed = Hash::hashYourData(header.getBase64Encoded() + "." + payload.getBase64Encoded(), selected_salt);
    // std::cout << "Generated Token: " + headerBase64 + "." + payloadBase64 + "." + hashed;
    return headerBase64 + "." + payloadBase64 + "." + hashed;
}

JWT::TOKEN_VERIFICATION_STATUS JWT::verifyToken(std::string jwt, std::string selected_salt, int userId, std::string tokenPrivilagesType) {
    int end = jwt.find(".");
    std::vector<std::string> jwtSeparated;
    while (end != -1) {
        jwtSeparated.push_back(jwt.substr(0, end));
        jwt.erase(jwt.begin(), jwt.begin() + end + 1);
        end = jwt.find(".");
    }
    jwtSeparated.push_back(jwt.substr(0, end));
    if (jwtSeparated.size() < 3) return JWT::TOKEN_VERIFICATION_STATUS::INVALID;

    crow::json::rvalue x;
    try{
        std::cout << Base64EncDec::decodeBase64(jwtSeparated[1]) << std::endl;
        x = crow::json::load(Base64EncDec::decodeBase64(jwtSeparated[1]));
    }
    catch(...){
        std::cout << "Fuck off" << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    }

    const int now = static_cast<long int> (time(NULL));
    const int tokenExpiredAt(x["expiredAt"]);
    const int userIdP(x["userId"]);
    const std::string privilagesType(x["tokenPriviliges"]);

    if (!(x.has("expiredAt") && now < tokenExpiredAt)) { // Checks whether it is an expired token
        std::cout << "Error: Expired token" << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::EXPIRED;
    }  else if (x.has("userId") && userIdP != -1 && userIdP != userId) {
        std::cout << "UserId of the token and the requested userId are not the same" << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    } else if (privilagesType != "full" && privilagesType != tokenPrivilagesType) {
        std::cout << "The token does not have the right priviliges" << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    }

    std::string hashed = Hash::hashYourData(jwtSeparated[0] + "." + jwtSeparated[1], selected_salt);
    std::cout << "Are tokens equal: " << (hashed == jwtSeparated[2]) << std::endl;
    return hashed == jwtSeparated[2] ? JWT::TOKEN_VERIFICATION_STATUS::VALID : JWT::TOKEN_VERIFICATION_STATUS::INVALID;
}
