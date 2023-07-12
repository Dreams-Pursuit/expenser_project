#pragma once

#include "crow.h"

struct AuthedUser : crow::ILocalMiddleware {
    struct context {

    };

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        CROW_LOG_INFO << "Before request to:" + req.url;
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx) {
        CROW_LOG_INFO << "After request to:" + req.url;
    }

};