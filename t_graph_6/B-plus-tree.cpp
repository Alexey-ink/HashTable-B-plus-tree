#include "B-plus-tree.h"

Node::~Node() {}

InterNode::~InterNode() {
	for (int i = 0; i < M * 2; i++) /////
		Child[i] = NULL;
}

LeafNode::~LeafNode() {}

Bplus::~Bplus() {};

Node::Node(int M)
{
	isLeaf = true;
	count = 0;
	Parent = NULL;
	this->M = M;
	key = vector<string>(M * 2 - 1, ""); /////
};

LeafNode::LeafNode(int M) : Node(M)
{
	this->M = M;
	isLeaf = true;
	Pre_Node = NULL;
	Next_Node = NULL;
}

InterNode::InterNode(int M) : Node(M) {
	this->M = M;
	isLeaf = false;
	Child = vector<Node*>(M * 2, NULL); /////
}

Bplus::Bplus(int M) {
	this->M = M;
	Root = NULL;
}

string InterNode::getMin() {
	InterNode* p = this;
	while (p != NULL) {
		if (p->Child[0]->isLeaf) {
			return p->Child[0]->key[0];
		}
		p = (InterNode*)p->Child[0];
	}
}

Node* Node::GetBrother(int& flag) {
	if (Parent == NULL)
		return NULL;

	Node* p = NULL;
	for (int i = 0; i <= Parent->count; i++) {
		if (Parent->Child[i] == this) {
			if (i == Parent->count) {
				p = Parent->Child[i - 1];
				flag = 1;
			}
			else {
				p = Parent->Child[i + 1];
				flag = 2;
			}
		}
	}
	return p;
}

void Node::Print() {
	for (int i = 0; i < count; i++) {
		cout << "" << key[i] << "  ";
		if (i >= count - 1)
			cout << " | ";
	}
}

string LeafNode::Split(LeafNode* p) {
	int j = 0;
	for (int i = M - 1; i < M * 2 - 1; i++, j++) /////
		p->key[j] = this->key[i];

	this->count = this->count - j;
	p->count = j;
	return p->key[0];
}

bool LeafNode::Delete(string value)
{
	bool found = false;
	int i = 0;
	for (; i < count; i++) {
		if (value == key[i]) {
			found = true;
			break;
		}
	}
	if (found == false)
		return false;
	int j = i;
	for (; j < count - 1; j++)
		key[j] = key[j + 1];
	key[j] = "";
	count--;
	return true;
}

bool LeafNode::Insert(string value) {
	int i = 0;
	for (; (value > key[i]) && (i < count); i++);

	for (int j = count; j > i; j--)
		key[j] = key[j - 1];

	key[i] = value;
	count++;
	return true;
}

LeafNode* Bplus::Find(string data) {
	int i = 0;
	Node* p = Root;
	InterNode* q;

	while (NULL != p) {
		if (p->isLeaf)
			break;
		for (i = 0; i < p->count; i++) {
			if (data < p->key[i])
				break;
		}
		q = (InterNode*)p;
		p = q->Child[i];
	}
	return (LeafNode*)p;
}


bool LeafNode::Merge(LeafNode* p) {
	if (this->count + p->count > M * 2 - 1) /////
		return false;
	for (int i = 0; i < p->count; i++)
		this->Insert(p->key[i]);
	return true;
}

bool InterNode::Merge(InterNode* p) {
	key[count] = p->Child[0]->key[0];
	count++;
	Child[count] = p->Child[0];
	Child[count]->Parent = this;
	for (int i = 0; i < p->count; i++) {
		key[count] = p->key[i];
		count++;
		Child[count] = p->Child[i + 1];
		Child[count]->Parent = this;
	}
	return true;
}

bool InterNode::Insert(string value, Node* New) {
	int i = 0;
	for (; (i < count) && (value > key[i]); i++);

	for (int j = count; j > i; j--)
		key[j] = key[j - 1];

	for (int j = count + 1; j > i + 1; j--)
		Child[j] = Child[j - 1];

	key[i] = value;
	Child[i + 1] = New;
	New->Parent = this;
	count++;
	return true;
}

