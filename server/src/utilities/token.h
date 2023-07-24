
#include <string>
#include <cryptopp/base64.h>

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
            string generateJWTToken();
    };

    // struct JWTTokens {
    //     string access_token;
    //     string refresh_token;

    //     JWTTokens(string access_token, string refresh_token): access_token(access_token), refresh_token(refresh_token) {};
    // };

    // JWTTokens issueNewTokens(Payload payload);
    bool verifyToken(string jwt);
}