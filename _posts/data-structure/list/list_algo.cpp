#include<cassert>
#include<iostream>
#include<stack>
#include<map>
using namespace std;

template<class T>
struct Node {
    T data;
    Node* next;
};

template<class T>
void print_list(Node<T>* head) {
    cout << "List: ";
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// 如何从尾到头输出单链表？
template<class T>
void print_reverse_list(Node<T>* head) {
    if (head->next != nullptr) {
        print_reverse_list(head->next);
    }
    cout << head->data << " ";
}

template<class T>
Node<T>* construct_list(int n) {
	Node<T>* head = new Node<T>;
	head->data = 0;
	head->next = nullptr;
	Node<T>* tmp = head;
	for (int i = 1; i < n; i++) {
		Node<T>* node = new Node<T>;
		node->data = i;
		node->next = nullptr;
		tmp->next = node;
		tmp = node;
	}

	return head;
}

// 构造带环的链表
template<class T>
Node<T>* construct_loop_list(T* a, const int n) {
    Node<T>* head = new Node<T>;
    head->data = a[0];
    head->next = nullptr;
    Node<T>* tmp = head;
	Node<T>* loop = nullptr;
    for (int i = 1; i < n; i++) {
        Node<T>* node = new Node<T>;
        if(n/2 == i) {
			loop=node;
		}
		node->data = a[i];
        node->next = nullptr;
        tmp->next = node;
        tmp = node;
    }
	tmp->next = loop;//尾节点指向链表中的某个节点，如果指向的是链表头，就变成循环链表了。
    return head;
}

// 如何检测一个较大的单链表是否有环？
template<class T>
bool is_loop_list(Node<T>* head) {
    assert(head != nullptr);
    std::map<Node<T>*, int> m_map;
    Node<T>* p = head;
    while (p != nullptr) {
        if (m_map[p] == 0) 
            m_map[p] = 1;
        else if (m_map[p] == 1) // 如果这个地址以前访问过，则是带环链表
            return true;
        p = p->next;
    }
	// 如果到链表尾也没有重复访问的链表地址，则不是带环链表
    return false;
}

// 如何实现单链表反转？
template<class T>
Node<T>* converse_list(Node<T>* head) {
    std::stack<Node<T>*> m_stack;
    while (head != nullptr) {
        m_stack.push(head);
        head = head->next;
    }

    Node<T>* node = m_stack.top();
    Node<T>* rhead = node;
    m_stack.pop();
    while (!m_stack.empty()) {
        node->next = m_stack.top();
        m_stack.pop();
        node = node->next;
    }
    node->next = nullptr;

    return rhead;
}

// 如何合并两个有序链表（非交叉）?
template<class T>
Node<T>* merge_list(Node<T>* ha, Node<T>* hb) {
    assert(ha != nullptr && hb!= nullptr);
    Node<T>* head = nullptr;
    Node<T>* tmp = nullptr;
    if (ha->data < hb->data) {
        head = ha;
        ha = ha->next;
    } else {
        head = hb;
        hb = hb->next;
    }

    tmp = head;
    while (ha != nullptr && hb != nullptr) {
        if (ha->data < hb->data) {
            tmp->next = ha;
            ha = ha->next;
        } else {
            tmp->next = hb;
            hb = hb->next;
        }
        tmp = tmp->next;
    }

    if (ha == nullptr) {
        tmp->next = hb;
    } else {
        tmp->next = ha;
    }

    return head;
}


int main() {
    Node<int>* head = construct_list<int>(10);
    print_reverse_list<int>(head);
    // print_list<int>(head);
    // Node<int>* rehead = converse_list<int>(head);
    // print_list<int>(rehead);
    int a[] = {1,3,5,4,8,6};
    Node<int>* lhead = construct_loop_list<int>(a, 6);
    cout << is_loop_list<int>(lhead) << endl;

    return 0;
}