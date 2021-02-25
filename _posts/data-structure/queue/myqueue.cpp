// 最简单的队列实现
#include<cassert>
#include<list>
using namespace std;

template<class T>
class myqueue {
public:
    myqueue(){}
    void clear() {
        m_list.clear();
    }

    bool empty() {
        return m_list.empty();
    }

    void push(const T& e) {
        m_list.push_back(e);
    }

    void pop() {
        m_list.pop_front();
    }

    T& front() {
        return m_list.front();
    }

private:
    list<T> m_list;
};

int main() {
    myqueue<int> q;
    int numbers[] = {1, 2, 3, 4, 5};
    for (auto i : numbers) {
        q.push(i);
    }
    for (auto j : numbers) {
        auto tmp = q.front();
        assert(tmp == j);
        q.pop();   
    }

    return 0;
}