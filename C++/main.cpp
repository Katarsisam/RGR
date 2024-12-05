#include <iostream>
#include <fstream>
#include <string>
#include "PlayferAlgorithm.h"
#include "EnigmaAlgorithm.h"
#include "Base64.h"

using namespace std;

// Чтение текста из файла
string read_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

// Функции запуска алгоритмов
void run_playfer(const string& input) {
    PlayferAlgorithm playfer;
    playfer.execute(input);
}

void run_enigma(const string& input) {
    EnigmaAlgorithm enigma;
    enigma.execute(input);
}

void run_base64(const string& input) {
    Base64 base64;
    base64.execute(input);
}

int main() {
    string passenter = "323565", passcheck, userName;
    cout << "Добро пожаловать, ваше имя? " << endl;
    cin >> userName;

    cout << userName + ", Введите пароль для авторизации: ";
    cin >> passcheck;
    while (passenter != passcheck) {
        cout << "Пароль неверный" << endl;
        cout << userName + ", Введите пароль для авторизации: ";
        cin >> passcheck;
    }

    while (true) {
        cout << "\nВыберите источник текста:\n";
        cout << "1. Ввод текста с клавиатуры\n";
        cout << "2. Чтение текста из файла\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        int input_choice;
        cin >> input_choice;

        if (input_choice == 0) {
            cout << "Выход из программы.\n";
            break;
        }

        string input_data;
        if (input_choice == 1) {
            cout << "Введите текст для обработки: ";
            cin.ignore(); 
            getline(cin, input_data);
        } else if (input_choice == 2) {
            string filename;
            cout << "Введите имя файла: ";
            cin >> filename;
            input_data = read_from_file(filename);
            if (input_data.empty()) {
                continue; 
            }
            cout << "Данные из файла:\n" << input_data << endl;
        } else {
            cerr << "Ошибка: неверный ввод!" << endl;
            continue;
        }

        cout << "\nВыберите алгоритм:\n";
        cout << "1. Playfer\n";
        cout << "2. Enigma\n";
        cout << "3. Base64\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "Выход из программы.\n";
            break;
        }

        switch (choice) {
            case 1:
                run_playfer(input_data);
                break;
            case 2:
                run_enigma(input_data);
                break;
            case 3:
                run_base64(input_data);
                break;
            default:
                cerr << "Ошибка: неверный ввод!" << endl;
        }
    }
    return 0;
}