string InterNode::Split(InterNode* p, string k) {
	int i = 0, j = 0;

	//int pos = k < this->key[M - 1] ? (M - 1) : (M); /////
	int pos = M - 1;
	k = this->key[pos];
	j = 0;
	for (i = pos + 1; i < M * 2 - 1; i++, j++)  /////
		p->key[j] = this->key[i];
	j = 0;
	for (i = pos + 1; i <= M * 2 - 1; i++, j++) { /////
		this->Child[i]->Parent = p;
		p->Child[j] = this->Child[i];
	}
	this->count = pos; /////
	p->count = M * 2 - pos - 2; /////
	return k;
}

// удаление ключа во внутреннем узле
bool InterNode::Delete(string k) {
	int i = 0;
	for (; (k >= key[i]) && (i < count); i++);

	for (int j = i - 1; j < count - 1; j++)
		key[j] = key[j + 1];

	int d = i;
	for (; d < count; d++) {
		Child[d] = Child[d + 1];
	}
	Child[d] = NULL;
	count--;
	return true;
}

bool InterNode::Slib(InterNode* p) {
	int i, j;
	if (p->key[0] < this->key[0]) {
		for (i = count; i > 0; i--)
			key[i] = key[i - 1];
		for (j = count + 1; j > 0; j--)
			Child[j] = Child[j - 1];
		key[0] = Child[0]->key[0];
		Child[0] = p->Child[p->count];
		Child[0]->Parent = this;
	}
	else {
		key[count] = p->Child[0]->key[0];
		Child[count + 1] = p->Child[0];
		Child[count + 1]->Parent = this;
		for (i = 1; i < p->count; i++)
			p->key[i - 1] = p->key[i];
		for (j = 0; j < p->count; j++)
			p->Child[j] = p->Child[j + 1];
	}
	this->count++;
	p->count--;
	return true;
}

bool Bplus::Add_Node(InterNode* p, string k, Node* New_Node) {
	if (p == NULL || p->isLeaf)
		return false;
	if (p->count < M * 2 - 1) /////
		return p->Insert(k, New_Node);

	InterNode* Brother = new InterNode(M);
	string NewKey = p->Split(Brother, k);

	if (Brother->Child[0]->key[0] < k) {
		Brother->Insert(k, New_Node);
	}
	else {
		p->Insert(k, New_Node);
	}

	InterNode* parent = (InterNode*)(p->Parent);
	if (parent == NULL) {
		parent = new InterNode(M);
		parent->Child[0] = p;
		parent->key[0] = NewKey;
		parent->Child[1] = Brother;
		p->Parent = parent;
		Brother->Parent = parent;
		parent->count = 1;
		Root = parent;
		return true;
	}
	return Add_Node(parent, NewKey, Brother);
}

bool Bplus::Search(string data, string& sPath) {
	int i = 0;
	sPath = "Путь к данным: ";
	Node* p = Root;
	if (p == NULL)
		return false;
	InterNode* q;
	while (p != NULL) {
		if (p->isLeaf)
			break;
		for (i = 0; (i < p->count) && (data >= p->key[i]); i++);
		int k = i > 0 ? i - 1 : i;
		sPath += p->key[k];
		sPath += "-->";
		q = (InterNode*)p;
		p = q->Child[i];
	}
	if (p == NULL)
		return false;
	sPath += p->key[0];
	bool found = false;
	for (i = 0; i < p->count; i++) {
		if (data == p->key[i])
			found = true;
	}
	if (found) sPath += " OK";
	else sPath += " FAIL";
	return found;
}

bool Bplus::Insert(string data) {
	string a;
	if (Search(data, a) == true)
		return false;

	LeafNode* Old_Node = Find(data);

	if (NULL == Old_Node) {
		Old_Node = new LeafNode(M);
		Root = Old_Node;
	}

	if (Old_Node->count < M * 2 - 1) /////
		return Old_Node->Insert(data);

	LeafNode* New_Node = new LeafNode(M);

	string k = Old_Node->Split(New_Node);

	LeafNode* OldNext = Old_Node->Next_Node;
	Old_Node->Next_Node = New_Node;
	New_Node->Next_Node = OldNext;
	New_Node->Pre_Node = Old_Node;

	if (OldNext != NULL)
		OldNext->Pre_Node = New_Node;

	if (data < k) {
		Old_Node->Insert(data);
	}
	else {
		New_Node->Insert(data);
	}
	InterNode* parent = (InterNode*)(Old_Node->Parent);

	if (parent == NULL) {
		InterNode* New_Root = new InterNode(M);
		New_Root->Child[0] = Old_Node;
		New_Root->key[0] = k;
		New_Root->Child[1] = New_Node;
		Old_Node->Parent = New_Root;
		New_Node->Parent = New_Root;
		New_Root->count = 1;
		Root = New_Root;
		return true;
	}

	return Add_Node(parent, k, New_Node);
}

