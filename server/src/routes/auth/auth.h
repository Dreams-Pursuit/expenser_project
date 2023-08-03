#define CROW_JSON_USE_MAP

#pragma once

#include "crow.h"
#include "../../middlewares/AuthedUser.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>
#include <string>

class AuthRoutes {
public:
    void getRoutes(crow::App<crow::CORSHandler, AuthedUser>& app, sqlpp::postgresql::connection& db);
private:
    static bool verifyPassword(std::string password, std::string originalHash);
};

