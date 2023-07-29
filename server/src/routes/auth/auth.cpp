#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

#include "../config/Sensitive.h"
#include "../../utilities/hash.h"
#include "../../utilities/token.h"
#include "auth.h"


#include "../../modeles/Expenser.h"

void AuthRoutes::getRoutes(crow::SimpleApp& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app,"/auth/login").methods("POST"_method)
    ([&db](const crow::request& req){
        crow::json::rvalue x;
        try{    
                std::cout << req.body << std::endl;
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        std::cout << x << std::endl;

        if (!x.has("grant_type")) return crow::response(400, "Invalid request");
        std::string grant_type (x["grant_type"]);
        
        if (grant_type == "password") {
            if (x.has("password") && x.has("email"))  {
                using namespace Expenser;
                AccountData acc;
                std::string email (x["email"]);
                std::string password (x["password"]);

                std::cout << "I'm here, catch me if you can" << std::endl;

                auto response = db(select(all_of(acc)).from(acc).where(acc.EMAIL == email));
                if(!response.empty()) {
                    const auto& row = response.front();
                    if(verifyPassword(password,row.PASSWORD)) {
                        const std::time_t issuedAt = std::time(nullptr);
                        const std::time_t expiredAtAccess = std::time(nullptr) + 600;
                        const std::time_t expiredAtRefresh = std::time(nullptr) + 86400;
                        std::cout << "Access token was issued at: " << issuedAt << " and expired at: " << expiredAtAccess << std::endl;
                        std::cout << "Refresh token was issued at: " << issuedAt << " and expired at: " << expiredAtRefresh << std::endl;

                        JWT::Payload jwtPayload = JWT::Payload(row.EMAIL, issuedAt, expiredAtAccess);
                        JWT::Payload jwtPayloadRefresh = JWT::Payload(row.EMAIL, issuedAt, expiredAtRefresh);
                        JWT::Token token = JWT::Token(jwtPayload);
                        JWT::Token tokenRefresh = JWT::Token(jwtPayloadRefresh);


                        std::string access_token = token.generateJWTToken();
                        std::string refresh_token = tokenRefresh.generateJWTToken(CREDENTIAL_SALT::REFRESH_TOKEN_SALT);

                        crow::json::wvalue resBody;
                        resBody["access_token"] = access_token;
                        resBody["refresh_token"] = refresh_token;
                        resBody["valid_for"] = JWT::Token::TOKEN_LIVE_TIME;
                        resBody["token_type"] = "bearer";
                        return crow::response(resBody);
                    } else {
                        return crow::response(403, "Invalid request. Invalid password");    
                    }
                } else {
                    return crow::response(403, "Invalid request. This user does not exist");        
                }
            }
            return crow::response(400, "Invalid request. The field password or email is absent");
        } else if (grant_type == "access_token" && x.has("access_token")) {
            std::string access_token (x["access_token"]);
            if (JWT::verifyToken(access_token) == JWT::TOKEN_VERIFICATION_STATUS::VALID) {
                return crow::response(200, "OK. Valid token"); 
            } else if (JWT::verifyToken(access_token) == JWT::TOKEN_VERIFICATION_STATUS::EXPIRED) {
                return crow::response(406, "Token is expired"); 
            }
        } ;
        

        return crow::response(403, "Invalid credentials");
    });

    CROW_ROUTE(app, "/auth/refresh").methods("POST"_method)
    ([&db](const crow::request& req){
        return crow::response(200, "OK"); 
    });

    CROW_ROUTE(app,"/auth/register").methods("POST"_method)
    ([&db](const crow::request& req){
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if (x.has("email") && x.has("password") && x.has("main_currency")) {
            using namespace Expenser;

            AccountData acc;
            std::string email (x["email"]);
            std::string password (x["password"]);
            std::string mainCurrency (x["main_currency"]);

            auto ifExists = db(select(acc.EMAIL).from(acc).where(acc.EMAIL == email));
            if (!ifExists.empty()) {
                return crow::response(400,"The user with this email already exists");
            }
            password = Hash::hashYourData(password, CREDENTIAL_SALT::PASSWORD_TOKEN_SALT);

            db(insert_into(acc).set(acc.EMAIL = email, acc.PASSWORD = password, acc.mainCurrency = mainCurrency));
            return crow::response(201,"The user was created");
        }
        return crow::response(400,"Bad Request");
    });


    CROW_ROUTE(app,"/auth/verify-session").methods("POST"_method) //TMP
    ([&db](const crow::request& req){
        crow::json::rvalue x;
        try {
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if (!x.has("access_token")) return crow::response(400, "Invalid request");

        return crow::response(200,"OK");
    });

    CROW_ROUTE(app,"/auth/check").methods("GET"_method) //TMP
    ([&db](const crow::request& req){
        std::string password = "toototo";
        std::string originalHash = "sildhfkadbig$@#$@#$bbvhbjhb$@#";
        std::string hashed = Hash::hashYourData(password);
        std::cout << hashed << std::endl;
        return crow::response(200,"OK");
    });

    CROW_ROUTE(app,"/auth/check-hash").methods("GET"_method) //TMP
    ([&db](const crow::request& req){
        JWT::JWTHeader jwtHead = JWT::JWTHeader("HMAC", "JWT");
        JWT::Payload jwtPayload = JWT::Payload("sashka", 1690638306, 1690638999);
        JWT::Token token = JWT::Token(jwtPayload, jwtHead);
        std::string jwt = token.generateJWTToken();
        std::cout << jwt << std::endl;
        JWT::verifyToken(jwt);
        return crow::response(200,"OK");
    });
}


bool AuthRoutes::verifyPassword(std::string password, std::string originalHash) {
    std::string hashed = Hash::hashYourData(password, CREDENTIAL_SALT::PASSWORD_TOKEN_SALT);
    std::cout << hashed << std::endl;
    return (hashed == originalHash);
}
