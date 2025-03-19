
#include <iostream>
#include <algorithm>
#include <cctype> 
#include <locale>
#include <windows.h>

#include "HashTable.h"
#include "B-plus-tree.h"
#include "check.h"


using namespace std;

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");


    HashTable myHashTable(10);
    Bplus myTree(2);

    while (true) {

        cout << endl << " Хэш-таблица\n";

        cout << "\n  1. Вывести словарь на экран \n";
        cout << "  2. Дополнить словарь из текстового файла \n";
        cout << "  3. Добавить новое слово в словарь \n";
        cout << "  4. Поиск слова в словаре \n";
        cout << "  5. Удалить слово из словаря \n";
        cout << "  6. Очистить словарь \n";

        cout << "\n B+ дерево  \n\n";

        cout << "  7. Вывести словарь на экран \n";
        cout << "  8. Дополнить словарь из текстового файла \n";
        cout << "  9. Добавить новое слово в словарь \n";
        cout << "  10. Поиск слова в словаре \n";
        cout << "  11. Удалить слово из словаря \n";
        cout << "  12. Очистить словарь \n";
        
        cout << "  0. Выход из программы\n";

        cout << "\n Выберите действие: ";

        int b = checkingInput(12);
        string word;
        string path;
        bool flag;
        int index;

        switch (b) {

        case 1:

            myHashTable.displayHashTable();
            cout << endl << "Количество слов в словаре: " << myHashTable.getCount() << endl;
            break;

        case 2:

            myHashTable.insertFromFile("story.txt");
            break;

        case 3:
            cout << "Введите слово (без пробелов), которое хотите добавить: " << endl;
            clear();
            word = checkingString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            index = myHashTable.search(word);
            if (index != -1) {
                cout << "Слово уже есть в словаре!" << endl;
            }
            else {
                myHashTable.insert(word);
                cout << "Слово успешно добавлено! " << endl;

            }

            break;

        case 4:

            cout << "Введите слово, которое хотите найти: " << endl;
            clear();
            word = checkingString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            
            index = myHashTable.search(word);
            if (index != -1) {
                cout << "Слово " << word << " присутствует в словаре! " << endl;
                cout << "Индекс бакета: " << index << endl << endl;
            }
            else cout << "Слово " << word << " отсутствует в словаре! " << endl << endl;
   
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
            if (myTree.Root == NULL) {
                cout << "B+-дерево пустое" << endl;
                system("pause");
                continue;
            }
            myTree.Print();
            break;
        
        case 8:
            myTree.loadFromFile("story.txt");
            cout << "B+- дерево дополнено словами из файла" << endl;
            break;

        case 9:
            cout << "Введите слово (без пробелов), которое хотите добавить: " << endl;
            clear();
            word = checkingString();
            transform(word.begin(), word.end(), word.begin(), ::tolower);

            flag = myTree.Insert(word);
            if (flag) {
                cout << "Вставка прошла успешно" << endl;
            }
            else {
                cout << "Такое слово уже присутствует в B+-дереве" << endl;
            }
            cout << endl;

            break;

        case 10: 

            cout << "Введите слово, наличие которого хотите проверить: ";

            if (myTree.Root == NULL) {
                cout << "Словарь пустой" << endl;
                continue;
            }

            clear();
            word = checkingString();
            if (myTree.Search(word, path)) {
                cout << "Слово было найдено! " << endl;;
            }
            else {
                cout << "Слово не найдено в словаре" << endl;
            }

            break;
            
        case 11:

            if (myTree.Root == NULL) {
                cout << "Словарь пустой" << endl;
                continue;
            }

            cout << "Введите слово, которое хотите удалить: " << endl;
            clear();
            word = checkingString();
            flag = myTree.Delete(word);
            if (flag) {
                cout << "Удаление слова прошло успешно" << endl;
            }
            else {
                cout << "Такого слова в B+-дереве нет" << endl;
            }
            break;

        case 12:
            if (myTree.Root == NULL) {
                cout << "Словарь пустой" << endl;
                continue;
            }
            myTree.clear(myTree.Root);
            cout << "B+-дерево очищено" << endl;

            break;

        case 0:
            return 0;

        default:
            cout << "Ошибка!";
        }

        system("pause");
    }

    return 0;
}

