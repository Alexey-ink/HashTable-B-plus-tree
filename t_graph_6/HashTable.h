#pragma once
#include <vector>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <cctype>

#include "LinkedList.h"

using namespace std;

class HashTable {

private: 
	LinkedList* table;

	int total_buckets;
	int total_elements = 0;
	double fillability;

	unsigned int hashFunction(const string& key);

public:

	HashTable(int size);
	void displayHashTable();
	void insert(const string& key);
	void remove(const string& key);
	int search(const string& key);
	void insertFromFile(const string& filename);
	
	void rehash();
	void clear();

	int getCount();
	
	~HashTable();

};


