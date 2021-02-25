//栈的链表实现
#include<list>
#include<cassert>
using namespace std;

template<class T>
class mystack {
public:
    mystack(){}
    void push(const T& e) {
        m_list.push_back(e);
    }

    void pop() {
        m_list.pop_back();
    }

    T& top() {
        return m_list.back();
    }

    bool empty() {
        return m_list.empty();
    }

    void clear() {
        m_list.clear();
    }

private:
    list<T> m_list;    
};

int main() {
    mystack<int> s;
    s.push(1);
    s.push(2);
    assert(2 == s.top());
    s.pop();
    assert(1 == s.top());
    
    return 0;
}