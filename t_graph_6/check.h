#pragma once
#include <iostream>
#include <limits>
using namespace std;

void clear() {
    while (getchar() != '\n');
}

int checkingInput(int max) {

    int n;

    while (true) {
        cin >> n;
        // Проверяем, является ли введенное значение целым числом и находится в допустимых пределах
        if (cin.fail() || n < 0 || n > max || cin.peek() != '\n') {
            cin.clear();
            clear();
            cout << "Ошибка! Некорректный ввод!" << endl;
        }
        else {
            break; 
        }
    }
    return n;
}


string checkingString() {
    string str;

    while (true) {
        getline(cin, str);

        bool valid = true;
        for (char c : str) {
            if (isspace(c) || !((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я'))) {
                valid = false;
                break;
            }
        }

        if (valid) {
            return str;
        }
        else {
            cout << "Ошибка! Введите слово, содержащее только русские буквы и без пробелов!" << endl;
        }
    }
}




