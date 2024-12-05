#include "EnigmaAlgorithm.h"
#include <iostream>
#include <algorithm>

#define ENG_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define RUS_ALPHABET "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"

const std::string STANDARD_ROTORS[] = {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK"
};

void EnigmaAlgorithm::encode_message(const std::string& alphabet) {
    int size = alphabet.size();

    for (size_t i = 0; i < message.size(); i++) {
        int pos = alphabet.find(message[i]);
        if (pos != std::string::npos) {
            message[i] = alphabet[(pos + rotor_shifts[0]) % size];
            rotor_shifts[0]++;
        }
    }

    for (size_t i = 0; i < message.size(); i++) {
        for (size_t j = 0; j < rotors.size(); j++) {
            int pos = alphabet.find(message[i]);
            if (pos != std::string::npos) {
                message[i] = rotors[j][pos];
            }
        }
    }

    std::cout << "Зашифрованное сообщение: " << message << std::endl;
}

void EnigmaAlgorithm::decode_message(const std::string& alphabet) {
    int size = alphabet.size();

    for (size_t i = 0; i < message.size(); i++) {
        for (int j = rotors.size() - 1; j >= 0; j--) {
            int pos = rotors[j].find(message[i]);
            if (pos != std::string::npos) {
                message[i] = alphabet[pos];
            }
        }
    }

    for (size_t i = 0; i < message.size(); i++) {
        int pos = alphabet.find(message[i]);
        if (pos != std::string::npos) {
            message[i] = alphabet[(pos - rotor_shifts[0] + size) % size];
            rotor_shifts[0]++;
        }
    }

    std::cout << "Дешифрованное сообщение: " << message << std::endl;
}

void EnigmaAlgorithm::execute(std::string inputX) {
    int operation;
    std::cout << "Введите режим (1 - ENCODE/ 2 - DECODE): ";
    std::cin >> operation;

    if (operation != 1 && operation != 2) {
        std::cerr << "Ошибка: неверный режим!" << std::endl;
        return;
    }
    
    message = inputX;
    
    std::cout << "Выберите 3 ротора (1-5): ";
    for (int i = 0; i < 3; ++i) {
        int rotor_choice;
        std::cin >> rotor_choice;
        if (rotor_choice < 1 || rotor_choice > 5) {
            std::cerr << "Ошибка: неверный номер ротора!" << std::endl;
            return;
        }
        rotors.push_back(STANDARD_ROTORS[rotor_choice - 1]);
    }

    std::cout << "Введите 3 смещения: ";
    for (int i = 0; i < 3; ++i) {
        int shift;
        std::cin >> shift;
        rotor_shifts.push_back(shift);
    }

    std::string alphabet = message.find_first_of(RUS_ALPHABET) != std::string::npos ? RUS_ALPHABET : ENG_ALPHABET;

    for (char& c : message) {
        c = toupper(c);
    }

    if (operation == 1) {
        encode_message(alphabet);
    } else {
        decode_message(alphabet);
    }
}
