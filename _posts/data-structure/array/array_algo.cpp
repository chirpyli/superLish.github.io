#include<iostream>
#include<cassert>
#include<map>

using namespace std;

// 递归数组求和
template<class T>
T asum1(T* a, int n) {
    assert(a != nullptr);
    if (1 == n) {
        return a[0];
    }

    return a[n-1] + asum1(a, n-1);
}

// 一个for循环打印二维数组
void print_array() {
	const int x = 2;
	const int y = 4;
    int b[2][4] = {1, 2, 3, 4, 5, 6, 7, 8};
	for(int i = 0;i < x * y;i++) {
		cout << b[i/y][i%y] << " ";   //这里是重点
	}
    cout << endl;
}

// 如何用递归算法判断一个数组是否是递增？
template<class T>
bool is_array_increase(T* a, int n) {
    assert(n > 1);
    if (2 == n) {
        return a[0] < a[1];
    }

    if (a[n-1] < a[n-2]) {
        return false;
    } else {
        return is_array_increase(a, n-1);
    }
}

// 二分查找算法的实现，时间复杂度O(log(n))
template<class T>
int binary_search(T *a, const int n, const T &k) {
    assert(a != nullptr);
    int begin = 0;
    int end = n - 1;
    while (begin <= end) {
        int m = (begin + end) / 2;
        if (a[m] < k) {
            begin = m + 1;
        } else if (a[m] > k) {
            end = m - 1;
        } else {
            return m;
        }
    }

    return -1;
}

template<class T>
int binary_search_edge(T* a, const int n, const T& k, bool isLeft) {
    assert(a != nullptr);
    int begin = 0;
    int end = n - 1;
    int last = -1;
    while (begin <= end) {
        int m = (begin + end) / 2;
        if (a[m] < k) {
            begin = m + 1;
        } else if (a[m] > k) {
            end = m - 1;
        } else {
            last = m;
            if (isLeft)
                end = m - 1;
            else
                begin = m + 1;
        }
    }

    return last;
}

// 如何在排序数组中，找出给定数字出现的次数? 时间复杂度O(log(n))
template<class T>
int binary_search_count(T* a, const int n, const T& k) {
    int left = binary_search_edge<T>(a, n, k, true);
    int right = binary_search_edge<T>(a, n, k, false);
    if (left == -1 || right == -1)
        return 0;

    return right - left + 1;
}

// 如何找出数组中重复次数最多的数？
template<class T>
T min_duplicate(T* a, const int n) {
    assert(a != nullptr && n > 1);
    std::map<T, int> m_map;
    T v = a[0];
    for (int i = 1; i < n; ++i) {
        if (++m_map[a[i]] > v)
            v = a[i];
    }

    return v;
}

// 如何在O(n)的时间复杂度内找出数组中出现次数超过一半的数？
template<class T>
T find_max_frequent(T* a, const int n) {
    assert(a != nullptr);    
    T candidate;
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (0 == count) {
            candidate = a[i];
            ++count;
        } else {
            if (candidate == a[i]) {
                ++count;
            } else {
                --count;
            }
        }
    }

    return candidate;
}

// 如何找出数组中出现奇数次的元素？
template<class T>
T find_odd_element(const T* a, const int n) {
    assert(a != nullptr);
    T v = a[0];
    for (int i = 1; i < n; ++i) {
        v = v ^ a[i];
    }

    return v;
}

int main() {
    int a[] = {1,2,3,4,5,6,7,8,9};
    int sum = asum1<int>(a, sizeof(a)/sizeof(int));
    cout << sum << endl;

    print_array();

    int b[] = {1,2,3,4,5,7,6,8,9};
    bool v = is_array_increase<int>(a, sizeof(a)/sizeof(int));
    cout << v << endl;

    v = is_array_increase<int>(b, sizeof(b)/sizeof(int));
    cout << v << endl;

    int pos = binary_search<int>(a, sizeof(a)/sizeof(int), 7);
    cout << pos << endl;

    int c[] = {1,2,3,4,5,6,6,6,6,6,6,6,7,8,9};
    // cout << binary_search_count<int>(c, sizeof(c)/sizeof(int), 6) << endl;
    cout << "重复次数最多的数是：" << min_duplicate<int>(c, sizeof(c)/sizeof(int)) << endl;
    cout << "超过一般的数是：" << find_max_frequent<int>(c, sizeof(c)/sizeof(int)) << endl;

    int e[] = {1,1,2,3,2};
    cout << "奇数次元素：" << find_odd_element<int>(e, sizeof(e)/sizeof(int)) << endl;
}