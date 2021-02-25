#include<iostream>
#include<vector>
#include<cassert>

using namespace std;

template<class T>
class MaxHeap {
public:
    MaxHeap():count(0) {
        data = vector<T>();
        T nul = T();
        data.push_back(nul);        // 采取已1为基数存储元素，0空着 
    }

    MaxHeap(T* a, int length):count(length) {
        data = vector<T>(a, a + length);
        T nul = T();
        data.insert(data.begin(), nul);

        for (int i = length / 2; i > 0; --i) {
            build_heap(i);
        }
    }

    void push(const T& e);     // 新增一个元素
    const T pop();             // 弹出根节点


    void print();   // 调试测试用
protected:
    vector<T> data;     
    size_t count;
    void swap(int a, int b) {
        T tmp = this->data[a];
        this->data[a] = this->data[b];
        this->data[b] = tmp;
    }

    void build_heap(int i);
};

template<class T>
void MaxHeap<T>::build_heap(int i) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;

    if (left <= this->count && this->data[left] > this->data[largest])
        largest = left;

    if (right <= this->count && this->data[right] > this->data[largest])
        largest = right;

    if (largest != i) {
        this->swap(i, largest);
        build_heap(largest);
    }
}

template<class T>
void MaxHeap<T>::push(const T& e) {
    this->count++;
    this->data.push_back(e);
    int i = this->count;
    while (i != 1) {
        int parent = i / 2;
        if (this->data[i] > this->data[parent]) {
            swap(i, parent);
            i = parent;
        } else 
            break;
    }
}

template<class T>
const T MaxHeap<T>::pop() {
    assert(this->count > 0); 
    T top = this->data[1];

    swap(1, this->count);
    this->count--;
    this->data.pop_back();
    int i = 1;
    int largest = 2 * i + 1;
    // 选最大的子节点进行交换
    while (largest <= this->count) {
        int left = 2 * i;
        int right = 2 * i + 1;
        if (this->data[left] > this->data[right] && this->data[left] > this->data[i]) {
            swap(left, i);
            i = left;
            largest = 2 * i + 1;
        } else if (this->data[left] < this->data[right] && this->data[right] > this->data[i]) {
            swap(right, i);
            i = right;
            largest = 2 * i + 1;
        } else 
            break;
    }

    int left = 2 * i + 1;
    if (left == this->count) {
        if (this->data[i] < this->data[left]) {
            swap(i, left);
        }
    }

    return top;
}

template<class T>
void MaxHeap<T>::print() {
    cout << "max heap array: ";
    for (int i = 1; i <= this->count; ++i) {
        cout << this->data[i] << " ";
    }
    cout << endl;
}