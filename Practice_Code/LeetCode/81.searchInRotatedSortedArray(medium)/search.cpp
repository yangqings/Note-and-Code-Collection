/**
 * @brief 直接使用二分查找
 *        mid指向的值小于右端，则右端有序
 *        mid指向的值大于左端，左端有序
 *        mid指向的值等于左端，不能判断左右区间，将左端点右移一位，继续二分
 */
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int start = 0, end = nums.size() - 1;
        while(start <= end){
            int mid = (start + end) / 2;
            if(nums[mid] == target){
                return true;
            }
            if(nums[start] == nums[mid]){//无法判断哪个区间是增序
                ++start;
            }else if(nums[mid] <= nums[end]){//右区间增序
                if(target > nums[mid] && target <= nums[end]){
                    start = mid + 1;
                }else{
                    end = mid - 1;
                }
            }else{//左区间增序
                if(target >= nums[start] && target < nums[mid]){
                    end = mid - 1;
                }else{
                    start = mid + 1;
                }
            }
        }
        return false;
    }
};