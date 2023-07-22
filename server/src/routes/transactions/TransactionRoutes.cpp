#pragma once
#include "TransactionRoutes.h"
//#include "middlewares/AuthedUser.h"
#include "../../modeles/Expenser.h"

void TransactionRoutes::getRoutes(crow::SimpleApp& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app, "/user/transactions").methods("POST"_method) //Get transaction list
    ([&db,this](const crow::request& req) {
        crow::json::rvalue x; //rvalue - read value
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
            auto query = getQuery(req);
            for(const auto& row : db(select(all_of(trans)).from(trans).where(trans.USERID == id && //basic user_id check - we only send transactions of determined user
            trans.DATE >= query[0] && trans.DATE <= query[1] &&  // taking some period from date1(fromDate) to date2(toDate)
            trans.AMOUNT >= stod(query[2]) && trans.AMOUNT <= stod(query[3]) && // taking some amount from amount1(fromAmount) to amount2(toAmount) - still there are things to be done we should take absolute value of amount
            (trans.CATEGORY == query[4] || !exists(select(trans.CATEGORY).from(trans).where(trans.CATEGORY == query[4])))))){ // To pass this test, transaction has to either fulfill the category(category list) request
                crow::json::wvalue y;                                                                                          // or view which consists of transactions(of given category) has to be empty, which means that cat(string query for CATEGORY)
                y["transaction_id"] = row.TRANSACTIONID;                                                                       // is empty or invalid(is dealt with by sending correct request from Front-end part)
                y["category"] = row.CATEGORY;
                y["amount"] = row.AMOUNT;
                y["currency"] = row.CURRENCY;
                y["date"] = row.DATE;
                y["description"] = row.DESCRIPTION;
                //std::cout << row.CATEGORY << " " << row.AMOUNT << " " << row.CURRENCY << " " << row.DATE << " " <<row.DESCRIPTION <<  std::endl;
                response.push_back(y); //After transforming each transaction into json object, we put it in vector;
            }
            crow::json::wvalue final = std::move(response); // here we should perform std::move operation twice to turn vector into array
            return crow::response(std::move(final));        // because response doesn't work with vector(it doesn't treat it as &&response)
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
std::vector<std::string> TransactionRoutes::getQuery(const crow::request& req){ //Configuring the query so only chosen transactions are viewed
    std::vector<std::string>config;
    std::ostringstream os;
    std::string fromDate = "";
    time_t now = time(0);
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    os << std::put_time(&tm,"%Y-%m-%d %H:%M:%S");
    std::string toDate = os.str();
    std::string fromAmount = "-1000000";
    std::string toAmount = "1000000";
    std::string cat = "";
        if(req.url_params.get("dfrom") != nullptr){ // dfrom - date from
            fromDate = boost::lexical_cast<std::string>(req.url_params.get("dfrom"));
            fromDate.insert(4,1,'-');   // lines 144-146 are made to serialize the date and turn it into 'timestamp'
            fromDate.insert(7,1,'-');
            fromDate += " 00:00:00";
        }
        config.push_back(fromDate);
        if(req.url_params.get("dto") != nullptr){ // dto - date to
            toDate = boost::lexical_cast<std::string>(req.url_params.get("dto"));
            toDate.insert(4,1,'-');
            toDate.insert(7,1,'-');
            toDate += " 23:59:59";
            //std::cout << toDate << std::endl;
        }
        config.push_back(toDate);
        if(req.url_params.get("afrom") != nullptr){ // afrom - amount from
            fromAmount = boost::lexical_cast<std::string>(req.url_params.get("afrom"));
        }
        config.push_back(fromAmount);
        if(req.url_params.get("ato") != nullptr){ // ato - amount to
            toAmount = boost::lexical_cast<std::string>(req.url_params.get("ato"));
        }
        config.push_back(toAmount);
        if(req.url_params.get("cat") != nullptr){ // cat - category
            cat = boost::lexical_cast<std::string>(req.url_params.get("cat"));
        }
        config.push_back(cat);
        return config;
}
