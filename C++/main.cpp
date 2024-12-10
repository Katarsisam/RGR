#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include "PlayferAlgorithm.h"
#include "EnigmaAlgorithm.h"
#include "Base64.h"

using namespace std;

// ������ ������ �� �����
string read_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "������: ���������� ������� ���� " << filename << endl;
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
        cerr << "������: ���������� ������� ���� " << filename << endl;
        return;
    }
    file << input;
    
    file.close();
    
}

// ������� ������� ����������
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
    SetConsoleCP(1251);        //��� ����������� ����� � ������ ������� �������� � �������
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string passenter = "323565", passcheck, userName;
    cout << "����� ����������, ���� ���? " << endl;
    cin >> userName;

    cout << userName + ", ������� ������ ��� �����������: ";
    cin >> passcheck;
    while (passenter != passcheck) {
        cout << "������ ��������" << endl;
        cout << userName + ", ������� ������ ��� �����������: ";
        cin >> passcheck;
    }

    while (true) {
        cout << "\n�������� �������� ������:\n";
        cout << "1. ���� ������ � ����������\n";
        cout << "2. ������ ������ �� �����\n";
        cout << "0. �����\n";
        cout << "��� �����: ";
        string input_choice;
        cin >> input_choice;

        if (input_choice == "0") {
            cout << "����� �� ���������.\n";
            break;
        }

        string input_data;
        string filename;
        if (input_choice == "1") {
            cout << "������� ����� ��� ���������: ";
            cin.ignore(); 
            getline(cin, input_data);
        } else if (input_choice == "2") {
            cout << "������� ��� �����: ";
            cin >> filename;
            input_data = read_from_file(filename);
            if (input_data.empty()) {
                continue; 
            }
            cout << "������ �� �����:\n" << input_data << endl;
        } else {
            cerr << "������: �������� ����!" << endl;
            continue;
        }

        cout << "\n�������� ��������:\n";
        cout << "1. Playfer\n";
        cout << "2. Enigma\n";
        cout << "3. Base64\n";
        cout << "0. �����\n";
        cout << "��� �����: ";

        string choice;
        cin >> choice;

        if (choice == "0") {
            cout << "����� �� ���������.\n";
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
                cerr << "������: �������� ����!" << endl;
        }

        if(input_choice == "2")
            change_file(filename,input_data);
    }
    return 0;
}