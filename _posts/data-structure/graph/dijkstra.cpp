// Dijkstra最短路径算法
// #pragma GCC diagnostic error "-std=c++11"

#include <cassert>
#include<vector>
#include<list>
#include<queue>
#include<iostream>
#include<utility> 
#include<climits>
#include<algorithm>
using namespace std;

class Vertex {
public:
    Vertex(int v, int d = INT_MAX):vertex(v),distance(d){}
    Vertex(const Vertex& v) {
        this->vertex = v.vertex;
        this->distance = v.distance;
    }
    void setDistance(int d) {
        this->distance = d;
    }

    int vertex;
    int distance;

    bool operator< (const Vertex &v) const {
        return this->distance > v.distance;
    }
};

// 无向有权（非负值）图
class Graph {
public:
    Graph(int numVertices) {
        this->numVertices = numVertices;
        matrix = new int*[numVertices];
        for (int i = 0; i < numVertices; ++i) {
            matrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    void addEdge(int v1, int v2, int value = 1) {
        matrix[v1][v2] = value;
        matrix[v2][v1] = value;
    }

    void removeEdge(int v1, int v2) {
        matrix[v1][v2] = 0;
        matrix[v2][v1] = 0;
    }

    list<int> dijkstraShortestPath(int src, int dst) {
        assert(src != dst);
        // vector<int> prev = dijkstra(src);
        vector<int> prev = dijkstra_priority_queue(src);        
        list<int> path;
        int u = dst;
        if (prev[u] != -1) {
            while (prev[u] != -1) {
                path.push_front(u);
                u = prev[u];    
            }
        }

        return path;
    }

    // dijkstra经典实现
    vector<int> dijkstra(int source) {
        vector<int> prev;
        vector<int> dist;
        list<int> *vlist = new list<int>;

        for (int i = 0; i < this->numVertices; ++i) {
            dist.push_back(INT_MAX);
            prev.push_back(-1);
            vlist->push_back(i);
        }
        dist[source] = 0;
 
        while (!vlist->empty()) {
            int u =  minVertexDistance(vlist, &dist);
            vlist->remove(u);
            vector<int> neighbors = neighbor_vertices(u, vlist);
            for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
                int alt = dist[u] + distance(u, *it);
                if (alt < dist[*it]) {
                    dist[*it] = alt;
                    prev[*it] = u;
                }
            }
        }

        // 打印距离值
        for (int i = 0; i < numVertices; ++i) {
            cout << i << " : " << dist[i] << endl;
        }

         return prev;
    }

    // dijkstra优先队列实现，这里使用的是普通的优先队列，事实上更应该使用Brodal queue或者Fibonacci heap
    vector<int> dijkstra_priority_queue(int source) {
        priority_queue<Vertex> pq;
        vector<int> dist;
        vector<int> prev;
        vector<bool> *visit = new vector<bool>;
        for (int i = 0; i < this->numVertices; ++i) {
            if (i != source) {
                dist.push_back(INT_MAX);
            } else {
                dist.push_back(0);
            }
            prev.push_back(-1);
            visit->push_back(false);
        }

        pq.push(Vertex(source, 0));
        while (!pq.empty()) {
            Vertex u(pq.top());
            pq.pop(); 
            if ((*visit)[u.vertex])
                continue;
            cout << endl <<"visit :" << u.vertex << "-----> ";
            (*visit)[u.vertex] = true;         
            vector<int> neighbor = neighbor_vertices(u.vertex, visit);
            cout << "detect neightor: ";            
            for (auto v : neighbor) {
                cout << "<" << v << ",";
                int alt = dist[u.vertex] + distance(u.vertex, v);
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u.vertex;
                    pq.push(Vertex(v, alt));
                }
                cout << dist[v] << "> ";
            }
        }

        // 打印距离值
        for (int i = 0; i < numVertices; ++i) {
            cout << i << " : " << dist[i] << endl;
        }

        delete visit;
        return prev;
    }

    vector<int> neighbor_vertices(int vertex, const list<int> *visit) {
        vector<int> neighbor;
        for (auto i = visit->begin(); i != visit->end(); ++i) {
            if (matrix[vertex][*i] != 0) {
                neighbor.push_back(*i);
            }
        }

        return neighbor;
    }

    vector<int> neighbor_vertices(int vertex, const vector<bool> *visit) {
        vector<int> neighbor;
        for (int i = 0; i < numVertices; ++i) {
            if (matrix[vertex][i] != 0 && visit->at(i) == false) {
                neighbor.push_back(i);
            }
        }

        return neighbor;
    }

    int distance(int v1, int v2) {
        return matrix[v1][v2];
    }

    void print() {
        for (int i = 0; i < numVertices; ++i) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        } 
    }

    ~Graph() {
        for (int i = 0; i < numVertices; ++i) {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

private: 
    int **matrix;
    int numVertices;

    bool isEdge(int v1, int v2) {
        return matrix[v1][v2] >= 0 ? true : false ;
    }

    int minVertexDistance(list<int> *vlist, vector<int> *dist) {
        assert(!vlist->empty() && !dist->empty());
        auto it = vlist->begin();
        int v = *it;
        int min = (*dist)[v];
        for ( ;it!= vlist->end(); ++it) {
            if ((*dist)[*it] < min) {
                v = *it;
            }
        }

        return v;
    }
};

/*
邻接矩阵
0 : 0 3 2 0 0 
1 : 3 0 0 1 0 
2 : 2 0 0 5 8 
3 : 0 1 5 0 4 
4 : 0 0 8 4 0 

距离
0 : 0
1 : 3
2 : 2
3 : 4
4 : 8

最短路径：path: 1 3 4
 */
void test() {
    Graph g(5);
    g.addEdge(0, 1, 3); 
    g.addEdge(0, 2, 2); 
    g.addEdge(1, 3, 1); 
    g.addEdge(2, 3, 5); 
    g.addEdge(2, 4, 8); 
    g.addEdge(3, 4, 4); 
    g.print();

    // vector<int> prev = g.dijkstra(0);
    // vector<int> prev = g.dijkstra_priority_queue(0);
    list<int> path = g.dijkstraShortestPath(0, 4);
    cout << "path: ";
    for (auto it = path.begin(); it != path.end(); ++it) {
        cout << *it << " ";
    }
}

// 如果是无向图中带有负权边的话，一定是没有最短路径的，有向图带有负权边的话，Dijkstra可能不会计算出最短路径。
/*
test negative case:    
0 : 0 5 6 
1 : 5 0 -2 
2 : 6 -2 0 

visit :0-----> detect neightor: <1,5> <2,6> 
visit :1-----> detect neightor: <2,3> 
visit :2-----> detect neightor: 0 : 0
1 : 5
2 : 3
path: 1

按照上面的连图画出来最短路径应该是0-2-1，而最后的结果确是0-1，
这是因为每次都是选取当前最短距离节点，先访问0，然后从1和2中选择了更小的1，
1访问完后，如果边权重全部是正的话，因为选1的时候已经是最小距离了，所以到下一个节点
如果是正的话是无论如何也不可能比再比1当前的距离小了，而如果是负值的话，则就可能会比当前值小，
从而打破了Dijkstra的贪心规则。
*/
void test_negative() {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 6);
    g.addEdge(2, 1, -2);
    g.print();
    list<int> path = g.dijkstraShortestPath(0, 1);
    cout << "path: ";
    for (auto it = path.begin(); it != path.end(); ++it) {
        cout << *it << " ";
    }
}

int main() {
    cout << "test normal case:" << endl;
    test();
    cout << endl << "test negative case:" << endl;
    test_negative();


    return 0;
}