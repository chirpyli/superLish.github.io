//循环单向链表的实现
#include<iostream>
using namespace std;

template<class T>
class Node {
public:
	Node() {
		next = 0;
	}
	Node(T e, Node* p = 0) :data(e), next(p) {}
	T data;			//节点信息
	Node<T>* next;	//下一节点地址
};

template<class T>
class CircleList {
public:
	CircleList();
	virtual ~CircleList();
	bool isEmpty() {
		return 0 == head;
	}
	size_t GetLength() const{	//获取循环链表长度
		return len;
	}

	void addToHead(T);
	T deleteFromHead();		//delete the head and return its data;
	void deleteNode(T);
	bool isInList(T);

protected:
	Node<T>* head;	//头节点
	size_t len;		//链表中节点个数
};

template<class T>
CircleList<T>::CircleList() {
	head = 0;
	len = 0;
}

template<class T>
CircleList<T>::~CircleList() {
	for (Node<T>* p = 0; !isEmpty();) {
		p = head->next;
		delete head;
		head = p;
	}
}

template<class T>
void CircleList<T>::addToHead(T d) {
	head = new Node<T>(d, head);
	if (0 == len) {
		head->next = head;
	} else {
		Node<T>* tmp;
		for (tmp = head->next; tmp->next != head->next; tmp = tmp->next);
		tmp->next = head;
	}
	++len;
}

template<class T>
T CircleList<T>::deleteFromHead() {
	if (isEmpty()) {
		return T();
	}

	T d = head->data;
	Node<T>* tmp = head;
	if (1 == len) {    // if only one node on the list;
		head = 0;
	} else {
		Node<T>* tmp;
		for (tmp = head->next; tmp->next != head; tmp = tmp->next);
		tmp->next = head->next;
		head = head->next;
	}
	delete tmp;
	--len;

	return d;
}

template<class T>
void CircleList<T>::deleteNode(T d) {
	if (head != 0) {     // if non-empty list;
		if (1 == len && d == head->data) {       // if only one node on the list;
			delete head;
			head = 0;
		} else {
			Node<T> *pred, *tmp;
			int size = len;
			for (pred = head, tmp = head->next; size > 0 && !(tmp->data == d); pred = pred->next, tmp = tmp->next,--size);
			if (size> 0) {
				pred->next = tmp->next;
				delete tmp;
			}
		}
		--len;
	}
}

template<class T>
bool CircleList<T>::isInList(T d) {
	if (len < 1)
		return false;

	Node<T>* tmp;
	for (tmp = head; len>0 && !(tmp->data == d); tmp = tmp->next,--len);
	return len > 0;
}
