#define CROW_JSON_USE_MAP

#pragma once

#include "crow.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>

class TransactionRoutes {
public:
    void getRoutes(crow::App<crow::CORSHandler>& app, sqlpp::postgresql::connection& db);
    std::vector<std::string> getQuery(const crow::request& req);
};

