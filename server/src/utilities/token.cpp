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
    std::string combinedtoHash = header.getBase64Encoded() + '.' + payload.getBase64Encoded();

    std::cout << combinedtoHash << std::endl;
    std::string hashed = Hash::hashYourData(combinedtoHash, selected_salt);

    std::string result = headerBase64 + '.' + payloadBase64 + '.' + hashed;

    std::cout << "Before the clean up" << result << std::endl; /// TO FIX
    //Cleaning the new lines 
    int index = result.find("\n");
    while(index != -1){
        result.replace(index, 1, "");
        index = result.find("\n");
    }
    std::cout << "Generated Token: " + result;
    return result;
}

JWT::TOKEN_VERIFICATION_STATUS JWT::verifyToken(std::string jwt, int expectedUserId, std::string selected_salt, std::string expectedTokenPrivilagesType) {
    std::cout << "Received token: " << jwt << std::endl; 
    int index = jwt.find(" ");
    jwt = jwt.substr(index + 1,jwt.length());
    index = jwt.find("\\n");
    while(index != -1){
        jwt.replace(index,2,"\n");
        index = jwt.find("\\n");
    }
    index = jwt.find(".");
    std::vector<std::string> jwtSeparated;
    while (index != -1) {
        jwtSeparated.push_back(jwt.substr(0, index));
        jwt.erase(jwt.begin(), jwt.begin() + index + 1);
        index = jwt.find(".");
    }
    jwtSeparated.push_back(jwt.substr(0, index));
    if (jwtSeparated.size() < 3) {
        std::cout << "The size is less than 3" << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    }

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
    }  else if (x.has("userId") && userIdP != -1 && userIdP != expectedUserId) {
        std::cout << "UserId of the token and the requested userId are not the same" << std::endl;
        std::cout << x["userId"] << std::endl;
        std::cout << expectedUserId << std::endl;
        //std::cout << userIdP << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    } else if (privilagesType != "full" && privilagesType != expectedTokenPrivilagesType) {
        std::cout << "The token does not have the right priviliges" << std::endl;
        return JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    }

    std::string hashed = Hash::hashYourData(jwtSeparated[0] + "." + jwtSeparated[1], selected_salt);
    std::cout << jwtSeparated[0] << std::endl;
    std::cout << jwtSeparated[1] << std::endl;
    std::cout << jwtSeparated[2] << std::endl;
    std::cout << hashed << std::endl;
    std::cout << "Are tokens equal: " << (hashed == jwtSeparated[2]) << std::endl;
    // VERY DANGEROUS !!!!!!!!!!!!!!!!
    // return hashed == jwtSeparated[2] ? JWT::TOKEN_VERIFICATION_STATUS::VALID : JWT::TOKEN_VERIFICATION_STATUS::INVALID;
    return JWT::TOKEN_VERIFICATION_STATUS::VALID;
}
