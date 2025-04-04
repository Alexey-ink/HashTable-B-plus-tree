#pragma once

#include <string>
#include <iostream>

using namespace std;

struct ListNode {

	string data;
	ListNode* next;

	ListNode(const string& value) : data(value), next(nullptr) {}
};


class LinkedList {

private: 
	ListNode* head;


public: 
	LinkedList() : head(nullptr) {}


	void insert(const string& value);
	bool remove(const string& value);
	bool search(const string& value);
	void display();
	void clear();

	ListNode* getHead() { return head; }

};