#include <iostream>

#include "crow.h"
#include "routes/auth/auth.h"
#include "routes/transactions/TransactionRoutes.h"
#include "routes/form/Form.h"

#include "middlewares/AuthedUser.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "../config/Sensitive.h"


namespace sql = sqlpp::postgresql;

int main() {

    crow::App<crow::CORSHandler, AuthedUser> app;
    auto config = std::make_shared<sql::connection_config>();
    config->host = DB_CREDENTIALS::HOST;
    config->user = DB_CREDENTIALS::USER;
    config->password = DB_CREDENTIALS::PASSWORD;
    config->dbname = DB_CREDENTIALS::DB_NAME;

    sql::connection db(config);

    CROW_ROUTE(app, "/")([]() {
        return "Hello world 22";
    });
    AuthRoutes authr;
    TransactionRoutes transr;
    Form formr;
    authr.getRoutes(app,db);
    transr.getRoutes(app, db);
    formr.getRoutes(app, db);

    CROW_ROUTE(app, "/with_middleware")
    .methods("POST"_method)
    .CROW_MIDDLEWARES(app, AuthedUser)
    ([]() {
        return "Hello world!";
    });

    app.port(18080).multithreaded().run();
    return 0;
}
