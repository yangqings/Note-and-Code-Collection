/**********************************************************
	> File Name: quick_sort.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  5/27 03:53:34 2020
 **********************************************************/

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
#include <ctime>
using namespace std;
#define TIME(func) ({ \
    int b = clock(); \
    func; \
    int e = clock(); \
    (e - b) * 1000.0/ CLOCKS_PER_SEC; \
})

void quick_sort_old(int *arr, int l, int r) {
    if (l >= r) return ;
    int x = l, y = r, z = arr[l]; 
    while (x < y) {
        while (x < y && arr[y] >= z) --y;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[x] <= z) ++x;
        if (x < y) arr[y--] = arr[x];
    }
    arr[x] = z;
    quick_sort_old(arr, l, x - 1);
    quick_sort_old(arr, x + 1, r);
    return ;
}

inline int select_value(int a, int b, int c) {
    if (a > b) swap(a, b);
    if (a > c) swap(a, c);
    if (b > c) swap(b, c);
    return b;
}

void quick_sort_new(int *arr, int l, int r) {
    while (l < r) {
        int x = l, y = r, z = select_value(arr[l], arr[r], arr[(l + r) >> 1]);
        do {
            while (arr[x] < z) ++x;
            while (arr[y] > z) --y;
            if (x <= y) {
                swap(arr[x], arr[y]);
                x++, y--;
            }
        } while (x <= y);
        quick_sort_new(arr, x, r);
        r = y;
    }
    return ;
}

#define MAX_N 1000000
int a1[MAX_N + 5], a2[MAX_N + 5];

void test_one(int t) {
    for (int i = 0; i < MAX_N; i++) {
        a1[i] = rand();
        a2[i] = a1[i];
    }
    int t1 = TIME(quick_sort_old(a1, 0, MAX_N - 1));
    int t2 = TIME(quick_sort_new(a1, 0, MAX_N - 1));
    printf("第 %d 轮测试，quick_sort_old(%dms)，quick_sort_new(%dms)\n", t, t1, t2);
    return ;
}

void test_random(int n) {
    printf("测试次数：%d\n每轮测试数据量：%d\n", n, MAX_N);
    for (int i = 1; i <= n; i++) {
        test_one(i);
    }
    return ;
}

int main() {
    srand(time(0));
    test_random(10);
    return 0;
}
