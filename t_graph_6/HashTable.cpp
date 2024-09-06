#include "HashTable.h"
#include <locale>

bool isAlphaNum(char c) {

	if (std::isalnum(static_cast<unsigned char>(c))) {
		return true;
	}

	return (c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я');
}


HashTable::HashTable(int size) {
	total_buckets = size;
	table = new LinkedList[total_buckets];
}

void HashTable::insert(const string& key) {

	int index = hashFunction(key);

	if (!search(key)) {

		table[index].insert(key);
		total_elements++;
		fillability = static_cast<double>(total_elements) / static_cast<double>(total_buckets);
	}
	
	if (fillability >= 0.9) {
		rehash();
	}
}

void HashTable::remove(const string& key) {

	int index = hashFunction(key);
	if (table[index].remove(key)) {
		total_elements--;
		fillability = static_cast<double>(total_elements) / static_cast<double>(total_buckets);
	}

	else cout << "\n Элемент не найден! " << endl;
}

bool HashTable::search(const string& key) {

	int index = hashFunction(key);
	if (table[index].search(key)) return true;
	else return false;

}


void HashTable::displayHashTable() {
	cout << endl;

	if (total_elements == 0) {
		cout << "Хэш-таблица пуста!" << endl;
	}
	else {
		for (int i = 0; i < total_buckets; i++) {
			cout << "[" << i << "]: ";
			table[i].display();
			cout << endl;
		}
	}
}


HashTable::~HashTable() {
	delete[] table;
}


unsigned int HashTable::hashFunction(const string& key) {

	unsigned int hash_value = 0;
	int a = 33; // основание полинома

	for (char c : key) {
		hash_value = (hash_value * a + static_cast<unsigned int>(c)) % total_buckets;
	}

	return hash_value;

}


void HashTable::insertFromFile(const string& filename) {
	
	ifstream file(filename);

	cout << "Fillability: " << fillability << endl;

	if (!file.is_open()) {
		cout << "Ошибка! Не удалось открыть файл!" << filename << endl;
		return;
	}

	string line, word;
	while (getline(file, line)) {

		stringstream ss(line);

		while (ss >> word) {

			transform(word.begin(), word.end(), word.begin(), ::tolower);
			word.erase(remove_if(word.begin(), word.end(), [](char c) {
				return !isAlphaNum(c);
				}), word.end());

			if (!word.empty()) { 
				insert(word);
				// cout << "Добавили " << word << endl;
			}
		}

	}

	cout << "Количество элементов: " << total_elements << endl;
	cout << "Fillability: " << fillability << endl;

}


void HashTable::rehash() {

	cout << "Пересоздаем таблицу..." << endl;

	int old_buckets = total_buckets;

	total_buckets *= 2;

	LinkedList* old_table = table; 
	table = new LinkedList[total_buckets];
	total_elements = 0;

	for (int i = 0; i < old_buckets; i++) {

		Node* temp = old_table[i].getHead();

		while (temp != nullptr) {
			insert(temp->data);
			temp = temp->next;
		}

	}

	delete[] old_table;

}

void HashTable::clear() {

	for (int i = 0; i < total_buckets; i++) {
		table[i].clear();
	}

	total_elements = 0;
	fillability = 0.0;

	cout << "Хэш-таблица полностью очищена!" << endl;

}


