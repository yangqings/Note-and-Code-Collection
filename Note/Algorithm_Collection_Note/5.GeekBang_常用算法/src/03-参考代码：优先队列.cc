/*************************************************************************
	> File Name: heap.cpp
	> Author: huguang
	> Mail: hug@haizeix.com
	> Created Time: 三  4/29 21:08:08 2020
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/*
* 下面我会用小顶堆，演示一个优先队列
* 你可以自行改成大顶堆
* */
typedef struct Heap {
    int *data; // 存储数据的数组, 默认每个元素的类型都是整型
    int n;     // 现有元素数量
    int size;  // 最大容量
} Priority_Queue;

// 初始化一个最大容量为 size 的优先队列
Priority_Queue *init(int size) {
    Priority_Queue *q = (Priority_Queue *)malloc(sizeof(Priority_Queue));
    q->data = (int *)malloc(sizeof(int) * size);
    // 控制数组下标从 1 开始
    q->data -= 1;
    q->n = 0;
    q->size = size;
    return q;
}

// 堆的向上调整操作
// ind 指向当前需要向上调整的节点
// father 指向 ind 的父节点
void up_update(Priority_Queue *q, int ind) {
    int father, val;
    while (ind != 1) {
        father = ind / 2;
        if (q->data[father] <= q->data[ind]) break;
        val = q->data[ind];
        q->data[ind] = q->data[father];
        q->data[father] = val;
        ind = father;
    }
    return ;
}

// 堆的向下调整操作
// ind 指向当前需要向下调整的节点
// temp 指向两个子节点中值较小的节点
// ind * 2 <= q->n 说明当前节点还有子节点
void down_update(Priority_Queue *q, int ind) {
    int temp, val;
    while (ind * 2 <= q->n) {
        temp = ind * 2;
        if (temp + 1 <= q->n && q->data[temp + 1] < q->data[temp]) {
            temp = temp + 1;
        }
        if (q->data[ind] <= q->data[temp]) break;
        val = q->data[ind];
        q->data[ind] = q->data[temp];
        q->data[temp] = val;
        ind = temp;
    }
    return ;
}

// 队列判空操作
int empty(Priority_Queue *q) {
    return q->n == 0;
}

// 入队操作
// 先放置元素，再向上调整
int push(Priority_Queue *q, int element) {
    if (q->n == q->size) return 0;
    q->data[++(q->n)] = element;
    up_update(q, q->n);
    return 1;
}

// 出队操作
// 先覆盖元素，再向下调整
void pop(Priority_Queue *q) {
    if (empty(q)) return ;
    q->data[1] = q->data[(q->n)--];
    down_update(q, 1);
    return ;
}

// 查看堆顶元素
int top(Priority_Queue *q) {
     return q->data[1];
}

// 销毁优先队列
void clear(Priority_Queue *q) {
    free(q->data + 1);
    free(q);
    return ;
}

//---------------华丽的分割线----------------//

void usage(int *op) {
    printf("优先队列结构学习，请输入操作命令(0--6)：\n");
    printf("\t0.查看堆中元素情况\n");
    printf("\t1.插入元素\n");
    printf("\t2.移除队首元素\n");
    printf("\t3.查看队首元素\n");
    printf("\t4.退出\n");
    printf("请输入操作命令所对应的数字：");
    scanf("%d", op);
    return ;
}

void output(Priority_Queue *q) {
    for (int i = 1; i <= q->size; i++) {
        printf("%4d", i);
    }
    printf("\n");
    for (int i = 1; i <= q->size; i++) {
        printf("----");
    }
    printf("\n");
    for (int i = 1; i <= q->n; i++) {
        printf("%4d", q->data[i]);
    }
    for (int i = q->n + 1; i <= q->size; i++) {
        printf("   -");
    }
    printf("\n");
    return ;
}


int main() {
    int size, loop = 1;
    printf("输入初始化容量：");
    scanf("%d", &size);
    Priority_Queue *q = init(size);
    do {
        int op, val;
        usage(&op);
        switch (op) {
            case 0: output(q); break;
            case 1: {
                printf("请输入要插入的数字：");
                scanf("%d", &val);
                push(q, val);
            } break;
            case 2: pop(q); break;
            case 3: printf("%d\n", top(q)); break;
            case 4: loop = 0; break;
        }
    } while (loop);
    clear(q);
    return 0;
}
