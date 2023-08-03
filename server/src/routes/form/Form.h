#define CROW_JSON_USE_MAP

#pragma once
#include "crow.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>
#include "../../middlewares/AuthedUser.h"
#include <string>

class Form {
public:
    void getRoutes(crow::App<crow::CORSHandler, AuthedUser>& app, sqlpp::postgresql::connection& db);
};

