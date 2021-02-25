//2个栈实现一个队列
#include<stack>
#include<cassert>
#include<iostream>
using namespace std;

template<class T>
class Queue
{
public:
	Queue(){}
	virtual ~Queue(){}

	void push(const T& e) {
		m_stackA.push(e);
	}

	void pop() {
		if(m_stackB.empty()) {
			while(!m_stackA.empty()) {
				m_stackB.push(m_stackA.top());
				m_stackA.pop();
			}
		}
		m_stackB.pop();
	}

	size_t size() const {
		return m_stackA.size() + m_stackB.size();
	}

	bool empty() {
		return m_stackA.empty() && m_stackB.empty();
	}

	T& top() {
		if(m_stackB.empty()) {
			while(!m_stackA.empty()) {
				m_stackB.push(m_stackA.top());
				m_stackA.pop();
			}
		}
		return m_stackB.top();
	}

protected:
	stack<T> m_stackA;	//栈A
	stack<T> m_stackB;	//栈B
};

int main() {
	Queue<int> m_queue;
	m_queue.push(1);
	m_queue.push(2);
    assert(m_queue.top() == 1);
    m_queue.pop();
    assert(2 == m_queue.top());

	return 0;
}