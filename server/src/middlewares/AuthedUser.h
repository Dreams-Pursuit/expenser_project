#pragma once

#include "crow.h"
#include "../utilities/token.h"
#include "../../config/Sensitive.h"

struct AuthedUser : crow::ILocalMiddleware {
    AuthedUser() {}
    struct context {
        crow::json::rvalue parsedX;
        std::string authToken;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        try{
                ctx.parsedX = crow::json::load(req.body);
                ctx.authToken = req.get_header_value("Authorization");
        }
        catch(...){
            res.code = 400;
            res.end();
        }
        if (ctx.authToken == "" && !ctx.parsedX.has("user_id")) {
            res.code = 400;
            res.end();
        } else {
            std::string userId(ctx.parsedX["user_id"]);
            if (JWT::verifyToken(ctx.authToken, stoi(userId), CREDENTIAL_SALT::ACCESS_TOKEN_SALT) == JWT::TOKEN_VERIFICATION_STATUS::VALID) {
                CROW_LOG_INFO << "Token:" + ctx.authToken;
                CROW_LOG_INFO << "UserId:" + userId;
            } else if (req.url.find("/transactions/add") != std::string::npos && JWT::verifyToken(ctx.authToken, stoi(userId), CREDENTIAL_SALT::ACCESS_TOKEN_SALT, "form") == JWT::TOKEN_VERIFICATION_STATUS::VALID) {
                CROW_LOG_INFO << "Token:" + ctx.authToken;
                CROW_LOG_INFO << "UserId:" + userId;
            } else {
                res.code = 403;
                res.end();
            }
        }
        
        CROW_LOG_INFO << "Before request to:" + req.url;
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx) {
        CROW_LOG_INFO << "After request to:" + req.url;
    }

};