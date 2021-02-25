// 图的邻接矩阵表示

#include<iostream>
using namespace std;


// 无向有权图
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

    bool isEdge(int v1, int v2) {
        return matrix[v1][v2] != 0 ? true : false ;
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
};



/*
0 : 0 1 1 1 
1 : 1 0 1 0 
2 : 1 1 0 0 
3 : 1 0 0 0 
 */
void test_adjacency_matrix() {
    Graph g(4);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.print();
}

int main() {
    test_adjacency_matrix();


    return 0;
}