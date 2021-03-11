//思路：双指针,更新雨水量
//O(n)时间复杂度  O(1)额外空间
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1, leftMax = 0, rightMax = 0;

        while(left < right){
            //应该从高度低的这一侧开始考虑雨水量，因为这一侧的高度是保证雨水不会从这一侧流掉的最低高度
            if(height[left] < height[right]){ //关键在于理解这个条件！！！
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

//栈保存可能存雨水的条形块