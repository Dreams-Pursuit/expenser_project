#pragma once
#include "TransactionRoutes.h"
//#include "middlewares/AuthedUser.h"
#include "../../modeles/Expenser.h"

void TransactionRoutes::getRoutes(crow::SimpleApp& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app, "/user/transactions").methods("POST"_method)
    ([&db](const crow::request& req) {
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if(x.has("user_id")){
            using namespace Expenser;
            TransactionsList trans;
            std::string user_id(x["user_id"]);
            int id = stoi(user_id);
            auto response = db(select(all_of(trans)).from(trans).where(trans.USERID == id));
            if(!response.empty()){
                const auto& row = response.front();
                std::cout << row.CATEGORY << " " << row.AMOUNT << " " << row.CURRENCY << " " << row.DATE << " " <<row.DESCRIPTION <<  std::endl;
                return crow::response(200, "OK. Valid");
            }
        }
        return crow::response(200, "Your list of transactions is currently empty");
    });
}