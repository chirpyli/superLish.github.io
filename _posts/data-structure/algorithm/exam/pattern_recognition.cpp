/********************************************************************
一维模式识别问题

问题：输入具有n个浮点数的向量x，要求输出输入向量的任意连续子向量中的最大和。
例如：输入向量：{31， -41， 59, 26， -53, 58, 97， -93， -23, 84}  
                        [      ...         ] 输出187      
********************************************************************/
#include<iostream>
#include<algorithm>
#include<cassert>
using namespace std;

// 时间复杂度O(n^2), 通过遍历所有可能子序列解决问题
double pattern_recognition_alg1(const double *a, const uint len) {
    assert(a != nullptr && len > 0);
    double max_subsequence = a[0];
    for (int i = 0; i < len; ++i) {
        double max = 0;
        for (int j = i; j < len; ++j) {
            max += a[j];
            max_subsequence = std::max(max_subsequence, max);
        }
    }

    return max_subsequence;
}

// 时间复杂度O(n)， 主要思路：一个序列加上一个正的序列会变大，而如果探测到当前序列为负，则应重新开始计算子序列
double pattern_recognition_alg2(const double *a, const uint len) {
    assert(a != nullptr && len > 0);
    
    double max_subsequence = a[0];
    double sum = 0;
    for (int begin = 0, end = 0; end < len; ++end) {
        sum += a[end];
        if (sum >= max_subsequence) {
            max_subsequence = sum;
        } else if (sum < 0) {       // 如果累积和依旧大于等于0，end就继续向前，如果累积和小于0，就重置起始begin值为end+1
            begin = end + 1;
            sum = 0;
        }
    }

    return max_subsequence;
}

int main() {
    // 输入参数分3种情况1. 全是负数，2.全是非负数， 3，有负有正，
    double input1[] = {-1,31,-41,59,26,-53,58,97,-93,-23,84,90000};
    double input2[] = {-20, -19, -1, -30};
    double rev1 = pattern_recognition_alg1(input1, sizeof(input1)/sizeof(double));
    cout << "alg1 input1 result is " << rev1 << endl;

    double rev2 = pattern_recognition_alg2(input1, sizeof(input1)/sizeof(double));
    cout << "alg2 input1 result is " << rev2 << endl;

    double rev12 = pattern_recognition_alg1(input2, sizeof(input2)/sizeof(double));
    cout << "alg1 input2 result is " << rev12 << endl;

    double rev22 = pattern_recognition_alg2(input2, sizeof(input2)/sizeof(double));
    cout << "alg2 input2 result is " << rev22 << endl;

    return 0;
}