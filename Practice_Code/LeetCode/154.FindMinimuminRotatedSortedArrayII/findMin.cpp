/**
 * @brief 一次遍历找最小值，时间复杂度O(n)，不符合题目要求
 * 
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size() - 1;
        int min = INT_MAX;
        for(int i = 0; i <= end; ++i){
            if(nums[i] < min)min = nums[i];
        }
        return min;
    }
};

/**
 * @brief 二分，三种情况，逐渐缩小边界找到最小值
 * 
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int start = 0, end = nums.size() - 1;
        while(start <  end){
            int pivot = start + (end - start) / 2;
            if(nums[pivot] < nums[end]) 
                end = pivot;
            else if(nums[pivot] > nums[end]) 
                start = pivot + 1;
            else 
                end -= 1;
        }
        return nums[start];
    }
};