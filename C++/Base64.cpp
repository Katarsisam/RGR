#include "Base64.h"
#include <iostream>
#include <stdexcept>
#include <string>



bool is_base64(BYTE c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string Base64::base64_encode(const BYTE* buf, unsigned int bufLen) {
    std::string ret;
    BYTE char_array_3[3], char_array_4[4];
    int i = 0;

    while (bufLen--) {
        char_array_3[i++] = *(buf++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                ret += BASE64_CHARS[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (int j = 0; j < i + 1; j++)
            ret += BASE64_CHARS[char_array_4[j]];

        while (i++ < 3)
            ret += '=';
    }

    return ret;
}

 std::vector<BYTE> Base64::base64_decode(const std::string& encoded_string) {
    int in_len = encoded_string.size();
    int i = 0, in_ = 0;
    BYTE char_array_4[4], char_array_3[3];
    std::vector<BYTE> ret;
    std::string base64_ch = BASE64_CHARS;
    
    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_];
        in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_ch.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++)
                ret.push_back(char_array_3[i]);
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (int j = 0; j < 4; j++)
            char_array_4[j] = base64_ch.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (int j = 0; j < i - 1; j++)
            ret.push_back(char_array_3[j]);
    }

    return ret;
}

void Base64::execute(std::string& inputX) {
   
    int operation;
    std::cout << "Введите режим (1 - ENCODE/ 2 - DECODE): ";
    std::cin >> operation;

    input = inputX;
    if (operation == 1) {
        std::string encoded = base64_encode(reinterpret_cast<const BYTE*>(input.c_str()), input.size());
        std::cout << "Закодированное сообщение: " << encoded << std::endl;
        inputX = encoded;
    } else {
        try {
            for (char c : input) {
                if (!isalnum(c) && c != '+' && c != '/' && c != '=') {
                    throw std::invalid_argument("Ошибка, неизвестный символ!");
                }
            }
            std::vector<BYTE> decoded = base64_decode(input);
            std::string decoded_str(decoded.begin(), decoded.end());
            std::cout << "Декодированное сообщение: " << decoded_str << std::endl;
            inputX = decoded_str;
        } catch (std::exception& e) {
            std::cerr << "Результат: " << e.what() << std::endl;
        }
    }
}
