/**
 * @file SortColors.cpp
 * @author your name (you@domain.com)
 * @brief  红白蓝三色分类问题：
 * @version 0.1
 * @date 2020-12-16
 * 
 * @copyright Copyright (c) 2020
 * 
 */


//单指针方式，第一次遍历，将 0 交换到ptr位置，位置+1
//第二次从0后遍历一次，将1交换到ptr位置，位置+1
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int ptr = 0;
        for (int i = 0; i < n; ++i){
            if(nums[i] == 0){
                swap(nums[i], nums[ptr]);
                ++ptr;
            }
        }
        for (int i = ptr; i < n; ++i){
            if(nums[i] == 1){
                swap(nums[i], nums[ptr]);
                ++ptr;
            }
        }
    }
};


//双指针，只进行一次遍历
class Solution(){
public:
    void sortColors(vecotr<int>& nums){
        int n = nums.size();
        int p0, p1 = 0;
        for(int i = 0; i < n; ++i) {
            if(nums[i] == 1){
                swap(nums[i], nums[p1]);
                ++p1;
            }else if (nums[i] == 0) {
                swap(nums[i],nums[p0]);
                if(p0 < p1){
                    swap(nums[i], nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};

//双指针，只进行一次遍历
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int p0 = 0, p2 = n - 1;
        for(int i = 0; i < n; ++i){
            while(nums[i] == 2 && i < p2){
                swap(nums[i], nums[p2]);
                -- p2;
            }
            if(nums[i] == 0){
                swap(nums[i], nums[p0]);
                ++p0;
            }
        }
    }
};

//类似桶排序，比较慢
class Solution {
public:
    void sortColors(vector<int>& nums) {
        unordered_map<int, int> counts;
        for(const int & num : nums){
            ++counts[num];
        }
        int k = 0;
        for( int i = 0; i < 3; i++ ){
            for(int j = 0; j < counts[i]; j++){
                nums[k++] = i;
            }
        }
    }
};