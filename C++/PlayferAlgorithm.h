#ifndef PLAYFER_ALGORITHM_H
#define PLAYFER_ALGORITHM_H

#include <string>
#include <utility>
#include <vector>

#define RUS_ALPHABET "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
#define ENG_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

class PlayferAlgorithm {
public:
    void execute(std::string& inputX);

private:
    char mode;
    int matrix_size;
    std::string keyword;
    std::string message;
    std::string alphabet;
    std::string preprocess_text(const std::string& text);
    std::vector<std::vector<unsigned char>> create_playfair_table(const std::string& key, std::string& alphabet);
    std::pair<int, int> find_position_in_table(const std::vector<std::vector<unsigned char>>& table, char ch);
    std::string playfair_encrypt(const std::string& text, const std::vector<std::vector<unsigned char>>& table);
    std::string playfair_decrypt(const std::string& text, const std::vector<std::vector<unsigned char>>& table);
};

#endif // PLAYFER_ALGORITHM_H
