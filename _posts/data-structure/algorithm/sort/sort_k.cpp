// 题目：输入一个序列，给出序列中第k大的数。
// 思路： 对输入序列的前k个数构造最小堆，遍历后面k到n，如果有大于最小堆的最小值的，赋值过去，执行下移操作，遍历完成后，最小堆的根即为第k大的数
// 时间复杂度， 遍历一遍O(n) + 构造堆O(k) + 遍历时需要下移的k个操作O(log(k))
#include <iostream>
#include<algorithm>
using namespace std;

// 最小堆
// 这里堆中根节点元素在0位置处， iParent = (i-1)/2, iLeft = 2*i+1, iRight = 2*i+2
template<class T>
void siftDown(T *a, int start, int end) {
    int root = start;
    while((2*root+1) <= end) {
        int child = 2 * root + 1;
        int swap = root;
        if (a[swap] > a[child])
            swap = child;
        if ((child+1) <= end && a[swap] > a[child+1])
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

void print_array(int data[], int start, int end) {
    cout << "array[" << start << "," << end << "] = ";
    for (int i = start; i <= end; ++i) {
        cout << data[i] << " ";
    }

    cout << endl;
}

void swap(int *a, int i, int j) {
    if (i != j) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

void reverse(int *a, int start, int end) {
    while (start < end) {
        swap(a, start, end);
        ++start;
        --end;
    }
}

// 快速排序
void quicksort(int *a, int left, int right) {
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int key = a[left];          // 中间这个值随便选一个就行，可以是第一个元素，也可以选中间的

    while(i < j) {
        while (i < j && key <= a[j])
            --j;
        swap(a, i, j);      // 从右边发现有值比选定的key小，将这个值甩到前面，

        while (i < j && key >= a[i])
            ++i;
        swap(a, i, j);          // 从右边发现有值比选定的key大，将这个值甩到后面，
    }
    // 因为每次只前进或后退一步，所以终止的条件是i==j，而且a[i]==key
    quicksort(a, i+1, right);
    quicksort(a, left, i-1);    
}



// 给出序列中第k大的数
int sequence_k(int *a, const int n, const int k) {
    if (n < k) {
        cout << "error" << endl;
        return -1;
    }

    heapify<int>(a, k);

    for (int i=k; i<n;++i) {
        if (a[i]>a[0]) {
            // 更新堆
            a[0] = a[i];
            siftDown<int>(a, 0, k-1);
        }
    }

    return a[0];
}


int main() {

    int a[] = {7, 19, 18, 1, 0, 3};
    // quicksort(a, 0, sizeof(a)/sizeof(int)-1);
    // print_array(a, 0, sizeof(a)/sizeof(int)-1);
    // reverse(a, 0, sizeof(a)/sizeof(int)-1);
    // print_array(a, 0, sizeof(a)/sizeof(int)-1);

    int k = sequence_k(a, sizeof(a)/sizeof(int), 2);
    cout << "k=" << k << endl;


    return 0;
}