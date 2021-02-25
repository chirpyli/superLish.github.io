#include<iostream>
using namespace std;

const int N = 8;    // 八皇后问题
int solutions = 0;

// 第n个放的皇后一定在第n-1行，但不确定在第几列，可以先试探一下，不行再右移再试
bool is_ok(int row) {

}

// 回溯算法，默认从第0行开始
void back_tracking(int row = 0) {
    if (N == row) {
        ++solutions;
    }
}


int main() {
    back_tracking();
    cout << "number of " << N << "queens solutions is : " << solutions;

    return 0;
}