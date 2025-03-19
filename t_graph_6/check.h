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
        if (cin.fail() || n < 0 || n > max || cin.peek() != '\n') {
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

    while (true) {
        getline(cin, str);

        bool valid = true;
        for (char c : str) {
            if (isspace(c) || !((c >= '�' && c <= '�') || (c >= '�' && c <= '�'))) {
                valid = false;
                break;
            }
        }

        if (valid) {
            return str;
        }
        else {
            cout << "������! ������� �����, ���������� ������ ������� ����� � ��� ��������!" << endl;
        }
    }
}




