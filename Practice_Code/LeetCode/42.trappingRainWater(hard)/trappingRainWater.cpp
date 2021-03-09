//很巧妙的解法，双指针，实际上想不出来
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();
        if(n <= 1)return 0;

        int leftMax = 0, left = 0, rightMax = 0, right = n - 1, ans = 0;

        while(left < right){
            if(height[left] < height[right]){
                height[left] >= leftMax ? (leftMax = height[left]) : ans += (leftMax - height[left]);
                ++left;
            }else{
                height[right] >= rightMax ? (rightMax = height[right]) : ans += (rightMax - height[right]);
                --right;
            }
        }

        return ans;
    }
};

//暴力算法
//时间复杂度，空间复杂度

//双指针算法
//时间复杂度，空间复杂度

//栈辅助算法
//时间复杂度，空间复杂度