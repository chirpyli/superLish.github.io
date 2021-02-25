// 通用二叉查找树的实现代码

#pragma once
#include<iostream>
#include<list>
#include<cassert>
#include<stack>
#include<queue>
using namespace std;

//栈实现
template<class T>
class Stack : public stack<T> {
public:
	T pop() {
		T tmp = stack<T>::top();
		stack<T>::pop();
		return tmp;
	}
};

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
	Node(const T& e, Node<T>* l = NULL, Node<T>* r = NULL):data(e),left(l),right(r){}
	~Node(){}
	T data;     
	Node* left;
	Node* right;
};


//二叉查找树的实现类
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
	void insert(const T&);		//插入
	bool remove(const T &x);	// 删除二叉查找树中指定的值
	void recursiveInsert(const T& el) {
		recursiveInsert(root, el);
        ++count;
	}
	Node<T>* search(const T& el) const {	//查找
		return search(root, el);
	}
	Node<T>* recursiveSearch(const T& el) const {
		return recursiveSearch(root, el);
	}
	void preorder() {//深度遍历之前序树遍历
		preorder(root);
	}
	void inorder() {//深度遍历之中序树遍历
		inorder(root);
	}
	void postorder() {//深度遍历之后序树遍历
		postorder(root);
	}
	void iterativePreorder();	// 深度遍历之前序树遍历
	void iterativeInorder();	// 深度遍历之中序树遍历
	void iterativePostorder();	// 深度遍历之后序树遍历
	void breadthFirst();		// 广度优先遍历
    void morrisInorder();       // Morris算法中序遍历
	void morrisPreorder();

	const T& findMin();	// 查找最小值，并返回最小值
    const T& findMax();	// 查找最大值，并返回最大值
protected:
	Node<T>* root; //根节点
    int count;
	void clear(Node<T>*);
	void recursiveInsert(Node<T>*&, const T&);	
	Node<T>* search(Node<T>*, const T&) const;
	Node<T>* recursiveSearch(Node<T>*, const T&) const;
	void preorder(Node<T>*);
	void inorder(Node<T>*);
	void postorder(Node<T>*);
	virtual void visit(Node<T>* p) {
		cout << p->data << ' ';
	}
	Node<T>* findMin(Node<T>* t) const;		//迭代方式实现
	Node<T>* findMax(Node<T>* t) const;		//迭代方式实现
	Node<T>* findMin_loop(Node<T>* t) const;		//循环方式实现
	Node<T>* findMax_loop(Node<T>* t) const;		//循环方式实现
	bool remove(const T&x, Node<T>*& t) const;

	void balance(T* data, int first, int last);		// 初始构建平衡树
};

// 前序遍历Morris算法实现
template<class T>
void BST<T>::morrisPreorder() {
	Node<T>* p = root;
	Node<T>* tmp;
	while (p != NULL) {
		if (p->left == NULL) {
			visit(p);
			p = p->right;
		} else {
			tmp = p->left;
			while (tmp->right != NULL && tmp->right != p)
				tmp = tmp->right;
			if (tmp->right == NULL) {
				visit(p);
				tmp->right = p;
				p = p->left;
			} else {
				tmp->right = NULL;
				p = p->right;
			}
		}
	}
}

// 中序遍历Morris算法实现
template<class T>
void BST<T>::morrisInorder() {
	Node<T>* p = root;
	Node<T>* tmp;
	while (p != NULL) {
		if (p->left == 0) {		// 如果当前节点的左孩子为空，打印当前节点，然后进入右孩子
			visit(p);
			p = p->right;
		} else {
			tmp = p->left;		// 根据当前节点，找到其前序节点(左子树最右节点)，然后进入当前节点的左孩子。
			while (tmp->right != 0 && tmp->right != p)
				tmp = tmp->right;
			if (tmp->right == NULL) {	// 如果前序节点的右孩子是空，那么把前序节点的右孩子指向当前节点
				tmp->right = p;
				p = p->left;
			} else {		// 如果当前节点的前序节点其右孩子指向了它本身，那么把前序节点的右孩子设置为空，打印当前节点，然后进入右孩子。
				visit(p);
				tmp->right = 0;
				p = p->right;
			}
		}
	}
} 

//根据数组中的内容构造树
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


