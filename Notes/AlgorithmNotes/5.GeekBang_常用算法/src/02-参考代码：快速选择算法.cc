
/************************************************************
	> File Name: quick_select.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  5/27 03:35:26 2020
 ************************************************************/

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

// arr  : 待查找数组
// l--r : 待查找区间
// k : 待查找元素的排名
// 在 arr 数组的 l 到 r 区间内，查找排名为 k 的元素
int quick_select(int *arr, int l, int r, int k) {
    // 首先选取基准值，完成 partition 操作
    int x = l, y = r, z = arr[l];
    while (x < y) {
        while (x < y && arr[y] >= z) --y;
        if (x < y) arr[x++] = arr[y];
        while (x < y && arr[x] <= z) ++x;
        if (x < y) arr[y--] = arr[x];
    }
    arr[x] = z;
    // ind 为当前基准值的排名
    // 用基准值的排名与 k 做比较
    // 如果相等，则为基准值
    // 如果 ind > k，在前半部分查找排名第 k 位的元素
    // 如果 ind < k, 在后半部分查找排名第 k - ind 位的元素
    int ind = x - l + 1;
    if (ind == k) return arr[x];
    if (ind > k) return quick_select(arr, l, x - 1, k);
    return quick_select(arr, x + 1, r, k - ind);
}

int main() {
    int n, a[100];
    printf("请输入元素数量:");
    scanf("%d", &n);
    printf("请输入 %d 个元素的值:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    printf("\n以下结果，均来自快速选择算法的结果\n");
    for (int i = 1; i <= n; i++) {
        printf("排名第 %d 位的元素：%d\n", i, quick_select(a, 0, n - 1, i));
    }
    return 0;
}
