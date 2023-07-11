#include "TransactionRoutes.h"
#include "middlewares/AuthedUser.h"


void TransactionRoutes::getRoutes(crow::SimpleApp& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app, "/transactions/get-latest-transaction").methods("POST"_method)
    ([&db](const crow::request& req) {
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }

        return crow::response(200, "Normul");
    });
}