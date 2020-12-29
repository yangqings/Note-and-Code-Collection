class Solution {
public:
    int climbStairs(int n) {
        //思路：列出n = 0， n = 1....发现
        //f(x) = f(x-1) + f(x-2)
        //滚动保存f(x-1)和f(x-2)
        int p = 0, q = 0, r = 1;
        for(int i = 1; i <= n; ++i){
            p = q;
            q = r;
            r = p + q;
        }
        return r;
    }
};