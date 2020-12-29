/****************************************************
	> File Name: middle_num.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 一  5/ 4 00:08:45 2020
 ****************************************************/

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

// 此份代码需要用 C++11 标准编译
// 定义新类型：MiddleHeap，代表了维护中位数的对顶堆
// insert ：插入元素的方法
// seek   ：查询中位数
// output ：输出大顶堆和小顶堆中的元素
class MiddleHeap {
public:
    MiddleHeap() { __t = 0; }
    
    // 插入 val 元素
    // 根据关键元素，判断 val 元素插入的位置
    // 如果大顶堆与小顶堆的元素相差了 2 个
    // 说明需要调整两个堆的关键元素了
    void insert(int val) {
        if (max_heap.size() == 0 || -val >= max_heap.begin()->first) {
            max_heap.insert(PII(-val, __t++));
        } else {
            min_heap.insert(PII(val, __t++));
        }
        
        if (max_heap.size() + 2 == min_heap.size()) {
            int num = min_heap.begin()->first;
            int t = min_heap.begin()->second;
            max_heap.insert(PII(-num, t));
            min_heap.erase(min_heap.begin());
        }
        if (min_heap.size() + 2 == max_heap.size()) {
            int num = max_heap.begin()->first;
            int t = max_heap.begin()->second;
            min_heap.insert(PII(-num, t));
            max_heap.erase(max_heap.begin());
        }
        return ;
    }
    
    // 查询中位数
    // 两个堆中的元素数量相同，取关键元素平均值
    // 否则，中位数就是元素数量较多的那个堆里面的关键元素
    double seek() {
        double val1 = -max_heap.begin()->first;
        double val2 = min_heap.begin()->first;
        if (max_heap.size() == min_heap.size()) {
            return (val1 + val2) / 2.0;
        }
        return max_heap.size() > min_heap.size() ? val1 : val2;
    }

    void output() {
        cout << "max heap : ";
        for (auto x : max_heap) {
            cout << -x.first << " ";
        }
        cout << endl;
        cout << "min heap : ";
        for (auto x : min_heap) {
            cout << x.first << " ";
        }
        cout << endl;
        return ;
    }
    
private:
    typedef pair<int, int> PII;
    set<PII> max_heap, min_heap;
    int __t;
};

int main() {
    int val;
    MiddleHeap s;
    while (cin >> val) {
        s.insert(val);
        s.output();
        cout << "中位数是：" << s.seek() << endl;
    }
    return 0;
}
