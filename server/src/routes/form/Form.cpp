#include "./Form.h"
#include "../../utilities/formUrlGenerator.h"

void Form::getRoutes(crow::App<crow::CORSHandler>& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app, "/form/generate_url").methods("POST"_method)([&db](const crow::request& req) {
        crow::json::rvalue x; //rvalue - read value
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        
        return crow::response(200, FormGenerator::generateUrl("Test"));
    });
}