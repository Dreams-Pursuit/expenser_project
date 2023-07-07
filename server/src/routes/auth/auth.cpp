#pragma once
#include "auth.h"
#include <iostream>

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
        return crow::response(200,"OK");
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
