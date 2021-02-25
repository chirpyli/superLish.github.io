// 图的邻接链表表示

#include<iostream>
#include<list>
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
};

/*
0 : 1 2 3 
1 : 2 
2 : 
3 :
 */
void test_adjacency_list() {
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.print();
}

int main() {
    test_adjacency_list();

    return 0;
}