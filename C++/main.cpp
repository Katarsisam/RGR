#include <iostream>
#include "PlayferAlgorithm.h"
#include "EnigmaAlgorithm.h"
#include "Base64.h"

using namespace std;
void run_playfer() {
    PlayferAlgorithm playfer;
    playfer.execute();
}

void run_enigma() {
    EnigmaAlgorithm enigma;
    enigma.execute();
}

void run_base64() {
    
    Base64 base64;
    base64.execute();
}



int main() {

    char pick;
    bool exit = true;
    string passenter = "323565", passcheck, userName;
    cout << "Добропожаловать, ваше имя?" << endl;
    cin >> userName;

    cout << userName + ", Введите парлоь для авторизации: ";
    cin >> passcheck;
    while (passenter != passcheck) {
        cout << "Пароль неверный" << endl;
        cout << userName + ", Введите парлоь для авторизации: ";
        cin >> passcheck;
    }

    while (true) {
        std::cout << "\nВыберите алгоритм:\n";
        std::cout << "1. Playfer\n";
        std::cout << "2. Enigma\n";
        std::cout << "3. Base64\n";
        std::cout << "0. Выход\n";
        std::cout << "Ваш выбор: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Выход из программы.\n";
            break;
        }

        switch (choice) {
            case 1:
                run_playfer();
                break;
            case 2:
                run_enigma();
                break;
            case 3:
                run_base64();
                break;
            default:
                std::cerr << "Ошибка: неверный ввод!" << std::endl;
        }
    }
    return 0;
}
