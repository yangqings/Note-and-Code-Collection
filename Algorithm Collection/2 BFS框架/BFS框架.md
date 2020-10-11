### BFS框架

#### 1. BFS找图的最短路径

```java
int BFS(Node start, Node target)
{
    Queue<Node> q;
    Set<Node> visited;
    
    q.offer(start);
    visited.add(start);
    int step = 0;
    
    while(q not empty){
        int sz = q.size();
        for(int i = 0; i < sz; i++){
            Node cur = q.poll();/*取出一个节点*/
            if(curr is target)  /*判断是否到终点,比如二叉树，左右子树都是null则到达终点*/
                return step;
            for(Node x : cur.adj())/*逐个取出当前节点的邻节点*/
                if(x not in visited)/*未被访问过*/
                {
                    q.offer(x);
                    visited.add(x);
                }
        }
        step ++;/*更新步数*/
    }
}
```

#### 2. 解开密码锁

LeetCode752题