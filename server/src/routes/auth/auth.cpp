#pragma once
#include "auth.h"

void AuthRoutes::getRoutes(crow::SmallApp& app, sqlpp::postgresql::connection& db){
    CROW_ROUTE(app,"/auth/login").methods("POST"_method)
    ([&db](const crow::request req){
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        return crow::response(200,"OK");
    })
}