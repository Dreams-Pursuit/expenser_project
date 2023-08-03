#include <string>
#include <cryptopp/base64.h>


namespace Base64EncDec {
    std::string getBase64(std::string convertTo);

    std::string decodeBase64(std::string convertFrom);
};