//清除节点p及其子节点
template<class T>
void BST<T>::clear(Node<T> *p) {
	if (p != NULL) {
		clear(p->left);
		clear(p->right);
		delete p;
	}
    count = 0;
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
		prev->left = new Node<T>(el);
	else prev->right = new Node<T>(el);

    ++count;
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

//查找
template<class T>
Node<T>* BST<T>::search(Node<T>* p, const T& el) const {
	while (p != NULL) { 
		if (el == p->data)
			return &p->el;
		else if (el < p->data)
			p = p->left;
		else p = p->right;
	}
	return NULL;
}

//查找，递归实现
template<class T>
Node<T>* BST<T>::recursiveSearch(Node<T>* p, const T& el) const {
	if (p != NULL)
		if (el == p->data)
			return p;
		else if (el < p->data)
			return recursiveSearch(p->left, el);
		else return recursiveSearch(p->right, el);
	else return NULL;
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

//中序遍历，递归实现
template<class T>
void BST<T>::inorder(Node<T> *p) {
	if (p != NULL) {
		inorder(p->left);
		visit(p);
		inorder(p->right);
	}
}

//前序遍历，递归实现
template<class T>
void BST<T>::preorder(Node<T> *p) {
	if (p != NULL) {
		visit(p);
		preorder(p->left);
		preorder(p->right);
	}
}

//后续遍历，递归实现
template<class T>
void BST<T>::postorder(Node<T>* p) {
	if (p != NULL) {
		postorder(p->left);
		postorder(p->right);
		visit(p);
	}
}

//前序遍历，非递归实现
template<class T>
void BST<T>::iterativePreorder() {
    Stack<Node<T>*> m_stack;
    Node<T>* p = root;
    if (p != NULL) {
        m_stack.push(p);//从跟节点开始压
        while (!m_stack.empty()) {
            p = m_stack.pop();
            visit(p);
            if (p->right != NULL)//先压右子节点再压左子节点，因为要左侧先出
                m_stack.push(p->right);
            if (p->left != NULL) // left child pushed after right
                m_stack.push(p->left);
        }
    }
}

//后序遍历，非递归实现
template<class T>
void BST<T>::iterativePostorder() {
	Stack<Node<T>*> m_stack;
	Node<T>* p = root, *q = root;
	while (p != NULL) {
		for (; p->left != NULL; p = p->left)
			m_stack.push(p);
		while (NULL == p->right || q == p->right) {
			visit(p);
			q = p;
			if (m_stack.empty())
				return;
			p = m_stack.pop();
		}
		m_stack.push(p);
		p = p->right;
	}
}

//中序遍历，非递归实现
template<class T>
void BST<T>::iterativeInorder() {
	Stack<Node<T>*> m_stack;
	Node<T>* p = root;
	while (p != NULL) {
		while (p != NULL) {                 // stack the right child (if any)
			if (p->right)                // and the node itself when going
				m_stack.push(p->right); // to the left;
			m_stack.push(p);
			p = p->left;
		}
		p = m_stack.pop();             // pop a node with no left child
		while (!m_stack.empty() && p->right == NULL) { // visit it and all nodes
			visit(p);                                 // with no right child;
			p = m_stack.pop();
		}
		visit(p);                        // visit also the first node with
		if (!m_stack.empty())          // a right child (if any);
			p = m_stack.pop();
		else p = NULL;
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
	if(NULL==t){
		return NULL;
	} else if(NULL==t->left){
		return t;
	} else{
		return findMin(t->left);
	}
}

//递归的方式
template<class T>
Node<T>* BST<T>::findMax(Node<T>* t) const {
	if(NULL == t){
		return NULL;
	} else if(NULL == t->right){
		return t;
	} else {
		return findMax(t->right);
	}
}

//循环方式
template<class T>
Node<T>* BST<T>::findMin_loop(Node<T>* t) const {
	if(NULL==t) {
		return NULL;
	}
	while(t->left) {
		t=t->left;
	}
	return t;
}

//循环方式
template<class T>
Node<T>* BST<T>::findMax_loop(Node<T>* t) const {
	if(NULL==t) {
		return NULL;
	}
	while(t->right) {
		t=t->right;
	}
	return t;
}

//查找最小值，并返回最小值
template<class T>
const T& BST<T>::findMin(){
	Node<T>* p=findMin(root);
	return p->data;
}

//查找最大值，并返回最大值
template<class T>
const T& BST<T>::findMax() {
	Node<T>* p=findMax(root);
	return p->data;
}