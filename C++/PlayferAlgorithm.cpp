#include "PlayferAlgorithm.h"
#include <iostream>
#include <algorithm>
#include <cctype>


#define RUS_ALPHABET "абвгдежзийклмнопрстуфхцчшщыэюя"
#define ENG_ALPHABET "abcdefghiklmnopqrstuvwxyz" // J исключён

void PlayferAlgorithm::generate_matrix(const std::string& alphabet) {
    std::string unique_key = keyword;
    for (char c : alphabet)
        if (unique_key.find(c) == std::string::npos)
            unique_key += c;

    int idx = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            matrix[i][j] = unique_key[idx++];
}

std::pair<int, int> PlayferAlgorithm::find_position(char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) return {i, j};
        }
    }
    return {-1, -1};
}

std::string PlayferAlgorithm::encode_bigram(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
    if (pos1.first == pos2.first) {
        return std::string(1, matrix[pos1.first][(pos1.second + 1) % 5]) +
               std::string(1, matrix[pos2.first][(pos2.second + 1) % 5]);
    } else if (pos1.second == pos2.second) {
        return std::string(1, matrix[(pos1.first + 1) % 5][pos1.second]) +
               std::string(1, matrix[(pos2.first + 1) % 5][pos2.second]);
    } else {
        return std::string(1, matrix[pos1.first][pos2.second]) +
               std::string(1, matrix[pos2.first][pos1.second]);
    }
}

std::string PlayferAlgorithm::decode_bigram(const std::pair<int, int>& pos1, const std::pair<int, int>& pos2) {
    if (pos1.first == pos2.first) {
        return std::string(1, matrix[pos1.first][(pos1.second + 4) % 5]) +
               std::string(1, matrix[pos2.first][(pos2.second + 4) % 5]);
    } else if (pos1.second == pos2.second) {
        return std::string(1, matrix[(pos1.first + 4) % 5][pos1.second]) +
               std::string(1, matrix[(pos2.first + 4) % 5][pos2.second]);
    } else {
        return std::string(1, matrix[pos1.first][pos2.second]) +
               std::string(1, matrix[pos2.first][pos1.second]);
    }
}

void PlayferAlgorithm::execute(std::string inputX) {
    char mode;
    
    std::cout << "Введите режим (1 - ENCODE/ 2 - DECODE): ";
    std::cin >> mode;

    if (mode != '1' && mode != '2') {
        std::cerr << "Ошибка: неверный режим!" << std::endl;
        return;
    }

    std::cout << "Введите ключевое слово (5-10 символов): ";
    std::cin >> keyword;

    if (keyword.size() < 5 || keyword.size() > 10) {
        std::cerr << "Ошибка: длина ключа должна быть от 5 до 10 символов!" << std::endl;
        return;
    }
    
    message = inputX;
   
    
    std::string alphabet = keyword.find_first_of(RUS_ALPHABET) != std::string::npos ? RUS_ALPHABET : ENG_ALPHABET;
    generate_matrix(alphabet);

    if (message.size() % 2 != 0) message += alphabet[0];

    std::string result;
    for (size_t i = 0; i < message.size(); i += 2) {
        auto pos1 = find_position(message[i]);
        auto pos2 = find_position(message[i + 1]);
        if (mode == '1') {
            result += encode_bigram(pos1, pos2);
        } else {
            result += decode_bigram(pos1, pos2);
        }
    }
    std::cout << "Результат: " << result << std::endl;
}
