// 自适应树

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

//树节点类
template<class T>
class Node {
public:
	Node():left(NULL),right(NULL){}
	Node(const T& e, Node<T>* l = NULL, Node<T>* r = NULL, Node<T>* p = NULL):data(e),left(l),right(r),parent(p){}
	~Node(){}
	T data;     
	Node* left;
	Node* right;
	Node* parent;
	Node* grandparent() {
        if (NULL == parent)
            return NULL;
        return parent->parent;
    }
};


template<class T>
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
	virtual void insert(const T &e);		// 插入
	virtual bool remove(const T &e);	// 删除二叉查找树中指定的值
    virtual bool search(const T &e);
	void breadthFirst();		// 广度优先遍历

protected:
	Node<T>* root; //根节点
    int count;
	void clear(Node<T>*);
    void balance(T* data, int first, int last);		// 初始构建平衡树
    bool remove(const T&x, Node<T>*& t) const;
	void recursiveInsert(Node<T>*&, const T&);	
    Node<T>* findMin(Node<T>* t) const;		//迭代方式实现
	Node<T>* findMax(Node<T>* t) const;
	virtual void visit(Node<T>* p) {
		cout << p->data << ' ';
	}
	void rotate_left(Node<T>* n);
    void rotate_right(Node<T>* n);
};

// 根据数组中的内容构造树
template<class T>
BST<T>::BST(T* a, int len, bool balance) {
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

template<class T>
void BST<T>::balance(T* data, int first, int last) {
	if (first <= last) {
		int middle = (first + last) >> 1;
		this->insert(data[middle]);
		balance(data, first, middle - 1);
		balance(data, middle + 1, last);
	}
}

// 清除节点p及其子节点
template<class T>
void BST<T>::clear(Node<T> *p) {
	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
    count = 0;
}

//插入，递归实现
template<class T>
void BST<T>::recursiveInsert(Node<T>*& p, const T& el) {
	if (p == NULL)
		p = new Node<T>(el);
	else if (el < p->data)
		recursiveInsert(p->left, el);
	else recursiveInsert(p->right, el);
}

//插入，非递归形式
template<class T>
void BST<T>::insert(const T& el) {
	Node<T> *p = root, *prev = NULL;
	while (p != NULL) {  // find a place for inserting new node;
		prev = p;
		if (el < p->data)
			p = p->left;
		else p = p->right;
	}
	if (root == NULL)    // tree is empty;
		root = new Node<T>(el);
	else if (el < prev->data)
		prev->left = new Node<T>(el, NULL, NULL, prev);
	else prev->right = new Node<T>(el, NULL, NULL, prev);

    ++count;
}


// 这里采用的方法一，选择右子树中最小值节点
template<class T>
bool BST<T>::remove(const T& x, Node<T>* &t) const {
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
		Node<T>* p = t;
		t = (t->left != NULL)?t->left:t->right;//用其子节点占据删除掉的位置；
		delete p;//直接删除对应的节点
	}

    return true;
}

//删除指定元素
template<class T>
bool BST<T>::remove(const T& x) {
	bool r = remove(x, root);
    if (r == true) {
        --count;
    }

    return r;
}

