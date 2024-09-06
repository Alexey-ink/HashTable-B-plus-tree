#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Node {

	string data;
	Node* next;

	Node(const string& value) : data(value), next(nullptr) {}
};


class LinkedList {

private: 
	Node* head;


public: 
	LinkedList() : head(nullptr) {}


	void insert(const string& value);
	bool remove(const string& value);
	bool search(const string& value);
	void display();
	void clear();

	Node* getHead() { return head; }

};