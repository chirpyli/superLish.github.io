#pragma once
#include<cstdlib>
#include<ctime>
#include<random>
#include<cmath>
#include<iostream>
#include<cassert>
#include<queue>

using namespace std;
const int MAX_PRIORITY = 1024;


//队列实现
template<class T>
class Queue : public queue<T> {
public:
	T dequeue() {
		T tmp = queue<T>::front();
		queue<T>::pop();
		return tmp;
	}
	void enqueue(const T& el) {
		queue<T>::push(el);
	}
};


// 树节点类
template<class T>
class Node {
public:
	Node():left(NULL),right(NULL){
        priority = rand() % MAX_PRIORITY;
    }
	Node(const T& e, Node<T>* l = NULL, Node<T>* r = NULL, Node<T>* p = NULL):data(e),left(l),right(r),parent(p){
        priority = rand() % MAX_PRIORITY;
    }
	~Node(){}
	T data;     
    int priority;
    
	Node* left;
	Node* right;
	Node* parent;
};


template<class T>
class Treap {
public:
    Treap():root(NULL) {}
	void insert(const T &e);
	void remove(const T &e);	
    Node<T>* search(const T& e);
    void breadthFirst();		// 广度优先遍历
    virtual void visit(Node<T>* p) {
		cout << "<" << p->data << ", " << p->priority << "> ";
	}
protected:
    Node<T>* bst_insert(const T &e);
    void iter_remove(Node<T>* n, const T& e);
	void rotate_left(Node<T>* n);
    void rotate_right(Node<T>* n);
    Node<T>* root;

};

//广度优先遍历（从上到下，从左到右，一层一层的向下访问）
template<class T>
void Treap<T>::breadthFirst() {
	Queue<Node<T>*> m_queue;	//要理解这里为什么要用队列，这个队列的作用是把下一层的数据放到本层数据的后面
	Node<T>* p = root;
	if (p != NULL) {
		m_queue.enqueue(p);
		while (!m_queue.empty()) {
			p = m_queue.dequeue();
			visit(p);
			if (p->left != NULL)
				m_queue.enqueue(p->left);
            if (p->right != NULL)
				m_queue.enqueue(p->right);
		}
	}
}

template<class T>
Node<T>* Treap<T>::bst_insert(const T& el) {
    Node<T> *p = root, *prev = NULL;
	while (p != NULL) {  // find a place for inserting new node;
		prev = p;
		if (el < p->data)
			p = p->left;
		else p = p->right;
	}
	if (root == NULL) {   // tree is empty;
		root = new Node<T>(el);
        return root;
    } else if (el < prev->data) {
		prev->left = new Node<T>(el, NULL, NULL, prev);
        return prev->left;
    } else {
        prev->right = new Node<T>(el, NULL, NULL, prev);
        return prev->right;
    }
}


/*
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
 */
template<class T>
void Treap<T>::rotate_left(Node<T>* n) {
	Node<T>* y = n->right;
    Node<T>* t2 = y->left;

	if (n != this->root) {
		if (n->parent->left == n) 
			n->parent->left = y;
		else
			n->parent->right = y;
		y->parent = n->parent; 
	} else {
		this->root = y;
		y->parent = NULL;
	}

    y->left = n;
    n->right = t2;
	n->parent = y;
}

/*
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \                                  / \
 T1  T2                               T2  T3
 */
template<class T>
void Treap<T>::rotate_right(Node<T>* n) {
    Node<T>* x = n->left;
    Node<T>* t2 = x->right;

	if (n != this->root) {
		if (n->parent->left == n)
			n->parent->left = x;
		else
			n->parent->right = x;
		x->parent = n->parent;	
	} else {
		this->root = x;
		x->parent = NULL;
	}

    x->right = n;
    n->left = t2;
	n->parent = x;
}

template<class T>
Node<T>* Treap<T>::search(const T &e) {
    Node<T>* p = root;
	while (p != NULL) { 
		if (e == p->data) {
			cout << "search " << e << " " << endl;
            return p;
        } else if (e < p->data)
			p = p->left;
		else p = p->right;
	}
    
	return NULL;
}


template<class T>
void Treap<T>::insert(const T& e) {
    Node<T>* n = this->bst_insert(e);
    if (n == root || n == NULL)
        return; 

    while (n != root) {
        if (n->parent->priority > n->priority) {
            break;
        } else if (n->parent->left == n) {
            this->rotate_right(n->parent);
        } else if (n->parent->right == n) {
            this->rotate_left(n->parent);
        }
    }
}

template<class T>
void Treap<T>::iter_remove(Node<T>* n, const T& e) {
    if (e == n->data) {
        if (!n->left || !n->right) {
            Node<T>* tmp = n;
            if (!n->right) {
                n->left->parent = n->parent;
                n = n->left;
            } else { 
                n->right->parent = n->parent;
                n = n->right;
            }    
            delete tmp;
        } else {
            if (n->left->priority > n->right->priority) {
                this->rotate_right(n);
                this->iter_remove(n->right, e);
            } else {
                this->rotate_left(n);
                this->iter_remove(n->left, e);
            }
        }
    } else if (e < n->data) 
        this->iter_remove(n->left, e);
    else 
        this->iter_remove(n->right, e);
}


// todo: 代码还未完成
template<class T>
void Treap<T>::remove(const T& e) {
    Node<T>* x = this->search(e);
    if (x == NULL)
        return;
    // iter_remove(x, e);

    // this->visit(x);

    while (x->left != NULL && x->right != NULL) {
        if (x->left->priority > x->right->priority) {
            this->rotate_right(x);
        } else {
            this->rotate_left(x);
        }
    }

    this->breadthFirst();
    
    // if (x->left == NULL && x->right != NULL) {
    //     if (x->parent->left == x) {
    //         x->parent->left = x->right;
    //         x->right->parent = x->parent;
    //     } else {
    //         x->parent->right = x->right;
    //         x->right->parent = x->parent;
    //     }
 
    // } else if (x->left != NULL && x->right == NULL) {
    //     if (x->parent->left == x) {
    //         x->parent->left = x->left;
    //         x->left->parent = x->parent;
    //     } else {
    //         x->parent->right = x->left;
    //         x->left->parent = x->parent;
    //     }
    // } else if (x->left == NULL && x->right == NULL) {
    //     if (x->parent->left == x) 
    //         x->parent->left = NULL;
    //     else
    //         x->parent->right = NULL;        
    // }

    // delete x;    
}