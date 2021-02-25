#include<iostream>
#include<queue>
namespace mytree {

using namespace std;

enum ecolor {
    red,
    black,
};

struct Node {
    Node():key(-1),color(ecolor::red),left(nullptr),right(nullptr),parent(nullptr){}
    Node(int k, Node* nil):key(k),color(ecolor::red),left(nil),right(nil),parent(nullptr){}
    Node* grandparent() {
        if (nullptr == parent)
            return nullptr;
        return parent->parent;
    }

    Node* uncle() {
        if (nullptr == grandparent())
            return nullptr;
        if (grandparent()->left == parent) 
            return grandparent()->right;
        else 
            return grandparent()->left;
    }

    Node* sibling() {
        if (nullptr == parent)
            return nullptr;
        if (parent->left == this)
            return parent->right;
        else 
            return parent->left;
    }
    
    int key;
    ecolor color;
    Node* left;
    Node* right;
    Node* parent;
};

class RBTree {
public:
    RBTree():root(nullptr) {
        nil = new Node();
        nil->color = ecolor::black;
    }
    ~RBTree() {
        delete_tree(root);
        delete nil;
    }

    // 广度优先遍历，方便调试用
    void print_tree() {
        if (nullptr == root)
            cout << "red-black tree is null." << endl;

        queue<Node*> m_queue;
        m_queue.push(root);
        while(!m_queue.empty()) {
            Node* t = m_queue.front();
            visit(t);
            if (t->left != nil)
                m_queue.push(t->left);
            if (t->right != nil) 
                m_queue.push(t->right);
            m_queue.pop();
        }
        cout << endl;
    }

    void insert(int k) {
        if (nullptr == root) {
            root = new Node(k, nil);
            root->color = ecolor::black;
        } else 
            insert(root, k);
    }

    bool remove(int k) {
        return delete_child(root, k);
    }

private:
    Node* root;
    Node* nil;

    void visit(Node* n) {
        if (nullptr == n)
            return;
        cout << "<" << n->key << ",";
        if (n->color == ecolor::red)
            cout << "r>  ";
        else 
            cout << "b>  ";
    }

    void insert(Node* n, int k) {
        if (k < n->key) {
            if (n->left != nil)
                insert(n->left, k);
            else {
                Node* tmp = new Node(k, nil);
                tmp->parent = n;
                n->left = tmp;
                insert_case(tmp);
            }
        } else if (k > n->key) {
            if (n->right != nil)
                insert(n->right, k);
            else {
                Node* tmp = new Node(k, nil);
                tmp->parent = n;
                n->right = tmp;
                insert_case(tmp);
            }
        }
    }


    // void insert_case1(Node* n) {
    //     if (nullptr == n->parent)
    //         n->color = ecolor::black;
    //     else
    //         insert_case2(n);
    // }

    // void insert_case2(Node* n) {
    //     if (n->parent->color == ecolor::black)
    //         return;
    //     else
    //         insert_case3(n);
    // }

    // void insert_case3(Node* n) {
    //     if (n->uncle() != nullptr && n->uncle()->color == ecolor::red) {
    //         n->parent->color = ecolor::black;
    //         n->uncle()->color = ecolor::black;
    //         n->grandparent()->color = ecolor::red;
    //         insert_case1(n->grandparent());
    //     } else
    //         insert_case4(n);
    // }

    // void insert_case4(Node* n) {
    //     if (n == n->parent->right && n->parent == n->grandparent()->left) {
    //         rotate_left(n);     
    //         n = n->left;
    //     } else if (n == n->parent->left && n->parent == n->grandparent()->right) {
    //         rotate_right(n);    
    //         n = n->right;
    //     }
    //     insert_case5(n);
    // }

    // void insert_case5(Node* n) {
    //     n->parent->color = ecolor::black;
    //     n->grandparent()->color = ecolor::red;
    //     if (n == n->parent->left && n->parent == n->grandparent()->left)
    //         rotate_right(n->parent);    
    //     else
    //         rotate_left(n->parent);     
    // }
    // 将上面的几种情况合并如下：
    void insert_case(Node* n) {
        if (nullptr == n->parent) {
            n->color = ecolor::black;
            return;
        }
        if (n->parent->color == ecolor::red) {
            if (n->uncle()->color == ecolor::red) {
                n->parent->color = ecolor::black;
                n->uncle()->color = ecolor::black;
                n->grandparent()->color = ecolor::red;
                insert_case(n->grandparent());
            } else {
                if (n == n->parent->right && n->parent == n->grandparent()->left) {
                    rotate_left(n);     
                    rotate_right(n);     
                    n->color = ecolor::black;
                    n->left->color = n->right->color = ecolor::red;
                } else if (n == n->parent->left && n->parent == n->grandparent()->right) {
                    rotate_right(n);    
                    rotate_left(n);
                    n->color = ecolor::black;
                    n->left->color = n->right->color = ecolor::red;
                } else if (n == n->parent->left && n->parent == n->grandparent()->left) {
                    n->parent->color = ecolor::black;
                    n->grandparent()->color = ecolor::red;
                    rotate_right(n->parent);
                } else if (n == n->parent->right && n->parent == n->grandparent()->right) {
                    n->parent->color = ecolor::black;
                    n->grandparent()->color = ecolor::red;   
                    rotate_left(n->parent);
                }
            }
        }
    }



