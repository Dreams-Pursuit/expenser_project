#pragma once
#include "TransactionRoutes.h"
//#include "middlewares/AuthedUser.h"
#include "../../modeles/Expenser.h"

void TransactionRoutes::getRoutes(crow::SimpleApp& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app, "/user/transactions").methods("POST"_method) //Get transaction list
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
            std::vector<crow::json::wvalue> response;
            for(const auto& row : db(select(all_of(trans)).from(trans).where(trans.USERID == id))){
                crow::json::wvalue y;
                y["transaction_id"] = row.TRANSACTIONID;
                y["category"] = row.CATEGORY;
                y["amount"] = row.AMOUNT;
                y["currency"] = row.CURRENCY;
                y["date"] = row.DATE;
                y["description"] = row.DESCRIPTION;
                //std::cout << row.CATEGORY << " " << row.AMOUNT << " " << row.CURRENCY << " " << row.DATE << " " <<row.DESCRIPTION <<  std::endl;
                response.push_back(y);
            }
            crow::json::wvalue final = std::move(response);
            return crow::response(std::move(final));
        }
        return crow::response(200, "Your list of transactions is currently empty");
    });// Get transaction list

    CROW_ROUTE(app, "/user/transactions/add").methods("POST"_method) //Add transaction
    ([&db](const crow::request& req) {
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if(x.has("user_id") && x.has("category") && x.has("amount") && x.has("currency") && x.has("date")){
            using namespace Expenser;
            TransactionsList trans;
            std::string user_id(x["user_id"]);
            int id = stoi(user_id);
            std::string category(x["category"]);
            std::string amount(x["amount"]);
            int int_amount = stoi(amount);
            std::string currency(x["currency"]);
            std::string date(x["date"]);
            std::string description(x["description"]);
            db(insert_into(trans).set(trans.USERID = id, trans.CATEGORY = category, trans.AMOUNT = int_amount, trans.CURRENCY = currency, trans.DATE = date, trans.DESCRIPTION = description));
            return crow::response(200,"Transaction has been successfully added to your list");
        }
        return crow::response(401, "Failed to add a new transaction");
    });//Add transaction

    CROW_ROUTE(app, "/user/transactions/modify").methods("POST"_method) //Modify transaction
    ([&db](const crow::request& req) {
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if(x.has("transaction_id") && x.has("category") && x.has("amount") && x.has("currency") && x.has("date") && x.has("description")){
            using namespace Expenser;
            TransactionsList trans;
            std::string trans_id(x["transaction_id"]);
            int id = stoi(trans_id);
            std::string category(x["category"]);
            std::string amount(x["amount"]);
            int int_amount = stoi(amount);
            std::string currency(x["currency"]);
            std::string date(x["date"]);
            std::string description(x["description"]);
            if(!db(select(all_of(trans)).from(trans).where(trans.TRANSACTIONID == id)).empty()){
                if(!category.empty())
                    db(update(trans).set(trans.CATEGORY = category).where(trans.TRANSACTIONID == id));
                if(!amount.empty())
                    db(update(trans).set(trans.AMOUNT = int_amount).where(trans.TRANSACTIONID == id));
                if(!currency.empty())
                    db(update(trans).set(trans.CURRENCY = currency).where(trans.TRANSACTIONID == id));
                if(!date.empty())
                    db(update(trans).set(trans.DATE = date).where(trans.TRANSACTIONID == id));
                if(!description.empty())
                    db(update(trans).set(trans.DESCRIPTION = description).where(trans.TRANSACTIONID == id));
                return crow::response(200,"Transaction has been successfully modifiedс");
            }
            return crow::response(404,"Oops, can't find this transaction!");
        }
        return crow::response(401, "Failed to update a transaction");
    });//Modify transaction

    CROW_ROUTE(app, "/user/transactions/delete").methods("POST"_method) //Delete transaction
    ([&db](const crow::request& req) {
        crow::json::rvalue x;
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if(x.has("transaction_id")){
            using namespace Expenser;
            TransactionsList trans;
            std::string trans_id(x["transaction_id"]);
            int id = stoi(trans_id);
            if(!db(select(all_of(trans)).from(trans).where(trans.TRANSACTIONID == id)).empty()){
            db(remove_from(trans).where(trans.TRANSACTIONID == id));
            return crow::response(200,"Transaction has been successfully deleted from your list");
            }
            return crow::response(404,"Oops, can't find this transaction!");
        }
        return crow::response(401, "Failed to delete a transaction");
    });//Delete transaction
}
