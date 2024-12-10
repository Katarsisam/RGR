#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "PlayferAlgorithm.h"
#include "EnigmaAlgorithm.h"
#include "Base64.h"

using namespace std;

// Чтение текста из файла
string read_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        file.close();
        return "";
    }
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    return content;
}

void change_file(const string& filename, string input) {
    ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: невозможно открыть файл " << filename << endl;
        return;
    }
    file << input;
    
    file.close();
    
}

// Функции запуска алгоритмов
void run_playfer(string& input) {
    PlayferAlgorithm playfer;
    playfer.execute(input);
}

void run_enigma(string& input) {
    EnigmaAlgorithm enigma;
    enigma.execute(input);
}

void run_base64(string& input) {
    Base64 base64;
    base64.execute(input);
}

int main() {
    SetConsoleCP(1251);        //для корректного ввода и вывода русских символов в консоли
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.UTF-8");
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
        string input_choice;
        cin >> input_choice;

        if (input_choice == "0") {
            cout << "Выход из программы.\n";
            break;
        }

        string input_data;
        string filename;
        if (input_choice == "1") {
            cout << "Введите текст для обработки: ";
            cin.ignore(); 
            getline(cin, input_data);
        } else if (input_choice == "2") {
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

        string choice;
        cin >> choice;

        if (choice == "0") {
            cout << "Выход из программы.\n";
            break;
        }

        switch (atoi(choice.c_str())) {
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

        if(input_choice == "2")
            change_file(filename,input_data);
    }
    return 0;
}