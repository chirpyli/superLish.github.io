// 双向链表实现
#include<iostream>
using namespace std;

//节点类
template<class T>
class DNode {
public:
	DNode() {
		next = prev = 0;
	}
	DNode(const T& e, DNode* n = 0,DNode* p=0) :data(e), next(n),prev(p) {}
	T data;			        //节点信息
	DNode<T>* next;	        //下一节点地址
	DNode<T>* prev;	        //上一节点地址
};

//链表实现
template<class T>
class DList {
public:
	DList();
	virtual ~DList();
	bool isEmpty() {
		return 0 == head;
	}
	void addToHead(T);
	void addToTail(T);
	T deleteFromHead();		//delete the head and return its data;
	T deleteFromTail();		//delete the tail and return its data;
	void deleteDNode(T);
	bool isInList(T) const;
protected:
	DNode<T>* head;	//头节点
	DNode<T>* tail;	//尾节点
};

template<class T>
DList<T>::DList() {
	head = tail = 0;
}

template<class T>
DList<T>::~DList() {
	for (DNode<T>* p = 0; !isEmpty();) {
		p = head->next;
		delete head;
		head = p;
	}
}

template<class T>
void DList<T>::addToHead(T d) {
	head = new DNode<T>(d, head);
	if (0 == tail) {
		tail = head;
	}
}

template<class T>
void DList<T>::addToTail(T d) {
	if (0 != tail) {    // if list not empty;
		tail = new DNode<T>(d, 0, tail);
		tail->prev->next = tail;
	} else {
		head = tail = new DNode<T>(d);
	}
}

template<class T>
T DList<T>::deleteFromHead() {
	if (isEmpty()) {
		return T();
	}

	T d = head->data;
	DNode<T>* tmp = head;
	if (head == tail) {       // if only one DNode on the list;
		head = tail = 0;
	} else {
		head = head->next;
		head->prev = 0;
	}
	delete tmp;

	return d;
}

template<class T>
T DList<T>::deleteFromTail() {
	if (isEmpty()) {
		return T();
	}

	T d = tail->data;
	if (head == tail) {      // if only one DNode on the list;
		delete tail;
		head = tail = 0;
	} else {     // if more than one DNode in the list
		tail = tail->prev;
		delete tail->next;
		tail->next = 0;
	}
	return d;
}

template<class T>
void DList<T>::deleteDNode(T d) {
	if (head != 0) { // if non-empty list;
		if (head == tail && d == head->data) {       // if only one DNode on the list;
			delete head;
			head = tail = 0;
		} else if (d == head->data) {
			DNode<T>* tmp = head;
			head = head->next;
			head->prev = 0;
			delete tmp;
		} else if (d == tail->data) {
			DNode<T>* tmp = tail;
			tail = tail->prev;
			tail->next = 0;
			delete tmp;
		} else {
			DNode<T>*tmp;
			for (tmp = head->next; tmp != 0 && !(tmp->data == d); tmp = tmp->next);
			if (tmp != 0) {
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;
			}
		}
	}
}

template<class T>
bool DList<T>::isInList(T d) const {
	DNode<T>* tmp;
	for (tmp = head; tmp != 0 && !(tmp->data == d); tmp = tmp->next);
	return tmp != 0;
}
