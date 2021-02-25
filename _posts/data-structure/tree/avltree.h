#include<iostream>
#include<cassert>
#include<algorithm>

template<class T>
class ANode {
public:
    ANode(){};
    ANode(T k):key(k),left(NULL),right(NULL),height(1){}
    ANode(T k, ANode* left, ANode* right, int height = 1):key(k),left(left),right(right),height(height){}
    T key;
    ANode* left;
    ANode* right;
    int height;
};


template<class T>
class AVLTree {
public:
    AVLTree():root(NULL){}
    AVLTree(T* k, int len);
    void insert(T k);
    void remove(const T &k);
    void preOrder(ANode<T>* n);
    int height(const ANode<T>* n) const;
    ANode<T>* getRoot() const;
private:
    int balance_factor(const ANode<T>* n) const;    
    ANode<T>* rightRotate(ANode<T>* y);
    ANode<T>* leftRotate(ANode<T>* x);
    ANode<T>* recursive_insert(ANode<T>* n, T k);
    ANode<T>* recursive_remove(ANode<T>* n, T k);
    ANode<T>* minNode(ANode<T>*);
    void visit(ANode<T>* n);

    ANode<T>* root;
};

template<class T>
AVLTree<T>::AVLTree(T* k, int len) {
    root = NULL;
    for (int i = 0; i < len; ++i) {
        insert(k[i]);
    }
}

template<class T>
void AVLTree<T>::visit(ANode<T>* n) {
    std::cout << n->key << " ";
}

template<class T>
ANode<T>* AVLTree<T>::minNode(ANode<T>* n) {
    ANode<T>* m = n;
    while(m->left != NULL) {
        m = m->left;
    }

    return m;
}

template<class T>   
ANode<T>* AVLTree<T>::getRoot() const{
    return this->root;
}

template<class T>
void AVLTree<T>::preOrder(ANode<T>* n) {
    if (n != NULL) {
        visit(n);
        preOrder(n->left);
        preOrder(n->right);
    }
}

template<class T>
int AVLTree<T>::height(const ANode<T>* n) const {
    if (NULL == n) {
        return 0;
    }

    return n->height;
}

template<class T>
int AVLTree<T>::balance_factor(const ANode<T>* n) const {
    if (NULL == n)
        return 0;

    int r = 0, l = 0;
    if (n->right != NULL) {
        r = n->right->height;
    }
    if (n->left != NULL) {
        l = n->left->height;
    }

    int bf = r - l;

    return bf;
}

/*
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y 
  / \       < - - - - - - -            / \
 T1  T2     Left Rotation            T2  T3
 */
template<class T>
ANode<T>* AVLTree<T>::rightRotate(ANode<T>* y) {
    // Perform rotation
    ANode<T>* x = y->left;
    ANode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;   // Return new root replace old root y
}

template<class T>
ANode<T>* AVLTree<T>::leftRotate(ANode<T>* x) {
    ANode<T>* y = x->right;
    ANode<T>* T2 = y->left;

    y->left = x;
    x->right = T2;
    
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}


/*
**a) Left Left Case**
```
T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
```

**b) Left Right Case**
```
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
```

**c) Right Right Case**
```
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
```

**d) Right Left Case**
```
   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
```
 */
template<class T>
ANode<T>* AVLTree<T>::recursive_insert(ANode<T>* n, T k) {
    // normal BST insertion.
    if (NULL == n) {
        n = new ANode<T>(k);
        return n;
    }

    if (k < n->key) {
        n->left = recursive_insert(n->left, k);
    } else if (k > n->key) {
        n->right = recursive_insert(n->right, k);
    } else {
        return n;   // equal k, update value, return node.
    }

    // update height
    n->height = std::max(height(n->left), height(n->right)) + 1;

    // get the balance factor of this node to check whether this node became unbalanced.
    int bf = this->balance_factor(n);

    // If this node becomes unbalanced, then there are 4 cases 

    // left-left
    if (bf < -1 && k < n->left->key)
        return rightRotate(n);
    // right-right
    if (bf > 1 && k > n->right->key)
        return leftRotate(n);
    // left-right
    if (bf < -1 && k > n->left->key) {
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    // right-left
    if (bf > 1 && k < n->right->key) {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
        
    return n;
}


// 时间复杂度O(h)=O(log(n))
template<class T>
void AVLTree<T>::insert(T k) {
    root = recursive_insert(root, k);
}


template<class T>
ANode<T>* AVLTree<T>::recursive_remove(ANode<T>* n, T k) {
    if (NULL == n) {
        return n;
    }

    // normal delete node k
    if (k < n->key) {
        n->left = recursive_remove(n->left, k);
    } else if (k > n->key) {
        n->right = recursive_remove(n->right, k);
    } else {
        if (n->left == NULL || n->right == NULL) {
            ANode<T>* tmp = n->left ? n->left : n->right;
            if (NULL == tmp) {
                tmp = n;
                n = NULL;
            } else {
                *n = *tmp;
            }
            free(tmp);
        } else {
            ANode<T>* tmp = minNode(n->right);
            n->key = tmp->key;
            n->right = recursive_remove(n->right, tmp->key);
        }
    }

    if (NULL == n) {
        return n;
    }

    // update height , calculate balance factor
    n->height = std::max(height(n->left), height(n->right)) + 1;
    int bf = this->balance_factor(n);

    // if this node become unbalanced , then there are 4 cases:

    // left-left
    if (bf < -1 && balance_factor(n->left) <= 0) {
        return rightRotate(n);
    }

    // right-right
    if (bf > 1 && balance_factor(n->right) >=0 ) {
        return leftRotate(n);
    }

    // left-right
    if (bf < -1 && balance_factor(n->left) > 0) {
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }

    // right-left
    if (bf > 1 && balance_factor(n->right) < 0) {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }

    return n;
}

template<class T>
void AVLTree<T>::remove(const T& k) {
    root = recursive_remove(root, k);
}
