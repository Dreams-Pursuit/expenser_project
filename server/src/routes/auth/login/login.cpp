#include "login.h"


void login::getLogin(crow::SimpleApp& app, sqlpp::postgresql::connection& db){
    CROW_ROUTE(app,"/auth/login").methods("POST"_method)([&db]())
}