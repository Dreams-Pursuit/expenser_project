#include "./Form.h"
#include "../../utilities/formUrlGenerator.h"
#include "../config/Sensitive.h"

void Form::getRoutes(crow::App<crow::CORSHandler, AuthedUser>& app, sqlpp::postgresql::connection& db) {
    CROW_ROUTE(app, "/form/generate_url").methods("POST"_method)([&db](const crow::request& req) {
        crow::json::rvalue x; //rvalue - read value
        try{
                x = crow::json::load(req.body);
        }
        catch(...){
            return crow::response(400, "probably json syntax error");
        }
        if (!x.has("access_token")) return crow::response(403, "No access token");
        if (x.has("username") && x.has("user_id")) {
            std::string username (x["username"]);
            std::string userId (x["user_id"]);
            std::string access_token (x["access_token"]);

            if (JWT::verifyToken(access_token, CREDENTIAL_SALT::ACCESS_TOKEN_SALT, stoi(userId)) != JWT::TOKEN_VERIFICATION_STATUS::VALID) return crow::response(403, "Invalid access_token");
            const std::time_t issuedAt = std::time(nullptr);
            const std::time_t expiredAt = std::time(nullptr) + pow(60, 4);

            JWT::Payload jwtPayload = JWT::Payload(username, issuedAt, expiredAt, stoi(userId), "form");
            JWT::Token token = JWT::Token(jwtPayload);
            std::string outToken = token.generateJWTToken();

            crow::json::wvalue resBody;
            resBody["url"] = outToken;
            return crow::response(resBody);
        }

        return crow::response(400, "Invalid request");
    });
}
