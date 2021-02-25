// Bellman-Ford最短路径算法

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

class Edge {
public:
    Edge(int first, int second, int weight):first(first),second(second),weight(weight){}
    int first;
    int second;
    int weight;
    friend ostream & operator<<(ostream & os,const Edge & e);
};

ostream & operator<<(ostream & os,const Edge & e) {
    os << "<" << e.first << "," << e.second << "," << e.weight << ">";
    return os;
}

// 有向图
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

    void shortest_path(int src, int dst) {
        vector<int> dist = vector<int>(this->numVertices, INT_MAX);
        vector<int> prev = vector<int>(this->numVertices, -1);
        if (this->bellman_ford(src, dist, prev)) {
            cout << "dist: ";
            for (auto d : dist) {
                cout << d << " ";
            } 
            cout << endl << "path: ";
            list<int> path;
            int u = dst;
            if (prev[u] != -1) {
                while (prev[u] != -1) {
                    path.push_front(u);
                    u = prev[u];    
                }
            }
            for (auto p : path) {
                cout << p << " ";
            }
        } else {
            cout << "shortest isn't exist." << endl;
        }
    }

    bool bellman_ford(int src, vector<int> &dist, vector<int> &prev) {
        // step 1 initial dist and prev
        for (int i = 0; i < this->numVertices; ++i) {
            dist[i] = INT_MAX;
            prev[i] = -1;
        }
        dist[src] = 0;

        // step 2 repead relax |V|-1 
        auto edges = this->edges();
        for (int i = 0; i < this->numVertices; ++i) {
            for (auto e : edges) {
                if (dist[e.first] + e.weight < dist[e.second]) {
                    dist[e.second] = dist[e.first] + e.weight;
                    prev[e.second] = e.first;
                }
            }
        }

        // step 3 check negative loop
        for (auto e : edges) {
            if (dist[e.first] + e.weight < dist[e.second]) {
                cout << "detect negative loop exist." << endl;
                return false;
            }
        }

        return true;
    }

    void addEdge(int v1, int v2, int value = 1) {
        matrix[v1][v2] = value;
    }

    void removeEdge(int v1, int v2) {
        matrix[v1][v2] = 0;
    }

    int distance(int v1, int v2) {
        return matrix[v1][v2];
    }

    vector<Edge> edges() {
        vector<Edge> e = vector<Edge>();
        for (int i = 0; i < this->numVertices; ++i) {
            for (int j = 0; j < this->numVertices; ++j) {
                if (this->matrix[i][j] != 0) {
                    e.push_back(Edge(i, j, this->matrix[i][j]));
                }
            }
        }

        return e;
    }    

    friend ostream & operator<<(ostream & os,const Graph & g);
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


};

ostream & operator<<(ostream & os,const Graph & g) {
    for (int i = 0; i < g.numVertices; ++i) {
            os << i << " : ";
            for (int j = 0; j < g.numVertices; ++j) {
                os << g.matrix[i][j] << " ";
            }
            os << endl;
        } 
    return os;
}


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
    cout << g << endl;;

    auto edges = g.edges();
    for (auto e : edges) {
        cout << e << endl;
    }
    g.shortest_path(0, 4);
}

void test_negative() {
    Graph g(5);
    g.addEdge(0, 1, 3); 
    g.addEdge(0, 2, 2); 
    g.addEdge(1, 3, 1); 
    g.addEdge(2, 3, -5); 
    g.addEdge(2, 4, 8); 
    g.addEdge(3, 4, 4); 
    cout << g << endl;;

    auto edges = g.edges();
    for (auto e : edges) {
        cout << e << endl;
    }
    g.shortest_path(0, 4);
}

void test_negative_loop() {
    Graph g(5);
    g.addEdge(0, 1, 3); 
    g.addEdge(0, 2, 2); 
    g.addEdge(1, 3, 1); 
    g.addEdge(2, 3, -5); 
    g.addEdge(2, 4, 8); 
    g.addEdge(3, 4, 4); 
    g.addEdge(3, 0, 1); //检测负权环
    cout << g << endl;;

    auto edges = g.edges();
    for (auto e : edges) {
        cout << e << endl;
    }
    g.shortest_path(0, 4);  
}

int main() {
    cout << "test normal case:" << endl;
    test();
    cout << "test negative case: " << endl;
    test_negative();
    cout << "test negative loop case: " << endl;
    test_negative_loop();


    return 0;
}