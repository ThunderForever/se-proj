#pragma once
#include<iostream>
#include<vector>
using namespace std;

using namespace std;

class Node {
public:
	int value;
	Node* next;
	Node(int v) : value(v), next(NULL) {}
	Node(int v, Node* link) :value(v), next(link) {}

	Node* getNext() { return next; }
};

class List {
public:

	List(const vector<int>& v);
	List(int* array, int array_size);
	int length() const;
	bool insert(int pos, int value);
	void printAll();
	int find(int value);
	int remove(int value);
	bool split(int pos, List& new_list);
	void combine(List& append_list);

	~List();
private:
	int size;
	Node* head;
};

//构造函数

List::List(const vector<int>& v) {
	size = v.size();
	if (size > 0) {			//检查向量v是否为空
		head = new Node(v[size - 1]);
		if (size > 1) {
			for (int i = size - 2; i >= 0; i--) {
				head = new Node(v[i], head);
			}
		}
	}
}

List::List(int* array, int array_size) {
	size = array_size;
	if (size > 0) {			//检查array_size是否为0
		head = new Node(array[size - 1]);
		if (size > 1) {
			for (int i = size - 2; i >= 0; i--) {
				head = new Node(array[i], head);
			}
		}
	}

}
//函数实现
int List::length() const { return List::size; };

bool List::insert(int pos, int value) {
	if (pos >= 0 && pos < size) {
		if (pos == 0) {
			head = new Node(value, head);
		}
		if (pos > 0) {
			Node* position = head->next;
			if (pos == 1) { Node* p = new Node(value, position); head->next = p; }
			else {
				Node* pre = position;
				for (int i = 2; i <= pos; i++) {
					pre = position;
					position = position->next;
				}
				Node* p = new Node(value, position);
				pre->next = p;
			}

		}
		size++;
		return true;
	}
	else {
		return false;
	}
}

void List::printAll() {
	Node* position = head;
	if (size == 1) {
		cout << head->value << ' ';
	}
	else if (size == 0) {
		cout << "no element" << endl;
	}
	else {
		cout << position->value << ' ';
		while (!(position->next == NULL)) {
			position = position->next;
			cout << position->value << ' ';
		}
	}
	cout << endl;
}

int List::find(int value) {
	Node* position = head;
	bool found = false;
	int pos = 0;
	while (!(position == NULL)) {
		if (position->value == value) {
			return pos;
			found = true;
			break;
		}
		else {
			pos++;
			position = position->next;
		}
	}
	if (!found) { return -1; }
}

List::~List() {
	Node* p =head;
	while (!p == NULL) {
		head = p;
		p = p->next;
		delete head;
	}
}

int List::remove(int value) {
	int pos = find(value);
	int times = 0;
	while (pos != -1) {
		if (pos == 0) {
			head = head->next;
			times++;
			size--;
		}
		else {
			Node* nextOne = head->next;
			Node* pre = head;
			if (pos == 1) {
				if (nextOne->next == NULL) { pre->next = NULL; }
				else { pre->next = nextOne->next; }
			}
			else {
				for (int i = 2; i <= pos; i++) {
					nextOne = nextOne->next;
					pre = pre->next;
				}
				if (nextOne->next == NULL) { pre->next = NULL; }
				else { pre->next = nextOne->next; }
			}
			times++;
			size--;
		}
		pos = find(value);

	}
	return times;
}

bool List::split(int pos, List& new_list) {
	Node* p = head;
	
	if (pos >= 0 && pos <= size - 1) {
		if (pos == 0) {
			new_list.head = p->next;
			p->next = NULL;
			new_list.size = size - 1;
			size = 1;
		}
		else {
			for (int i = 1; i <= pos ; i++) {
				p = p->next;
			}
			new_list.head = p->next;
			p->next = NULL;
			new_list.size = size - pos - 1;
			size = pos + 1;
		}
		return true;
	}
	else {
		return false;
	}
}

void List::combine(List& append_list) {
	Node* p = head;
	for (int i = 0; i <= size - 2; i++) {
		p = p->next;
	}
	p->next = append_list.head;
	size = size + append_list.size;
}