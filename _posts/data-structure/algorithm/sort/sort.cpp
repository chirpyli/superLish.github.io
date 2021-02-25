// 各种内排序算法的实现
#include<memory>
#include<cstring>
#include<iostream>
#include<cassert>

using namespace std;

template<class T>
void print_array(const T* a, const int n) {
    cout << "array: ";
    for (int i = 0; i < n; ++i) {
        cout << *(a + i) << " ";
    }
    cout << endl;
}

// 冒泡排序法
template<class T>
void bubble_sort(T* a, const int n) {
    T tmp;
    for (int i = 1; i < n; ++i) {
        for (int j = n - 1; j >= i; --j) {
            if (a[j] < a[j-1]) {
                tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
            }
        }
    }
}

// 双向冒泡法
template<class T>
void double_bubble_sort(T* a, const int n) {
    T tmp;
    int left = 1;
    int right = n - 1;
    int t;
    do {
        // 正向部分
        for (int i = right; i >= left; --i) {
            if (a[i] < a[i-1]) {
                tmp = a[i-1];
                a[i-1] = a[i];
                a[i] = tmp;
                t = i;
            }
        }
        left = t + 1;
        // 反向部分
        for (int i = left; i < right + 1; ++i) {
            if (a[i] < a[i-1]) {
                tmp = a[i];
                a[i] = a[i-1];
                a[i-1] = tmp;
                t = i;
            }    
        }
        right = t - 1;
    } while (left <= right);
}

// 交换排序法（每次用当前的元素一一的同其后的元素比较并交换）
template<class T>
void swap_sort(T* a, const int n) {
    T tmp;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] > a[j]) {
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

// 选择排序法
template<class T>
void select_sort(T* a, const int n) {
    T tmp;
    int pos;
    for (int i = 0; i < n - 1; ++i) {
        T min = a[i];
        pos = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < min) {
                min = a[j];
                pos = j;
            }
        }
        tmp = a[i];
        a[i] = min;
        a[pos] = tmp;
    }
}

// 插入排序法
template<class T>
void insert_sort(T* a, const int n) {
    T tmp;
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; --j) {
            if (a[j] < a[j-1]) {
                tmp = a[j-1];
                a[j-1] = a[j];
                a[j] = tmp;
            } else 
                break;
        }
    }
}


template<class T>
void quick_recursion_sort(T* a, const int begin, const int end) {
    int left = begin;
    int right = end;
    const int mp = (begin + end) / 2;   // 中间值
    const T middle = a[mp];
    T tmp;
    do {
        while (left < mp && a[left] < middle)
            ++left;
        while (right > mp && a[right] > middle)
            --right;
        
        if (left <= right) {
            tmp = a[left];
            a[left] = a[right];
            a[right] = tmp;
            ++left;
            --right;
        }
    } while (left <= right);

    if (begin < right)
        quick_recursion_sort(a, begin, right);
    
    if (end > left)
        quick_recursion_sort(a, left, end);

}

// 快速排序法
template<class T>
void quick_sort(T* a, const int n) {
    quick_recursion_sort<T>(a, 0, n - 1);    
}


template<class T>
void merge(T* a, const int start, const int mid, const int end) {
    // const int n1 = mid - start + 1;
    // const int n2 = end - mid;
    const int n = end - start + 1;
    T* b = new T[n];
    int k = 0;
    int i = start;
    int j = mid + 1;
    for (; i <= mid && j <= end; ++k) {
        if (a[i] < a[j]) {
            b[k] = a[i++];
        } else {
            b[k] = a[j++];
        }
    }
    
    if (j > end) {
        while (i <= mid) {
            b[k++] = a[i++];
        }
    }

    if (i > mid) {
        while (j <= end) {
            b[k++] = a[j++];
        }
    }

    for (int i = 0, j = start; i < n;) {
        a[j++] = b[i++];
    }

    delete [] b;
}


// 归并排序
template<class T>
void merge_sort(T* a, int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(a, start, mid);
        merge_sort(a, mid + 1, end);
        merge(a, start, mid, end);
    } 
}

// 桶排序
void bucket_sort(int* a, const int n) {
    const int vmax = 20;
    int* t = new int[vmax];
    memset(t, 0, 20 * sizeof(int)); 
    for (int i = 0; i < n; ++i) {
        t[a[i]] = 1;
    }
    for (int i = 0, j = 0; i < vmax; ++i) {
        if (t[i] == 1) {
            a[j++] = i;
        }
    }
}


int main() {
    int a[] = {1,4,6,3,9,13,2};
    int b[] = {1,3,4,6,2,3,9};
    // bubble_sort<int>(a, sizeof(a)/sizeof(int));
    // double_bubble_sort<int>(a, sizeof(a)/sizeof(int));
    // swap_sort<int>(a, sizeof(a)/sizeof(int));
    // select_sort<int>(a, sizeof(a)/sizeof(int));
    // insert_sort<int>(a, sizeof(a)/sizeof(int));
    // quick_sort<int>(a, sizeof(a)/sizeof(int));

    // merge<int>(b, 0, 3, sizeof(b)/sizeof(int) - 1);
    // merge_sort<int>(a, 0, sizeof(a)/sizeof(int) - 1);
    bucket_sort(a, sizeof(a)/sizeof(int));
    print_array<int>(a, sizeof(a)/sizeof(int));
}