    void delete_tree(Node* n) {
        if (!n || n == nil)
            return;
        delete_tree(n->left);
        delete_tree(n->right);
        delete n;
    }

    void rotate_left(Node* n) {
        if (n->parent == nullptr) {
            root = n;
            return;
        }

        Node* gp = n->grandparent();
        Node* fa = n->parent;
        Node* y = n->left;

        fa->right = y;
        if (y != nil) {
            y->parent = fa;
        }

        n->left = fa;
        fa->parent = n;

        if (root == fa)
            root = n;
        n->parent = gp;

        if (gp != nullptr) {
            if (gp->left == fa)
                gp->left = n;
            else 
                gp->right = n;
        }
    }

    void rotate_right(Node* n) {
        Node* gp = n->grandparent();
        Node* fa = n->parent;
        Node* y = n->right;

        fa->left = y;
        if (y != nil)
            y->parent = fa;
        n->right = fa;
        fa->parent = n;

        if (fa == nullptr)
            root = n;
        n->parent = gp;
        if (gp != nullptr) {
            if (gp->left == fa)
                gp->left = n;
            else
                gp->right = n;
        }
    }

    Node* min_child(Node* n) {
        if (n->left == nil)
            return n;
        return min_child(n->left);
    }

    // 复制删除
    bool delete_child(Node* n, int k) {
        if (n->key > k) {
            if (n->left == nil)
                return false;
            delete_child(n->left, k);
        } else if (n->key < k) {
            if (n->right == nil)
                return false;
            delete_child(n->right, k);
        } else {
            if (n->right == nil) {
                delete_one_child(n);
                return true;
            }
            Node* min = min_child(n->right);
            std::swap(n->key, min->key);
            delete_one_child(min);

            return true;
        }
    }

    void delete_one_child(Node* n) {
        Node* child = n->left == nil ? n->right : n->left;
        if (n->parent == nullptr && n->left && n->right == nil) {
            root = nullptr;
            delete n;
            n = nullptr;
            return;
        }

        if (n->parent == nullptr) {
            delete n;
            child->parent = nullptr;
            root = child;
            root->color = ecolor::black;
            return;
        }

        if (n->parent->left == n)
            n->parent->left = child;
        if (n->parent->right == n)
            n->parent->right = child;
        child->parent = n->parent;

        if (n->color == ecolor::black) {
            if (child->color == ecolor::red)
                child->color = ecolor::black;
            else
                delete_case(child);
        }

        delete n;
    }

    // 被删除节点及其子节点都是黑色
    void delete_case(Node* n) {
        // case1: 父节点是null
        if (n->parent == nullptr) {
            n->color == ecolor::black;
            return;
        }

        // case2: 兄弟节点是红色（隐含其父节点是黑色）
        if (n->sibling()->color == ecolor::red) {
            n->parent->color = ecolor::red;
            n->sibling()->color = ecolor::black;
            if (n == n->parent->left) 
                rotate_left(n->parent);
            else 
                rotate_right(n->parent);
        }

        if (n->parent->color == ecolor::black && n->sibling()->color == ecolor::black && n->sibling()->left->color == ecolor::black && n->sibling()->right->color == ecolor::black) {
            // case3: N的父节点、S是黑色的，另外S的子节点都是黑色的。
            n->sibling()->color = ecolor::red;
            delete_case(n->parent);
        } else if (n->parent->color == ecolor::red && n->sibling()->color == ecolor::black && n->sibling()->left->color == ecolor::black && n->sibling()->right->color == ecolor::black) {
            // case4: N的父节点P是红色，N的兄弟节点S是黑色，兄弟节点S的子节点都是黑色
            n->parent->color = ecolor::black;
            n->sibling()->color = ecolor::red;   
        } else {
            if (n->sibling()->color == ecolor::black) {
                // case5: N的兄弟节点S是黑色， 兄弟节点S的子节点一个是红色一个是黑色
                if (n == n->parent->left && n->sibling()->left->color == ecolor::red && n->sibling()->right->color == ecolor::black) {
                    n->sibling()->color = ecolor::red;
                    n->sibling()->left->color = ecolor::black;
                    rotate_right(n->sibling()); // fixme
                } else if (n == n->parent->right && n->sibling()->left->color == ecolor::black && n->sibling()->right->color == ecolor::red) {
                    n->sibling()->color == ecolor::red;
                    n->sibling()->right->color = ecolor::black;
                    rotate_left(n->sibling());  // fixme
                }
            }

            // case6: S是黑色，S的右子节点是红色(两个子节点都是红色的情况也在这里)，而N是它父节点的左子节点。 还有一种是镜像对称
            n->sibling()->color = n->parent->color;
            n->parent->color = ecolor::black;
            if (n == n->parent->left) {
                n->sibling()->right->color = ecolor::black;
                rotate_left(n->parent);     // fixme
            } else {
                n->sibling()->left->color = ecolor::black;
                rotate_right(n->parent);    // fixme
            }
        }
    }
};
}