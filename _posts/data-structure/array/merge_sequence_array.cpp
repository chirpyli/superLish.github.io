
// #要求：请不要使用系统库、第三方库提供的便捷功能，包括排序。如有需要，请自行实现。

// #归并排序。给定两个有序数组（整数、递增），请将它们归并成一个有序数组。
// #例：
// #输入：[1,3,5,7], [2,4,6,8]
// #输出：[1,2,3,5,6,7,8]

#include<cassert>
#include<algorithm>
#include<iostream>
using namespace std;

void merge_sort(int* a, int *b, const int alen, const int blen, int c[]) {
    assert(a != nullptr || b != nullptr);
    int pos_a = 0;
    int pos_b = 0;
    int pos = 0;
    while(pos_a < alen && pos_b < blen) {
        if (a[pos_a] < b[pos_b]) {
            c[pos++] = a[pos_a++];
        } else {
            c[pos++] = b[pos_b++];
        }
    }

    if (pos_a == alen) {
        while(pos_b < blen) {
            c[pos++] = b[pos_b++];
        }
    } else if (pos_b == blen) {
        while(pos_a < alen) {
            c[pos++] = a[pos_a++];
        }
    }
}

// 如何计算两个有序整型数组（没有重复元素）的交集？
// 例如 a={0,1,2,3,4};b={1,3,5,7,9}; 交集为{1，3}。
std::pair<int*, int> mixd(int* a, const int na, int *b, const int nb) {
    assert(a != nullptr && b != nullptr);
    int pa = 0;
    int pb = 0;
    int p = 0;
    int* m = new int[min(na, nb)];
    while (pa < na && pb < nb) {
        if (a[pa] == b[pb]) {
            m[p++] = a[pa];
            ++pa;
            ++pb;
        } else if (a[pa] < b[pb]) {
            ++pa;
        } else {
            ++pb;
        }
    }

    return std::make_pair(m, p);
}


int main() {
    int a[7] = {1,3,5,7,9,11,21};
    int b[4] = {2,4,6,8};
    int c[11];
    merge_sort(a, b, 7, 4, c);
    for(auto i : c) {
        cout << i << " ";
    }
    cout << endl;

    int d[] = {1,2,3,4,5,6};
    auto p = mixd(b, sizeof(b)/sizeof(int), d, sizeof(d)/sizeof(int));
    for (int i = 0; i < p.second; ++i) {
        cout << p.first[i] << " ";
    }
    delete [] p.first;

    return 0;
}