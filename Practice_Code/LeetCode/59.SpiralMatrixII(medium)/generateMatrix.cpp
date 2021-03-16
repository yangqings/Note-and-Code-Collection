class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        if(n == 1) return {{1}};
        vector<vector<int>> ans(n, vector<int>(n,0));
        int top = 0, down = n - 1, left = 0, right = n - 1, count = 0;

        while(true){
            for(int i = left; i <= right; ++i) ans[top][i] = ++count;
            if(++top > down) break;
            for(int i = top; i <= down; ++i) ans[i][right] = ++count;
            if(--right < left) break;
            for(int i = right; i >= left; --i) ans[down][i] = ++count;
            if(--down < top) break;
            for(int i = down; i >= top; --i) ans[i][left] = ++count;
            if(++left > right) break;
        }


        return ans;
    }  
};