bool Bplus::Delete(string data) {
	LeafNode* Old_Node = Find(data);
	string NewKey = Old_Node->key[0];
	if (Old_Node == NULL)
		return false;
	if (false == Old_Node->Delete(data))
		return false;

	InterNode* parent = (InterNode*)(Old_Node->Parent);
	if (NULL == parent || parent->Child.size() == 0) {
		if (0 == Old_Node->count) {
			delete Old_Node;
			Root = NULL;
		}
		return true;
	}
	if (Old_Node->count >= M - 1) { /////
		//for (int i = 0; (i < parent->count) && (data >= parent->key[i]); i++) {
		//	if (parent->key[i] == data)
		//		parent->key[i] = Old_Node->key[0];
		//}
		for (int i = 0; (i < parent->count) && (data >= parent->key[i]); i++) {
			if (parent->Child[i + 1]->isLeaf) {
				parent->key[i] = parent->Child[i + 1]->key[0];
			}
			else {
				parent->key[i] = static_cast<InterNode*>(parent->Child[i + 1])->getMin();
			}
		}
		return true;
	}

	int flag = 1;
	LeafNode* Brother = (LeafNode*)(Old_Node->GetBrother(flag));
	string NewData = "";
	if (Brother->count > M - 1) { /////
		if (1 == flag) {
			NewData = Brother->key[Brother->count - 1];
		}
		else {
			NewData = Brother->key[0];
		}
		Old_Node->Insert(NewData);
		Brother->Delete(NewData);

		if (1 == flag) {
			for (int i = 0; i <= parent->count; i++) {
				if (parent->Child[i] == Old_Node && i > 0)
					parent->key[i - 1] = Old_Node->key[0];
			}
		}
		else {
			for (int i = 0; i <= parent->count; i++) {
				if (parent->Child[i] == Old_Node && i > 0)
					parent->key[i - 1] = Old_Node->key[0];
				if (parent->Child[i] == Brother && i > 0)
					parent->key[i - 1] = Brother->key[0];
			}
		}
		return true;
	}

	if (1 == flag) {
		Brother->Merge(Old_Node);
		NewKey = Old_Node->key[0];
		LeafNode* OldNext = Old_Node->Next_Node;
		Brother->Next_Node = OldNext;
		if (NULL != OldNext)
			OldNext->Pre_Node = Brother;
		delete Old_Node;
	}
	else {
		Old_Node->Merge(Brother);
		NewKey = Brother->key[0];
		LeafNode* OldNext = Brother->Next_Node;
		Old_Node->Next_Node = OldNext;
		if (NULL != OldNext)
			OldNext->Pre_Node = Old_Node;

		delete Brother;
	}
	return Remove_Node(parent, NewKey);
}

