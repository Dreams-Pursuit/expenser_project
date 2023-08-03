#pragma once

#include "crow.h"
#include "../utilities/token.h"
#include "../../config/Sensitive.h"

struct AuthedUser : crow::ILocalMiddleware {
    AuthedUser() {
        
    }
    struct context {
        crow::json::rvalue parsedX;
    };

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        try{
                ctx.parsedX = crow::json::load(req.body);
        }
        catch(...){
            res.code = 400;
            res.end();
        }
        if (ctx.parsedX.has("access_token") && ctx.parsedX.has("user_id")) {
            std::string access_token(ctx.parsedX["access_token"]);
            std::string userId(ctx.parsedX["user_id"]);
            if (JWT::verifyToken(access_token, CREDENTIAL_SALT::ACCESS_TOKEN_SALT, stoi(userId))) {
                CROW_LOG_INFO << "Token:" + access_token;
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