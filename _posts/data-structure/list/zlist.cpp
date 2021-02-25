// 自组织链表（前移法）实现
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

// 单向链表类
template<class T>
class ZList {
public:
	ZList();
	virtual ~ZList();
	bool isEmpty() {	     //是否为空链表
		return 0 == head;
	}
	void addToHead(T);       //在头结点添加新节点
	void deleteNode(T);      //删除指定节点
	void visit(T);           //访问指定节点
    void print();
private:
	Node<T>* head;	         //头节点
};

template<class T>
ZList<T>::ZList() {
	head = 0;
}

template<class T>
ZList<T>::~ZList(){
	for (Node<T>* p = 0; !isEmpty();) {
		p = head->next;
		delete head;
		head = p;
	}
}

template<class T>
void ZList<T>::print() {
    Node<T>* p = head;
    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}


template<class T>
void ZList<T>::addToHead(T d) {
	head = new Node<T>(d, head);
}

template<class T>
void ZList<T>::deleteNode(T d) {
	if (head == 0) {                 // if non-empty list;
        return;
	} else if (head->data == d) {
        Node<T>* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    Node<T>* p = head;
    while (p->next != NULL && p->next->data != d) {
        p = p->next;
    }
    if (p->next != NULL) {
        Node<T>* tmp = p->next;
        p->next = tmp->next;
        delete tmp;
    }
}

template<class T>
void ZList<T>::visit(T d) {
	if (head == 0) {                 // if non-empty list;
        return;
	} else if (head->data == d) {
        cout << "visit " << d << endl;
        return;
    }

	Node<T>* p = head;
    while (p->next != NULL && p->next->data != d) {
        p = p->next;
    }
    if (p->next != NULL) {
        Node<T>* tmp = p->next;
        p->next = tmp->next;
        Node<T>* tmp_head = head;
        head = tmp;
        head->next = tmp_head;
    }
}


int main() {
    ZList<int> list;
    list.addToHead(10);
    list.addToHead(20);
    list.addToHead(30);
    list.print();
    list.visit(10);
    list.print();


    return 0;
}