#pragma once
#include <iostream>
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

            auto response = db(select(all_of(acc)).from(acc).where(acc.EMAIL == email and acc.PASSWORD == password));
            if(!response.empty()) {
                const auto& row = response.front();
                std::cout << row.PASSWORD << std::endl;
                std::cout << row.EMAIL << std::endl;
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
        std::cout << x["username"] << std::endl;
        return crow::response(200,"OK");
    });
}


bool AuthRoutes::verifyPassword(std::string password, std::string originalHash) {
    return true;
}