bool Bplus::Remove_Node(InterNode* p, string k) {
	if (k == "")
		return false;

	if (false == p->Delete(k))
		return false;

	InterNode* parent = (InterNode*)(p->Parent);
	if (NULL == parent || parent->Child.size() == 0) {
		if (0 == p->count) {
			Root = p->Child[0];
			delete p;
		}
		return true;
	}

	if (p->count >= M - 1) { /////
		for (int i = 0; (i < parent->count) && (k >= parent->key[i]); i++) { // обновляем ключи в родителе если надо
			if (parent->key[i] == k)
				parent->key[i] = p->getMin();
		}
		for (int i = 0; i < p->count; i++) { // обновляем ключи в узле относительно правого ребёнка
			if (p->Child[i + 1]->isLeaf) {
				p->key[i] = p->Child[i + 1]->key[0];
			}
			else {
				p->key[i] = static_cast<InterNode*>(p->Child[i + 1])->getMin();
			}
		}

		return true;
	}
	int flag = 1;
	InterNode* Brother = (InterNode*)(p->GetBrother(flag));
	if (Brother->count > M - 1) { /////
		p->Slib(Brother);

		for (int i = 0; i < Brother->count; i++) { // обновляем ключи у узла, откуда перенесли
			if (Brother->Child[i + 1]->isLeaf) {
				Brother->key[i] = Brother->Child[i + 1]->key[0];
			}
			else {
				Brother->key[i] = static_cast<InterNode*>(Brother->Child[i + 1])->getMin();
			}
		}
		for (int i = 0; i < p->count; i++) { // обновляем ключи у узла, куда перенесли
			if (p->Child[i + 1]->isLeaf) {
				p->key[i] = p->Child[i + 1]->key[0];
			}
			else {
				p->key[i] = static_cast<InterNode*>(p->Child[i + 1])->getMin();
			}
		}
		for (int i = 0; i <= parent->count; i++) {  // обновляем ключи у родителя
			if (parent->Child[i] == p && i > 0)
				parent->key[i - 1] = p->getMin();
			if (parent->Child[i] == Brother && i > 0)
				parent->key[i - 1] = Brother->getMin();
		}
		return true;
	}
	string NewKey = "";
	if (1 == flag) {
		Brother->Merge(p);
		for (int i = 0; i < Brother->count; i++) { // обновляем ключи в узле
			if (Brother->Child[i + 1]->isLeaf) {
				Brother->key[i] = Brother->Child[i + 1]->key[0];
			}
			else {
				Brother->key[i] = static_cast<InterNode*>(Brother->Child[i + 1])->getMin();
			}
		}
		NewKey = p->key[0];
		delete p;
	}
	else {
		p->Merge(Brother);
		for (int i = 0; i < p->count; i++) { // обновляем ключи в узле
			if (p->Child[i + 1]->isLeaf) {
				p->key[i] = p->Child[i + 1]->key[0];
			}
			else {
				p->key[i] = static_cast<InterNode*>(p->Child[i + 1])->getMin();
			}
		}
		NewKey = Brother->key[0];
		delete Brother;
	}
	return Remove_Node(parent, NewKey);
}

void Bplus::Print() {
	Node* p = Root;
	if (NULL == p)
		return;

	InterNode* a;
	int H = 0;
	queue<Node*> q;
	queue<int> h;
	q.push(p);
	h.push(1);
	while (!q.empty()) {
		p = q.front();
		if (H != h.front()) {
			cout << endl;
			cout << "Уровень: " << H << endl;
			H = h.front();
		}
		q.pop();
		h.pop();
		p->Print();
		if (NULL != p && !p->isLeaf) {
			a = (InterNode*)p;
			for (int i = 0; i <= p->count; i++) {
				q.push(a->Child[i]);
				h.push(H + 1);
			}
		}
	}
	cout << endl;
}


void Bplus::loadFromFile(string path) {
	ifstream file(path, ios::in);
	stringstream ss;
	ss << file.rdbuf();
	string editedFileString;
	editedFileString = regex_replace(ss.str(), regex("[^а-яА-Я]"), " "); // убираем небуквенные символы
	istringstream input{ editedFileString };

	cout << endl;

	int counter = 0;
	while (!input.eof()) {
		string substring;
		input >> substring;
		transform(substring.begin(), substring.end(), substring.begin(), ::tolower); // приводим слово к нижнему регистру
		if (Search(substring, path)) {
			cout << "Слово '" << substring << "' уже есть в словаре" << endl;;
		}
		Insert(substring);
		Print();
		cout << endl;
		counter++;
		if (counter == 30) return;
	}
}

void Bplus::clear(Node* root) {
	for (int i = 0; i < root->count + 1; i++) {
		if (root->isLeaf) {
			Root = NULL;
			delete root;
			root = NULL;
			return;
		}
		else {
			clear(((InterNode*)root)->Child[i]);
		}
	}
	if (root == Root) {
		Root = NULL;
		delete root;
		root = NULL;
	}
	else {
		delete root;
		root = NULL;
	}
}