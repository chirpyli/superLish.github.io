// 单向链表实现
#include<iostream>
using namespace std;

// 节点类
template<class T>
class Node {
public:
	Node() {
		next = 0;
	}
	Node(T e, Node* p = 0) :data(e), next(p) {}
	T data;			        //节点信息
	Node<T>* next;	        //下一节点地址
};

//单向链表类
template<class T>
class SList {
public:
	SList();
	virtual ~SList();
	bool isEmpty() {	     //是否为空链表
		return 0 == head;
	}
	void addToHead(T);       //在头结点添加新节点
	void addToTail(T);       //在尾节点添加新节点
	T deleteFromHead();		 //delete the head and return its data;
	T deleteFromTail();		 //delete the tail and return its data;
	void deleteNode(T);      //删除指定节点
	bool isInList(T) const;  //判断是否存在指定节点
private:
	Node<T>* head;	         //头节点
	Node<T>* tail;           //尾节点
};

template<class T>
SList<T>::SList() {
	head = tail = 0;
}

template<class T>
SList<T>::~SList(){
	for (Node<T>* p = 0; !isEmpty();) {
		p = head->next;
		delete head;
		head = p;
	}
}

template<class T>
void SList<T>::addToHead(T d) {
	head = new Node<T>(d, head);
	if (0 == tail) {
		tail = head;
	}
}

template<class T>
void SList<T>::addToTail(T d) {
    if (0 != tail) {    	// if list not empty;
		tail->next = new Node<T>(d);
		tail = tail->next;
	} else {
		head = tail = new Node<T>(d);
	}
}

template<class T>
T SList<T>::deleteFromHead() {
	if (isEmpty()) {
		return T();
	}

	T d = head->data;
	Node<T>* tmp = head;
	if (head == tail) {
		head = tail = 0;    // if only one node on the list;
	} else {
		head = head->next;
	}
	delete tmp;

	return d;
}

template<class T>
T SList<T>::deleteFromTail() {
	if (isEmpty()) {
		return T();
	}

	T d = tail->data;
	if (head == tail) { // if only one node on the list;
		delete tail;
		head = tail = 0;
	} else {             // if more than one node in the list
		Node<T>* tmp;
		for (tmp = head; tmp->next != tail; tmp = tmp->next);
		delete tail;
		tail = tmp;
		tail->next = 0;
	}
	return d;
}

template<class T>
void SList<T>::deleteNode(T d) {
	if (head != 0) {                 // if non-empty list;
		if (head == tail&&d == head->data) {    // if only one node on the list;
			delete head;
			head = tail = 0;
		} else if (d == head->data) {
			Node<T>* tmp = head;
			head = head->next;
			delete tmp;
		} else {
			Node<T> *pred, *tmp;
			for (pred = head, tmp = head->next; tmp != 0 && !(tmp->data == d); pred = pred->next, tmp = tmp->next);
			if (tmp != 0) {
				pred->next = tmp->next;
				if (tmp == tail)
					tail = pred;
				delete tmp;
			}
		}
	}
}

template<class T>
bool SList<T>::isInList(T d) const {
	Node<T>* tmp;
	for (tmp = head; tmp != 0 && !(tmp->data == d); tmp = tmp->next);
	return tmp != 0;
}
