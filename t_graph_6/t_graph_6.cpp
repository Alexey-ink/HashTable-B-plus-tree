
#include <iostream>
#include <algorithm>
#include <cctype> 
#include <locale>
#include <windows.h>

#include "HashTable.h"
#include "check.h"


using namespace std;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    cout << endl << " Хэш-таблица\n";


    HashTable myHashTable(10);

    while (true) {

        cout << "\n  1. Вывести словарь на экран \n";
        cout << "  2. Дополнить словарь из текстового файла \n";
        cout << "  3. Добавить новое слово в словарь \n";
        cout << "  4. Поиск слова в словаре \n";
        cout << "  5. Удалить слово из словаря \n";
        cout << "  6. Очистить словарь \n";

        
        
        cout << "  7. Выход\n";

        cout << "\n B+ дерево (пока не реализовано) \n";
        cout << "\n Выберите действие: ";

        int b = checkingInput(7);
        string word;

        switch (b) {

        case 1:

            myHashTable.displayHashTable();
            break;

        case 2:

            myHashTable.insertFromFile("story.txt");
            break;

        case 3:
            cout << "Введите слово (без пробелов), которое хотите добавить: " << endl;
            clear();
            word = checkingString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (myHashTable.search(word)) {
                cout << "Слово уже есть в словаре!" << endl;
            }
            else {
                myHashTable.insert(word);
                cout << "Слово успешно добавлено! " << endl;

            }

            break;

        case 4:

            cout << "Введите слово, наличие которого хотите проверить: " << endl;
            clear();
            word = checkingString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            if (myHashTable.search(word)) {
                cout << "Слово " << word << " присутствует в словаре! " << endl;
            }
            else cout << "Слово " << word << " отсутствует в словаре! " << endl;
   
            break;

        case 5:

            cout << "Введите слово, которое хотите удалить: " << endl;
            clear();
            word = checkingString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            myHashTable.remove(word);
            break;

        case 6:
            myHashTable.clear();
            break;

        case 7:
            return 0;

        default:
            cout << "Ошибка!";
        }

    }


    return 0;
}

