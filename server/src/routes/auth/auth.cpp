#pragma once
#include <iostream>
// #include <cryptopp/blowfish.h>
#include "../../utilities/hash.h"
#include "auth.h"


#include "../../modeles/Expenser.h"

void AuthRoutes::getRoutes(crow::SimpleApp& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app,"/auth/login").methods("POST"_method)
    ([&db](const crow::request& req){
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        std::cout << x << std::endl;
        if (x.has("password") || x.has("email"))  {
            using namespace Expenser;
            AccountData acc;
            std::string email (x["email"]);
            std::string password (x["password"]);

            auto response = db(select(all_of(acc)).from(acc).where(acc.EMAIL == email));
            if(!response.empty()) {
                const auto& row = response.front();
                if(verifyPassword(password,Hash::hashYourData(row.PASSWORD)))
                    return crow::response(200, "OK. Valid");
            }
        }

        return crow::response(403, "Invalid credentials");
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

            db(insert_into(acc).set(acc.EMAIL = email, acc.PASSWORD = password, acc.mainCurrency = mainCurrency));
            return crow::response(201,"The user was created");
        }
        return crow::response(400,"Bad Request");
    });

    CROW_ROUTE(app,"/auth/check").methods("POST"_method)
    ([&db](const crow::request& req){
        std::string password = "toototo";
        std::string originalHash = "sildhfkadbig$@#$@#$bbvhbjhb$@#";
        std::string hashed = Hash::hashYourData(password);
        std::cout << hashed << std::endl;
        return crow::response(200,"OK");
    });
}


bool AuthRoutes::verifyPassword(std::string password, std::string originalHash) {
    std::string hashed = Hash::hashYourData(password);
    std::cout << hashed << std::endl;
    return (hashed == originalHash);
}
