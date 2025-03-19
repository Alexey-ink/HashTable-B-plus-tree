#include "LinkedList.h"


void LinkedList::insert(const string& value) {
	ListNode* newNode = new ListNode(value);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		ListNode* temp = head;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = newNode;
	}
}


bool LinkedList::remove(const string& value) {
	if (head == nullptr) {
		// cout << "Ёлемент не найден!" << endl;
		return false;
	}

	if (head->data == value) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
		cout << "—лово успешно удалено! " << endl;
		return true;
	}


	ListNode* current = head;
	ListNode* previous = nullptr;

	while (current != nullptr && current->data != value) {
		previous = current;
		current = current->next;
	}

	if (current == nullptr) {
		// cout << "Ёлемент " << value << "не найден!!!" << endl;
		return false;
	}

	previous->next = current->next;
	delete current;
	cout << "—лово успешно удалено! " << endl;
	return true;

}


bool LinkedList::search(const string& value) {
	ListNode* temp = head;

	while (temp != nullptr) {
		if (temp->data == value) {
			return true;
		}
		temp = temp->next;
	}
	return false;

}

void LinkedList::display() {
	ListNode* temp = head;
	while (temp != nullptr) {
		cout << temp->data; 
		if (temp->next != nullptr) {
			cout << "->";
		}
		temp = temp->next;
	}
}

void LinkedList::clear() {

	ListNode* current = head;
	while (current != nullptr) {
		ListNode* toDelete = current;
		current = current->next;
		delete toDelete; 
	}
	head = nullptr; 

}


