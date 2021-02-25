// 堆排序
#include<iostream>
#include<algorithm>

using namespace std;

// 这里堆中根节点元素在0位置处， iParent = (i-1)/2, iLeft = 2*i+1, iRight = 2*i+2
template<class T>
void siftDown(T *a, int start, int end) {
    int root = start;
    while((2*root+1) <= end) {
        int child = 2 * root + 1;
        int swap = root;
        if (a[swap] < a[child])
            swap = child;
        if ((child+1) <= end && a[swap] < a[child+1])
            swap = child + 1;
        if (swap != root) {
            std::swap(a[root], a[swap]);
            root = swap;
        } else{
            return;  
        }
    } 
}


template<class T>
void heapify(T* a, int count) {
    int start = (count - 1 - 1) / 2;
    while (start >= 0) {
        siftDown(a, start, count-1);
        --start;
    }
}


template<class T>
void heapsort(T* a, int count) {
    heapify(a, count);

    int end = count -1;
    while (end > 0) {
        swap(a[0], a[end]);
        --end;
        siftDown(a, 0, end);
    }
}


int main() {
	int data[] = {8, 3, 13, 1, 4, 6, 7, 11, 12, 18, 24, 29};
    heapsort<int>(data, sizeof(data)/sizeof(int));
    for (auto i : data) {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}