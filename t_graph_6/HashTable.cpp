#include "HashTable.h"
#include <locale>

static const int NOT_FOUND = -1;
static const double REHASH_THRESHOLD;

bool isAlphaNum(char c) {

	if (std::isalnum(static_cast<unsigned char>(c))) {
		return true;
	}

	return (c >= '�' && c <= '�') || (c >= '�' && c <= '�');
}


HashTable::HashTable(int size) {
	total_buckets = size;
	fillability = 0.0;
	table = new LinkedList[total_buckets];
}

void HashTable::insert(const string& key) {

	int index = hashFunction(key);

	if (search(key) == NOT_FOUND) {

		table[index].insert(key);
		total_elements++;
		fillability = static_cast<double>(total_elements) / static_cast<double>(total_buckets);
	}
	
	if (fillability >= REHASH_THRESHOLD) {
		rehash();
	}
}

void HashTable::remove(const string& key) {

	int index = hashFunction(key);
	if (table[index].remove(key)) {
		total_elements--;
		fillability = static_cast<double>(total_elements) / static_cast<double>(total_buckets);
	}

	else cout << "\n ������� �� ������! " << endl;
}

int HashTable::search(const string& key) {

	int index = hashFunction(key);
	if (table[index].search(key)) return index;
	else return NOT_FOUND;

}


void HashTable::displayHashTable() {
	cout << endl;

	if (total_elements == 0) {
		cout << "���-������� �����!" << endl;
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
	int a = 33; // ��������� ��������

	for (char c : key) {
		hash_value = (hash_value * a + static_cast<unsigned int>(c)) % total_buckets;
	}
		
	return hash_value;
}
		

void HashTable::insertFromFile(const string& filename) {
	
	ifstream file(filename);

	if (!file.is_open()) {
		cout << "������! �� ������� ������� ����!" << filename << endl;
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
				// cout << "�������� " << word << endl;
			}
		}

	}

	cout << "����� ������� ���������! " << endl << endl;

	// cout << "���������� ���������: " << total_elements << endl;
	// cout << "����. ������������� ���-�������: " << fillability << endl;
}


void HashTable::rehash() {

	// cout << "����������� �������..." << endl;

	int old_buckets = total_buckets;

	total_buckets *= 2;

	LinkedList* old_table = table; 
	table = new LinkedList[total_buckets];
	total_elements = 0;

	for (int i = 0; i < old_buckets; i++) {

		ListNode* temp = old_table[i].getHead();

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

	cout << "���-������� ��������� �������!" << endl;

}

int HashTable::getCount() {
	return total_elements;
}


