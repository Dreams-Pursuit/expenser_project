#pragma once
#include <string.h>
//#include "../routes.h"

class login: public RouteCollection{
    public:
        static void getLogin(crow::SimpleApp& app, sqlpp::postgresql::connection& db);
    private:
        static bool verifyPassword(std::string Password, std::string Original_Password);
}