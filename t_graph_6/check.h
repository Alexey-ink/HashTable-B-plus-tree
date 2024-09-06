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
        // ���������, �������� �� ��������� �������� ����� ������ � ��������� � ���������� ��������
        if (cin.fail() || n <= 0 || n > max || cin.peek() != '\n') {
            cin.clear();
            clear();
            cout << "������! ������������ ����!" << endl;
        }
        else {
            break; 
        }
    }
    return n;
}


string checkingString() {
    string str;

    bool haveSpace = false;

    while(true) {

        getline(cin, str);
        haveSpace = false;

        for (char c : str) {
            if (isspace(c)) {
                haveSpace = true;
            }
        }

        if (haveSpace) {
            cout << "������! ������� ����� ��� ��������!" << endl;
        }
        else return str;
    }
    return str;
}




