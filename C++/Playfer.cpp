#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

void Encode(vector<int> index,char matrix[5][5]){
    int a = 0, b = 0;
    cout << "encrypted sequence: " << endl;
    for(int i = 0; i <= index.size()-3; i+=4){
        a = index[i + 3] + 1;
        // если на одной строке
        if(index[i] == index[i+2] && a < 5){
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] + 1] << matrix[index[i + 2]][a];
        }
        // если на одной строке и у края
        if(index[i] == index[i+2] && a >= 5){
            a = 0;
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] + 1] << matrix[index[i + 2]][a];
        }
        b = index[i + 2] + 1;
        // если в одном столбце
        if(index[i + 1] == index[i + 3] && b < 5){
            cout.width(5);
            cout << matrix[index[i] + 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        // если в одном столбце и у края
        if(index[i + 1] == index[i + 3] && b >= 5){
            b = 0;
            cout.width(5);
            cout << matrix[index[i] + 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        
        if(index[i] != index[i + 2] && index[i + 1] != index[i + 3]){
            cout.width(5);
            cout << matrix[index[i + 2]][index[i + 1]] << matrix[index[i]][index[i + 3]];
        }
    }
}

void Decode(vector<int> index,char matrix[5][5]){
    int a = 0, b = 0;
    cout << "encrypted sequence: " << endl;
    for(int i = 0; i <= index.size()-3; i+=4){
        // если на одной строке
        a = index[i + 3] - 1;
        if(index[i] == index[i + 2] && a >= 0){
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] - 1] << matrix[index[i + 2]][a];
        }
        // если на одной строке и у края
        if(index[i] == index[i + 2] && a < 0){
            a = 4;
            cout.width(5);
            cout << matrix[index[i]][index[i + 1] - 1] << matrix[index[i + 2]][a];
        }
        // если в одном столбце
        b = index[i + 2] - 1;
        if(index[i + 1] == index[i + 3] && b >= 0){
            cout.width(5);
            cout << matrix[index[i] - 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        // если в одном столбце и у края
        if(index[i + 1] == index[i + 3] && b < 0){
            b = 4;
            cout.width(5);
            cout << matrix[index[i] - 1][index[i + 1]] << matrix[b][index[i + 3]];
        }
        
        if(index[i] != index[i + 2] && index[i + 1] != index[i + 3]){
            cout.width(5);
            cout << matrix[index[i + 2]][index[i + 1]] << matrix[index[i]][index[i + 3]];
        }
    }
}

int main(){
    vector<int> index;
    string keyword, code;
    string alphabet = "abcdefghijklmnoprstuvwxyz";
    char matrix[5][5];
    
    char x;
    cout << "enter number encoding(1) or decoding(2)" << endl;
    cin >> x;
    
    if(x != '1' && x != '2'){
        cout << "value entered incorrectly" << endl;
        exit(0);
    }
    
    int q = 0;
    while(q == 0){
        cout << "enter a keyword: ";
        cin >> keyword;
        
        // проверка на верхний регистр
        for(int i = 0; i < keyword.length(); i++){
            if(isupper(keyword[i])) keyword[i] = tolower(keyword[i]);
        }
        
        // проверка на посторонние символы
        for(int i = 0; i < keyword.length(); i++){
            if(isalpha(keyword[i])) q = 1;
            else {
                cout << "symbol " << keyword[i] << " is not appropriate " << i + 1 << " on position" << endl;
                q = 0;
                break;
            }
        }
    }
    
    // удаление дублирования
    for(int i = 1; i < keyword.length(); i++){
        if(keyword[i-1] == keyword[i]){
            keyword.erase(i, 1);
            i--;
        }
    }
    
    // удаление букв ключевого слова из алфавита 
    for(int i = 0; i < keyword.length(); i++){
        for(int j = 0; j < alphabet.length(); j++){
            if(keyword[i] == alphabet[j]) alphabet.erase(j, 1);
        }
    }
    
    // ввод данных в массив
    cout << "key matrix: " << endl;
    int k = 0, m = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(k < keyword.length()){
                matrix[i][j] = keyword[k];
            }
            if(k >= keyword.length()){
                matrix[i][j] = alphabet[m];
                m++;
            }
            k++;
        }
    }
    
    // вывод массива 
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    int p = 0;
    while(p == 0){
        cout << "enter massage: ";
        cin >> code;
        
        // проверка на верхний регистр
        for(int i = 0; i < code.length(); i++){
            if(isupper(code[i])) code[i] = tolower(code[i]);
        }
        
        // проверка на посторонние символы
        for(int i = 0; i < code.length(); i++){
            if(isalpha(code[i])) p = 1;
            else {
                cout << "symbol " << code[i] << " is not appropriate " << i + 1 << " on position" << endl;
                p = 0;
                break;
            }
        }
    }
    
    // обработка дублирования в биграмме 
    for(int i = 0; i < code.length(); i++){
        if(code[i] == code[i + 1]) code.insert(i+1, 1, 'x');
    }
    
    // добавление символа в неполную биграмму 
    if(code.length() % 2 != 0) code.push_back('x');
    
    // формирование биграмм
    for(int i = 0; i < code.length(); i+=2){
        cout.width(5);
        cout << code[i] << code[i + 1];
    }
    cout << endl;
    
    // нахождение индексов в матрице
    for(int i = 0; i < code.length(); i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 5; k++){
                if(code[i] == matrix[j][k]){
                    index.push_back(j);
                    index.push_back(k);
                }
            }
        }
    }
    
    for(int i = 0; i < index.size(); i+=2) cout << index[i] << " " << index[i+1] << "   ";
    cout << endl;
    
    if(x == '1') Encode(index, matrix);
    if(x == '2') Decode(index, matrix);
    return 0;
}