//题解，双指针法
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
         vector<vector<int>> result;
         sort(nums.begin(), nums.end());

         for(int i = 0; i < nums.size(); i++){
             if(nums[i]>0)return result;//排好序，三数中最小的数大于零，三数之和必大于零
             if(i > 0 && nums[i] == nums[i-1])continue;//去重
             
             int left = i + 1;
             int right = nums.size() - 1;
             int sum = 0;

             while(left < right){
                 sum = nums[i] + nums[left] + nums[right];
                 if(sum < 0) left++;
                 else if(sum > 0) right--;
                 else {
                     result.push_back( vector<int>{nums[i], nums[left], nums[right]} );
                     //去掉重复三元组
                     while(left < right && nums[right] == nums[right-1]) right--;
                     while(left < right && nums[left] == nums[left+1]) left++; 

                     left++;
                     right--;
                 }
             }
         }
         return result;
    }
};