#include <iostream>
#include "crow.h"

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "../config/Sensitive.cpp"


namespace sql = sqlpp::postgresql;

int main() {

    crow::SimpleApp app;
    auto config = std::make_shared<sql::connection_config>();
    config->host = DB_CREDENTIALS::HOST;
    config->user = DB_CREDENTIALS::USER;
    config->password = DB_CREDENTIALS::PASSWORD;
    config->dbname = DB_CREDENTIALS::DB_NAME;

    sql::connection db(config);

    CROW_ROUTE(app, "/")([]() {
        return "Hello world 22";
    });

    app.port(18080).multithreaded().run();
    return 0;
}
