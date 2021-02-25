#include<iostream>
#include<cstdlib>
#include<ctime>
#include<random>
#include<cmath>
#include<climits>
#include<vector>
#include<cassert>
#include<algorithm>

using namespace std;

const int MAX_LEVEL = 8;   // 用户定义的最大层数
const float P = 0.5;        // 用户设置的概率P

//跳跃列表节点类
template<class K, class V>
class SkipListNode {
public:
    SkipListNode() {}
    SkipListNode(K key, V value, int level);
    K key;
    V value;
    typedef SkipListNode<K, V>* NodePtr;
    NodePtr forward[MAX_LEVEL];
};

template<class K, class V>
SkipListNode<K, V>::SkipListNode(K key, V value, int level):key(key),value(value) {
    for (int i = 0; i < level; ++i) {
        this->forward[i] = nullptr;
    }
}

// 跳跃列表类
template<class K, class V>
class SkipList {
public:
typedef SkipListNode<K, V>* NodePtr;

    SkipList();
    SkipList(NodePtr header, NodePtr tail);
    ~SkipList();
    V* search(const K& key);
    void insert(const K& key,const V& value);
    void remove(const K& key);
    void print();
private:
    int randomLevel() const;
    NodePtr header;           // header节点
    NodePtr tail;             // tail节点
    int level;                // 当前层数
    int n;                    // 节点数量
};

template<class K, class V>
void SkipList<K, V>::print() {
    assert(this->header != nullptr);
    std::cout << "level=" << this->level << " count=" << this->n << endl;
    for (int i = this->level - 1; i >= 0 ; --i) {
        cout << "level" << i + 1 << ":";
        NodePtr pNode = this->header->forward[i];
        while (pNode != this->tail) {
            cout << "<" << pNode->key << ", " << pNode->value << ">  ";
            pNode = pNode->forward[i]; 
        }
        cout << endl;
    }
}

template<class K, class V>
SkipList<K, V>::SkipList() {
    this->header = nullptr;
    this->tail = nullptr;
    this->level = 0;
    this->n = 0;
}

template<class K, class V>
SkipList<K, V>::SkipList(NodePtr header, NodePtr tail) {
    this->header = header;
    this->tail = tail;
    this->level = 1;
    this->n = 0;
    for (int i = 0; i < MAX_LEVEL; ++i) {
        this->header->forward[i] = tail;
    }
}

template<class K, class V>
SkipList<K, V>::~SkipList() {
    NodePtr p = this->header;
    while (p->forward[0] != nullptr) {
        NodePtr tmp = p;
        p = p->forward[0];
        delete tmp;
    }
}

template<class K, class V>
int SkipList<K, V>::randomLevel() const {
    int lvl = 1;
    int maxLevel = (int)log(this->n) + 1;
    while (rand() % 100 < P * 100 && lvl < min(maxLevel, MAX_LEVEL)) {
        ++lvl;
    }

    return lvl;
}

template<class K, class V>
V* SkipList<K, V>::search(const K& key) {
    NodePtr x = this->header;
    for (int i = 0; i < this->level; ++i) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
    }

    x = x->forward[0];      
    if (x->key == key) {
        return &x->value;
    } else {
        return nullptr;
    }
}

template<class K, class V>
void SkipList<K, V>::insert(const K& key,const V& value) {
    // 找到待调整的项
    NodePtr update[MAX_LEVEL];
    NodePtr ptr = this->header;
    for (int i = this->level - 1; i >= 0; --i) {
        while (ptr->forward[i]->key < key) {
            ptr = ptr->forward[i];
        }
        update[i] = ptr;
    }

    if (update[0]->forward[0]->key == key) {
        update[0]->forward[0]->value = value;
        return;
    }
    // 进行节点加入操作（与链表插入类似）
    const int lvl = this->randomLevel();        // 随机生成该节点层数
    if (lvl > this->level) {
        for (int i = this->level; i< lvl; ++i) {
            update[i] = this->header;
        }
        this->level = lvl;
    }

    NodePtr x = new SkipListNode<K, V>(key, value, lvl);
    for (int i = 0; i < this->level; ++i) {
        x->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = x;
    }

    this->n++;
}

template<class K, class V>
void SkipList<K, V>::remove(const K& key) {
    NodePtr update[MAX_LEVEL];
    NodePtr x = this->header;
    for (int i = this->level -1; i >= 0; --i) {
        while (x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }

    x = x->forward[0];
    if (x->key == key) {
        for (int i = 0; i < this->level; ++i) {
            if (update[i]->forward[i] != x) 
                break;
            update[i]->forward[i] = x->forward[i];
        }
        delete x;
        this->n--;
        while (this->level > 1 && this->header->forward[this->level - 1] == this->tail) {
            this->level--;
        }
    }
} 

int main() {
    srand(time(nullptr));
    SkipListNode<int, int> *header = new SkipListNode<int, int>(INT_MIN, 0, 1);
    SkipListNode<int, int> *tail = new SkipListNode<int, int>(INT_MAX, 0, 1);
    SkipList<int, int>* pSkiplist = new SkipList<int, int>(header, tail);
    pSkiplist->insert(10, 10);
    pSkiplist->insert(15, 15);
    pSkiplist->insert(12, 12);
    pSkiplist->insert(18, 18);
    pSkiplist->insert(1, 1);
    pSkiplist->insert(121, 121);
    pSkiplist->insert(118, 118);
    pSkiplist->insert(10, 100);
    pSkiplist->print();
    int* v = pSkiplist->search(121);
    cout << "value is :" << *v << endl;
    pSkiplist->remove(118);
    pSkiplist->print();
    pSkiplist->insert(11860, 1180);
    pSkiplist->insert(11850, 1180);
    pSkiplist->insert(11840, 1180);
    pSkiplist->insert(11830, 1180);
    pSkiplist->insert(11820, 1180);

    pSkiplist->print();

    delete pSkiplist;

}
