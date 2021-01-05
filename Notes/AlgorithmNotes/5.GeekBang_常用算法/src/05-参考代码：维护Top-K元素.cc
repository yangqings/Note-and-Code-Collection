/******************************************************
	> File Name: top_k.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 日  5/ 3 23:55:13 2020
 ******************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

// 用 pair 封装两个整型元素
// 第一个 int 值代表数值
// 第二个 int 值是时间戳
// 时间戳是为了防止 set 去重
typedef pair<int, int> PII;

int main() {
    // n 代表元素数量，k 代表要取 k 个最大值
    // val 是每次读入的元素值，t 是时间戳
    // s 是用 set 模拟的小顶堆
    int n, k, val, t = 0;
    set<PII> s;

    // 读入 n 和 k 的值
    // 之后读入 n 个元素的值
    // 每次用读入的元素值和小顶堆的堆顶元素比较
    cin >> n >> k;
    while (n--) {
        cin >> val;
        if (s.size() < k) s.insert(PII(val, t++));
        else if (s.begin()->first < val) {
            s.erase(s.begin());
            s.insert(PII(val, t++));
        }
    }
    
    // 遍历 s 集合，输出最大的 k 个值
    printf("Top-K(%d) : ", k);
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        cout << iter->first << " " ;
    }
    cout << endl;
    return 0;
}
