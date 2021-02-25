// 图的遍历：深度优先、广度优先

#include<iostream>
#include<memory>
#include<list>
#include<stack>
#include<queue>
using namespace std;

//有向无权图
class Graph {
public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjLists = new list<int>[numVertices];
    }

    void addEdge(int src, int dst) {
        adjLists[src].push_back(dst);
    }

    void removeEdge(int src, int dst) {
        adjLists[src].remove(dst);
    }

    void depthFirstSearch(int vertex) {
        bool visited[this->numVertices];
        for (auto i = 0; i < this->numVertices; ++i) {
            visited[i] = false;
        }

        stack<int> m_stack;
        m_stack.push(vertex);
        while (!m_stack.empty()) {
            auto v = m_stack.top();
            if (visited[v]) {
                m_stack.pop();
                continue;
            }

            visit(v);
            visited[v] = true;
            m_stack.pop();
            
            for (auto it = this->adjLists[v].begin(); it != this->adjLists[v].end(); ++ it) {
                if (!visited[*it]) {
                    m_stack.push(*it);
                }
            }
        }
    }

    void breadthFirstSearch(int vertex) {
        bool visited[this->numVertices];
        for (auto i = 0; i < this->numVertices; ++i) {
            visited[i] = false;
        }

        queue<int> m_queue;
        m_queue.push(vertex);
        while(!m_queue.empty()) {
            auto v = m_queue.front();
            if (visited[v]) {
                m_queue.pop();
                continue;
            }

            visit(v);
            visited[v] = true;
            m_queue.pop();

            for (auto it = this->adjLists[v].begin(); it != this->adjLists[v].end(); ++it) {
                if (!visited[*it]) {
                    m_queue.push(*it);
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < numVertices; ++i) {
            cout << i << " : ";
            for (auto it = adjLists[i].begin(); it != adjLists[i].end(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        }
    }

    ~Graph() {
        delete[] adjLists;
    }
private:
    list<int> *adjLists;
    int numVertices;

    void visit(int v) {
        cout << " v" << v << " ";
    }
};


void test_traversal() {
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(2,4);

    g.depthFirstSearch(0);
    cout << endl;
    g.breadthFirstSearch(0);
}

int main() {
    test_traversal();

    return 0;
}
 