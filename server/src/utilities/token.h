
#include <string>
#include <cryptopp/base64.h>
#include "../../config/Sensitive.h"

namespace JWT {
    using std::string;
    class JWTHeader {
        private:
            string alg;
            string typ;
        public: 
            JWTHeader(string algorithm, string type): alg(algorithm), typ(type) {};
            string getBase64Encoded();

    };

    class Payload {
        private:
            string username; 
            int issuedAt; 
            int expiredAt;
        public:
            Payload(string username, int iat, int expat): username(username), issuedAt(iat), expiredAt(expat) {};
            string getBase64Encoded();

    };

    class Token {
            JWTHeader header;
            Payload payload;
        public: 
            static int TOKEN_LIVE_TIME;
            
            Token(Payload payload, JWTHeader header=JWTHeader("HMAC", "JWT")): header(header), payload(payload) {};
            string generateJWTToken(std::string selected_salt=CREDENTIAL_SALT::ACCESS_TOKEN_SALT);
    };

    enum TOKEN_VERIFICATION_STATUS {
        INVALID,
        VALID,
        EXPIRED
    };

    TOKEN_VERIFICATION_STATUS verifyToken(string jwt, string salt_selected=CREDENTIAL_SALT::ACCESS_TOKEN_SALT);
}