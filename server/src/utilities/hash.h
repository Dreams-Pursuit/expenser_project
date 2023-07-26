#pragma once 
#include <iostream>
#include <string>
#include "../../config/Sensitive.h"

namespace Hash {
    std::string hashYourData(std::string plaintext, std::string salt_selected=CREDENTIAL_SALT::ACCESS_TOKEN_SALT);
};