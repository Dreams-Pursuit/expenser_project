#ifndef SENSITIVE_H
#define SENSITIVE_H
#include <string>

struct DB_CREDENTIALS {
    static const std::string HOST;
    static const std::string USER;
    static const std::string PASSWORD;
    static const std::string DB_NAME;
};

struct CREDENTIAL_SALT {
    static const std::string ACCESS_TOKEN_SALT;
    static const std::string REFRESH_TOKEN_SALT;
    static const std::string PASSWORD_SALT;
};
#endif