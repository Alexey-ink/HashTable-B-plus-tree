#pragma once
#include <time.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>
#include <regex>
#include <algorithm>

using namespace std;

class InterNode;

class Node
{
	int M;
public:
	Node(int M);
	virtual ~Node();
	Node* GetBrother(int& flag);
	InterNode* Parent;
	vector<string> key;
	int count;              // 
	bool isLeaf;
	void Print();
};

class InterNode : public Node
{
	int M;
public:
	InterNode(int M);
	virtual ~InterNode();
	bool Insert(string value, Node* pNode);
	bool Delete(string value);
	string Split(InterNode* pNode, string key);
	bool Merge(InterNode* pNode);
	bool Slib(InterNode* pNode);
	string getMin();
	vector<Node*> Child;
};

class LeafNode : public Node
{
	int M;
public:
	LeafNode(int M);
	virtual ~LeafNode();
	bool Insert(string value);
	bool Delete(string value);
	string Split(LeafNode* pNode);
	bool Merge(LeafNode* pNode);
	LeafNode* Pre_Node;
	LeafNode* Next_Node;
};

class Bplus
{
	int M;
public:
	Bplus(int M);
	virtual ~Bplus();
	bool Search(string data, string& sPath);
	bool Insert(string data);
	bool Delete(string data);
	void Print();
	void loadFromFile(string path);
	void clear(Node* root);
	Node* Root;
protected:
	LeafNode* Find(string data);
	bool Add_Node(InterNode* pNode, string key, Node* New_Node);
	bool Remove_Node(InterNode* pNode, string key);
};
