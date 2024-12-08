#ifndef BASE64_H
#define BASE64_H

#define BASE64_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

#include <string>
#include <vector>

typedef unsigned char BYTE;

class Base64 {
public:
    void execute(std::string& inputX);

private:
    int var;
    std::string input;
    std::string base64_encode(const BYTE* buf, unsigned int bufLen);
    std::vector<BYTE> base64_decode(const std::string& encoded_string);
};

#endif // BASE64_H
