#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "PlayferAlgorithm.h"

// ������� ������ �� �������� � �������������� � ������� �������
std::string PlayferAlgorithm::preprocess_text(const std::string& text) {
    std::string result;
    for (char ch : text) {
        if (std::isalpha(ch)) { // ������� ���, ����� ����
            result += std::toupper(ch);
        }
    }
    return result;
}

// �������� ������� ��������
std::vector<std::vector<unsigned char>> PlayferAlgorithm::create_playfair_table(const std::string& key, std::string& alphabet) {
    alphabet = (key.find_first_of(RUS_ALPHABET) != std::string::npos) ? RUS_ALPHABET : ENG_ALPHABET;
    matrix_size = (alphabet == RUS_ALPHABET) ? 6 : 5;

    std::vector<std::vector<unsigned char>> table(matrix_size, std::vector<unsigned char>(matrix_size));
    std::string filtered_key = preprocess_text(key);
    std::string table_content;

    // ������� ��������� �� �����
    for (char ch : filtered_key) {
        if (table_content.find(ch) == std::string::npos) {
            table_content += ch;
        }
    }

    // ��������� ���������� ����� ��������
    for (char ch : alphabet) {
        if (table_content.find(ch) == std::string::npos) {
            table_content += ch;
        }
    }

    // ��������� �������
    int idx = 0;
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            table[i][j] = table_content[idx++];
        }
    }

    return table;
}

// ����� ������� ������� � �������
std::pair<int, int> PlayferAlgorithm::find_position_in_table(const std::vector<std::vector<unsigned char>>& table, char ch) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            if (table[i][j] == ch) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // �� ������
}

// ���������� �������
std::string PlayferAlgorithm::playfair_encrypt(const std::string& text, const std::vector<std::vector<unsigned char>>& table) {
    std::string result;
    std::string prepared_text;

    // ��������� ��������
    for (size_t i = 0; i < text.size(); i++) {
        prepared_text += text[i];
        if (i + 1 < text.size() && text[i] == text[i + 1]) {
            prepared_text += 'X'; // ����������, ���� ������ �����������
        }
    }
    if (prepared_text.size() % 2 != 0) {
        prepared_text += 'X'; // ��������� �� ������ �����
    }

    for (size_t i = 0; i < prepared_text.size(); i += 2) {
        char a = prepared_text[i];
        char b = prepared_text[i + 1];

        auto pos1 = find_position_in_table(table, a);
        auto pos2 = find_position_in_table(table, b);

        if (pos1.first == pos2.first) { // ���� ���
            result += table[pos1.first][(pos1.second + 1) % matrix_size];
            result += table[pos2.first][(pos2.second + 1) % matrix_size];
        } else if (pos1.second == pos2.second) { // ���� �������
            result += table[(pos1.first + 1) % matrix_size][pos1.second];
            result += table[(pos2.first + 1) % matrix_size][pos2.second];
        } else { // �������������
            result += table[pos1.first][pos2.second];
            result += table[pos2.first][pos1.second];
        }
    }

    return result;
}

// ������������ �������
std::string PlayferAlgorithm::playfair_decrypt(const std::string& text, const std::vector<std::vector<unsigned char>>& table) {
    std::string result;

    for (size_t i = 0; i < text.size(); i += 2) {
        char a = text[i];
        char b = text[i + 1];

        auto pos1 = find_position_in_table(table, a);
        auto pos2 = find_position_in_table(table, b);

        if (pos1.first == pos2.first) { // ���� ���
            result += table[pos1.first][(pos1.second - 1 + matrix_size) % matrix_size];
            result += table[pos2.first][(pos2.second - 1 + matrix_size) % matrix_size];
        } else if (pos1.second == pos2.second) { // ���� �������
            result += table[(pos1.first - 1 + matrix_size) % matrix_size][pos1.second];
            result += table[(pos2.first - 1 + matrix_size) % matrix_size][pos2.second];
        } else { // �������������
            result += table[pos1.first][pos2.second];
            result += table[pos2.first][pos1.second];
        }
    }

    return result;
}

void PlayferAlgorithm::execute(std::string& inputX) {
    
    std::cout << "������� ����� (1 - ENCODE/ 2 - DECODE): ";
    std::cin >> mode;

    if (mode != '1' && mode != '2') {
        std::cerr << "������: �������� �����!" << std::endl;
        return;
    }

    std::cout << "������� �������� ����� (5-10 ��������): ";
    std::cin >> keyword;

    if (keyword.size() < 5 || keyword.size() > 10) {
        std::cerr << "������: ����� ����� ������ ���� �� 5 �� 10 ��������!" << std::endl;
        return;
    }

    auto table = create_playfair_table(keyword, alphabet);

    if (mode == '1') {
        message = preprocess_text(inputX);
        inputX = playfair_encrypt(message, table);
        std::cout << "������������� �����: " <<  inputX << std::endl;
    } else {
        inputX = preprocess_text(inputX);
        inputX = playfair_decrypt(inputX, table);
        std::cout << "�������������� �����: " << inputX << std::endl;
    }
}
