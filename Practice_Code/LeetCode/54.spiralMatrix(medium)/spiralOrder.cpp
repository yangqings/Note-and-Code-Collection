//nice
//通过每次更新边界来缩小遍历范围，判断上下左右边界是否发生交换，作为结束条件
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        vector<int> ans;

        int top = 0, down = matrix.size() - 1, left = 0, right = matrix[0].size() - 1;
        
        while(true){//
            //left --> right
            for(int i = left; i <= right; ++i) ans.emplace_back(matrix[top][i]);
            if(++top > down) break;

            //top-->down
            for(int i = top; i <= down; ++i) ans.emplace_back(matrix[i][right]);
            if(--right < left) break;

            //right-->left
            for(int i = right; i >= left; --i) ans.emplace_back(matrix[down][i]);
            if(--down < top) break;

            //down-->top
            for(int i = down; i >= top; --i) ans.emplace_back(matrix[i][left]);
            if(++left > right) break;
        }

        return ans;

    }
};