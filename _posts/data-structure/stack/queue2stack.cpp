// 两个队列实现一个栈
#include<queue>
#include<cassert>
#include<iostream>
using namespace std;

template<class T>
class Stack
{
public:
	Stack(){}
	virtual ~Stack(){}

	void push(const T& e) {
		m_qa.push(e);
        while (m_qa.size() != 1) {
            T& tmp = m_qa.front();
            m_qb.push(tmp);
            m_qa.pop();
        }
	}

	void pop() {
        assert(!this->empty());
        this->update();
        m_qa.pop();
        this->update();
	}

	size_t size() const {
		return m_qa.size() + m_qb.size();
	}

	bool empty() {
		return m_qa.empty() && m_qb.empty();
	}

	T& top() {
        assert(!this->empty());
        this->update();

        return m_qa.front();
	}

protected:
	queue<T> m_qa;	//栈A
	queue<T> m_qb;	//栈B

private:
    void update() {
        // 如果a为空，b不为空，就将b推到a中
        if (m_qa.empty() && !m_qb.empty()) {
            while (!m_qb.empty()) {
                T& tmp = m_qb.front();
                m_qa.push(tmp);
                m_qb.pop();
            }
        }
            
        // 将a推到b，只留1个元素
        while (m_qa.size() > 1) {
            T& tmp = m_qa.front();
            m_qb.push(tmp);
            m_qa.pop();
        }
    }
};

int main() {
    Stack<int> m_stack;

    for (int i = 0; i < 10; ++i) {
        m_stack.push(i);
    }

    for (int i = 9; i >=0; --i) {
        int tmp = m_stack.top();
        m_stack.pop();
        assert(tmp == i);
    }

	return 0;
}