//查找
template<class T>
bool BST<T>::search(const T &e) {
    Node<T>* p = root;
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
template<class T>
void BST<T>::breadthFirst() {
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

//这段代码是实现查找最大值和最小值的代码
/*思路：我们可以从root节点开始：
    一直沿着左节点往下找，直到子节点等于NULL为止，这样就可以找到最小值了；
    一直沿着右节点往下找，直到子节点等于NULL为止，这样就可以找到最大值了。
 */
//递归的方式
template<class T>
Node<T>* BST<T>::findMin(Node<T>* t) const {
	if(NULL == t) {
		return NULL;
	} else if(NULL==t->left){
		return t;
	} else{
		return findMin(t->left);
	}
}

template<class T>
Node<T>* BST<T>::findMax(Node<T>* t) const {
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
template<class T>
void BST<T>::rotate_left(Node<T>* n) {
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

template<class T>
void BST<T>::rotate_right(Node<T>* n) {
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

// 自适应树——单一旋转实现
template<class T>
class STree : public BST<T> {
public:
    STree(){}
	STree(T* a, int len, bool balance = false) {	//根据数组中的数据构造树，调试测试用
        BST<T>(a, len, balance);
    }
    ~STree(){}
    virtual bool search(const T& e);
};

template<class T>
bool STree<T>::search(const T& e) {
    Node<T>* n = this->root;
	Node<T>* par = NULL;
    while (n != NULL) { 
		if (e == n->data) {
			cout << "search " << e << ", rotate upper." << endl;
            if (n != this->root) {
                if (n == par->left) 
                    this->rotate_right(par);
                else if (n == par->right)
                    this->rotate_left(par);
            }
            return true;
        } else if (e < n->data) {
			par = n;
            n = n->left;
        } else {
            par = n;
            n = n->right;
        } 
	}
    
	return false;
}

// 伸展树
template<class T>
class SplayTree: public BST<T> {
public:
	virtual bool search(const T& e);
	virtual void insert(const T& e);
	virtual bool remove(const T& e);
protected:
	void splaying(Node<T>* n);
};


// 查询后伸展
template<class T>
bool SplayTree<T>::search(const T& e) {
	Node<T>* n = this->root;
	while (n != NULL) {
		if (e == n->data) {
			cout << "splay node " << e << endl;
			splaying(n);
			return true;
		} else if (e < n->data) {
			n = n->left;
		} else {
			n = n->right;
		}
	}

	return false;
}

// 插入后伸展
template<class T>
void SplayTree<T>::insert(const T& e) {
	Node<T> *p = this->root, *prev = NULL;
	while (p != NULL) {  // find a place for inserting new node;
		prev = p;
		if (e < p->data)
			p = p->left;
		else p = p->right;
	}
	if (this->root == NULL)    // tree is empty;
		this->root = new Node<T>(e);
	else if (e < prev->data) {
		prev->left = new Node<T>(e, NULL, NULL, prev);
		splaying(prev->left);
	} else {
		prev->right = new Node<T>(e, NULL, NULL, prev);
		splaying(prev->right);
	}

    this->count++;	
}

// 删除要稍微麻烦一点， 这里采用方法二，先旋转被删除的节点到根节点，删除根节点，变成左右2个子树，再将左右两个子树进行拼接。
// 拼接方法，这里因为是删除根节点后的左右两个子树，有左子树的所有节点都小于右子树，找到左子树的最大节点，伸展至左子树根节点，将右子树拼接至左子树最大值节点的右子树。
template<class T>
bool SplayTree<T>::remove(const T& e) {
	if (!search(e))
		return false;
	
	Node<T>* lt = this->root->left;
	Node<T>* rt = this->root->right;
	delete this->root;

	if (lt != NULL) {
		Node<T>* lsubmax = this->findMax(lt);
		splaying(lsubmax);
		this->root = lsubmax;
		lsubmax->parent = NULL;
		
		Node<T>* smax = this->findMax(lsubmax);
		smax->right = rt;
		rt->parent = smax;
	} else {
		this->root = rt;
		rt->parent = NULL;
	}

	return true;
}

/*
case1:
		Q							R
	   /  \    right_rotete(Q)     /  \
	  R    C  --------------> 	  A    Q
	 / \                 			  / \
	A   B               		     B   C

case2:
		P						       Q                                R
	   /  \    right_rotete(P)        /  \       right_rotate(Q)       / \
	  Q    D  ---------------->      R	  P   ------------------>     A   Q
	 / \                			/ \   / \                            /  \
	R   C              			   A   B C   D                          B    P
   / \																		/ \
  A   B																	   C   D

case3:
		P							     P                              R
	   / \								/ \                           /   \
	  Q   D    left_rotete(Q)          R   D    right_rotate(P)      Q     P
	 / \     --------------------->   /  \    ------------------>   / \   /  \
	A   R                            Q    C                        A   B  C   D
	   / \							/ \				
	  B   C                        A   B
*/
template<class T>
void SplayTree<T>::splaying(Node<T>* n) {
	while (n->parent) {
		if (n->parent == this->root) {
			if (n->parent->left == n) 
				this->rotate_right(n->parent);
			else 
				this->rotate_left(n->parent);
		} else if (n->parent->parent) {
			if (n->parent->left == n && n->parent->parent->left == n->parent) {
				this->rotate_right(n->parent->parent);
				this->rotate_right(n->parent);
			} else if (n->parent->right == n && n->parent->parent->right == n->parent) {
				this->rotate_left(n->parent->parent);
				this->rotate_left(n->parent);
			} else if (n->parent->left == n && n->parent->parent->right == n->parent) {
				this->rotate_right(n->parent);
				this->rotate_left(n->parent);
			} else if (n->parent->right == n && n->parent->parent->left == n->parent) {
				this->rotate_left(n->parent);
				this->rotate_right(n->parent);
			}
		}
	}
}