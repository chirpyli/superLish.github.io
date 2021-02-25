// Brute-Force 字符串匹配算法

#include<iostream>
#include<string.h>
using namespace std;


bool brute_force(char* text, char* pattern) {
    const int t_len = strlen(text);
    const int p_len = strlen(pattern);
    cout << "text: " << text << " len=" << t_len << endl;
    cout << "pattern: " << pattern << " len=" << p_len << endl;

    int i = 0;
    int j = 0;
    while (i < t_len && j < p_len) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            i = i-j+1;      // 主串回退到匹配起始位置的第二个字节
            j = 0;
        }
    } 
    if (j == p_len) {
        cout << "pattern matches at " << i-j << endl;
        return true;
    } else {
        cout << "pattern mismatch." << endl;
        return false;
    }
}


int main() {
    char* t = "nanjing agriculture university.";
    char* p = "i";
    bool v = brute_force(t, p);


    return 0;
}