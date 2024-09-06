#include "LinkedList.h"


void LinkedList::insert(const string& value) {
	Node* newNode = new Node(value);
	if (head == nullptr) {
		head = newNode;
	}
	else {
		Node* temp = head;
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
		Node* temp = head;
		head = head->next;
		delete temp;
		cout << "—лово успешно удалено! " << endl;
		return true;
	}


	Node* current = head;
	Node* previous = nullptr;

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
	Node* temp = head;

	while (temp != nullptr) {
		if (temp->data == value) {
			return true;
		}
		temp = temp->next;
	}
	return false;

}

void LinkedList::display() {
	Node* temp = head;
	while (temp != nullptr) {
		cout << temp->data; 
		if (temp->next != nullptr) {
			cout << "->";
		}
		temp = temp->next;
	}
}

void LinkedList::clear() {

	Node* current = head;
	while (current != nullptr) {
		Node* toDelete = current;
		current = current->next;
		delete toDelete; 
	}
	head = nullptr; 

}


