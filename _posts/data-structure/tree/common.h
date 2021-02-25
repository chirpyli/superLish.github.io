#pragma once
#include<iostream>
#include<list>
#include<cassert>
#include<stack>
#include<queue>
using namespace std;

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
	Node():left(NULL),right(NULL){}
	Node(const T& e, Node* l = NULL, Node* r = NULL):data(e),left(l),right(r) {}
	~Node(){}
	T data;     
	Node* left;
	Node* right;
};

template<class T>
class TreapNode: public Node<T> {
public:
    int priority;
};



template<class T, class N>
class BST {
public:
	BST():root(NULL),count(0) {}
	BST(T* a, int len, bool balance = false);	//根据数组中的数据构造树，调试测试用
	~BST() {
		clear();
	}
	bool isEmpty() const {
		return NULL == root;
	}
	void clear() {
		clear(root);
		root = NULL;
	}
	virtual N* insert(const T &e);		// 插入
	virtual bool remove(const T &e);	// 删除二叉查找树中指定的值
    virtual bool search(const T &e);
	void breadthFirst();		// 广度优先遍历

protected:
	N* root; //根节点
    int count;
	void clear(N*);
    void balance(T* data, int first, int last);		// 初始构建平衡树
    bool remove(const T&x, N*& t) const;
	void recursiveInsert(N*&, const T&);	
    N* findMin(N* t) const;		//迭代方式实现
	N* findMax(N* t) const;
	virtual void visit(N* p) {
		cout << p->data << ' ';
	}
	void rotate_left(N* n);
    void rotate_right(N* n);
};

// 根据数组中的内容构造树
template<class T, class N>
BST<T, N>::BST(T* a, int len, bool balance) {
	assert(a != NULL);
	root = NULL;
	if (balance == true) {
		this->balance(a, 0, len - 1);
	} else {
		for (int i = 0; i < len; i++) {
			insert(a[i]);
		}
	}
}

template<class T, class N>
void BST<T, N>::balance(T* data, int first, int last) {
	if (first <= last) {
		int middle = (first + last) >> 1;
		this->insert(data[middle]);
		balance(data, first, middle - 1);
		balance(data, middle + 1, last);
	}
}

// 清除节点p及其子节点
template<class T, class N>
void BST<T, N>::clear(N *p) {
	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
    count = 0;
}

//插入，递归实现
template<class T, class N>
void BST<T, N>::recursiveInsert(N*& p, const T& el) {
	if (p == NULL)
		p = new N(el);
	else if (el < p->data)
		recursiveInsert(p->left, el);
	else recursiveInsert(p->right, el);
}

//插入，非递归形式
template<class T, class N>
N* BST<T, N>::insert(const T& el) {
	N *p = root;
	while (p != NULL) {  // find a place for inserting new node;
		prev = p;
		if (el < p->data)
			p = p->left;
		else p = p->right;
	}
	if (root == NULL)    // tree is empty;
		root = new N(el);
	else if (el < prev->data)
		prev->left = new N(el, NULL, NULL);
	else prev->right = new N(el, NULL, NULL);

    ++count;
}


// 这里采用的方法一，选择右子树中最小值节点
template<class T, class N>
bool BST<T, N>::remove(const T& x, N* &t) const {
	if(NULL == t)
		return false;
	// 移除一个节点稍微麻烦一点，因为移除一个节点后二叉树需要将移除的位置再填一个节点过去
	if(x < t->data) {
		remove(x, t->left);
	} else if(x > t->data) {
		remove(x, t->right);
	} else if(t->left != NULL && t->right != NULL) {
		//拥有2个子节点
		t->data = findMin(t->right)->data;	//当前元素用右子树最小值填充
		remove(t->data, t->right);		//填充值被移走了，需要删除原填充值
	} else if(t->left == NULL && t->right == NULL) {
		//没有子节点，最简单的情况，直接删掉
		delete t;
		t = NULL;
	} else if(t->left == NULL || t->right == NULL) {
		//拥有一个子节点
		N* p = t;
		t = (t->left != NULL)?t->left:t->right;//用其子节点占据删除掉的位置；
		delete p;//直接删除对应的节点
	}

    return true;
}

//删除指定元素
template<class T, class N>
bool BST<T, N>::remove(const T& x) {
	bool r = remove(x, root);
    if (r == true) {
        --count;
    }

    return r;
}

//查找
template<class T, class N>
bool BST<T, N>::search(const T &e) {
    N* p = root;
	while (p != NULL) { 
		if (e == p->data) {
			cout << "search " << e << " " << endl;
            return true;
        } else if (e < p->data)
			p = p->left;
		else p = p->right;
	}
    
	return false;
}

//广度优先遍历（从上到下，从左到右，一层一层的向下访问）
template<class T, class N>
void BST<T, N>::breadthFirst() {
	Queue<N*> m_queue;	//要理解这里为什么要用队列，这个队列的作用是把下一层的数据放到本层数据的后面
	N* p = root;
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

//这段代码是实现查找最大值和最小值的代码
/*思路：我们可以从root节点开始：
    一直沿着左节点往下找，直到子节点等于NULL为止，这样就可以找到最小值了；
    一直沿着右节点往下找，直到子节点等于NULL为止，这样就可以找到最大值了。
 */
//递归的方式
template<class T, class N>
N* BST<T, N>::findMin(N* t) const {
	if(NULL == t) {
		return NULL;
	} else if(NULL==t->left){
		return t;
	} else{
		return findMin(t->left);
	}
}

template<class T, class N>
N* BST<T, N>::findMax(N* t) const {
	if(NULL == t) {
		return NULL;
	} else if (NULL == t->right){
		return t;
	} else {
		return findMax(t->right);
	}
}

/*
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
 */
template<class T, class N>
void BST<T, N>::rotate_left(N* n) {
	N* y = n->right;
    N* t2 = y->left;

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

template<class T, class N>
void BST<T, N>::rotate_right(N* n) {
    N* x = n->left;
    N* t2 = x->right;

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

