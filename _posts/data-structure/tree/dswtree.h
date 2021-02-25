#include"bstree.h"
#include<cmath>

template<class T>
class DswBST: public BST<T> {
public:
	DswBST(T* a, int len);    //根据数组中的数据构造树，调试测试用
    void dswBalance();
protected:
    void createBackbone();
    void creatPerfectTree();
    void rotateRight(Node<T>* Gr, Node<T>* Par, Node<T>* Ch);
    void rotateLeft(Node<T>* Gr, Node<T>* Par, Node<T>* Ch);
};

template<class T>
DswBST<T>::DswBST(T* a, int len) {
    assert(a != NULL);
	for (int i = 0; i < len; i++) {
		this->insert(a[i]);
	}
}

template<class T>
void DswBST<T>::dswBalance() {
	createBackbone();
    creatPerfectTree();
}

// 二叉查找树转化成主链的过程分析
/**********************************************************************************************
*  5 <-tmp         5               5               5              5
*   \               \               \               \               \
*    10             10              10              10              10
*      \              \               \               \               \
*       20            15              15              15              15
*      /  \             \               \               \               \
*     15  30            20              20              20              20
*         / \             \              \                \               \
*        25 40            30 <-tmp       25 <-tmp         23               23        
*       /  \             /  \           /  \               \                \
*     23    28          25   40        23   30              25              25    
*                      /  \                /  \              \                \
*                     23   28             28   40            30 <-tmp         28
*                                                           /  \               \
*                                                          28  40               30
*                                                                                \
*                                                                                 40 <-tmp
***********************************************************************************************/
template<class T>
void DswBST<T>::createBackbone() {
	Node<T> *Gr = 0, *Par = this->root, *Ch = 0;
	while(Par != 0) {
		Ch = Par->left;
		if(Ch != 0) {
			rotateRight(Gr, Par, Ch);
			Par = Ch;
		} else {
			Gr = Par;
			Par = Par->right;
		}
		// 旋转过程中，如果是绕根节点的右节点旋转时要将根节点置为原根节点的右节点
		if(Gr == 0)
            this->root = Ch;
	}
}

/************************************************************************
 *  子节点Ch围绕父节点Par的右旋转
 *   Before      After
 *    Gr          Gr
 *     \           \
 *     Par         Ch
 *    /  \        /  \
 *   Ch   Z      X   Par
 *  /  \            /  \
 * X    Y          Y    Z
 ***********************************************************************/
template<class T>
void DswBST<T>::rotateRight(Node<T>* Gr, Node<T>* Par, Node<T>* Ch) {
	if(Gr != 0)
        Gr->right = Ch;
	Par->left = Ch->right;
	Ch->right = Par;
}

template<class T>
void DswBST<T>::rotateLeft(Node<T>* Gr, Node<T>* Par, Node<T>* Ch) {
	if(Gr != 0)
        Gr->right = Ch;
	Par->right = Ch->left;
	Ch->left = Par;
}

template<class T>
void DswBST<T>::creatPerfectTree() {
    int n = this->count;
    if (n < 3) {  
        return; //节点数目小于3不用平衡
    }
	int m = (1 << ((int)(log10(n+1)/log10(2)))) - 1;
	Node<T> *Gr = 0;
    Node<T> *Par = this->root;
    Node<T> *Ch = this->root->right;
    
    this->root = this->root->right; //修改root指针
    // 第一阶段： 左旋n-m次
	for(int i = 0; i < n - m; i++) {
		rotateLeft(Gr, Par, Ch);
        Gr = Ch;
        Par = Gr->right;
        if (0 != Par) {
            Ch = Par->right;
        } else {
            break;
        }
	}

    // 第二阶段，进入while循环
	while( m > 1) {
		m = m >> 1;
		Node<T> *Gr = 0;
        Node<T> *Par = this->root;
        Node<T> *Ch = this->root->right;

        this->root = this->root->right;	
        for(int i = 0; i < m; i++) {
            rotateLeft(Gr, Par, Ch);
            Gr = Ch;
            Par = Gr->right;
            if (0 != Par) {
                Ch = Par->right;
            } else {
                break;
            }
        }
	}
}
