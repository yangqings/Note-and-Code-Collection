/**
 * @brief 这种方法比较巧妙
 *        判断相邻元素是否相同，以及当前索引是否为偶数
 * 
 */
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while(lo < hi){
            int mid = lo + (hi -lo) / 2;
            if(mid % 2 == 1) mid--; //确保 mid 是偶数
            if(nums[mid] == nums[mid + 1]){
                lo = mid + 2;
            } else {
                hi = mid;
            }
        }
        return nums[lo];
    }
};

/**
 * @brief 比较常规的思路，二分查找
 * 
 */

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        while(lo < hi){
            int mid = lo + (hi - lo) / 2;
            bool halvesAreEven = (hi - mid) % 2 == 0;
            if(nums[mid + 1] == nums[mid]){ //相同元素在右边
                if(halvesAreEven){
                    lo = mid + 2;
                } else {
                    hi = mid - 1;
                } 
            }else if(nums[mid - 1] == nums[mid]) { //相同元素在右边
                if(halvesAreEven){ //右边数组大小为偶数。
                    hi = mid - 2;
                } else {           //右边数组大小为奇数
                    lo = mid + 1;
                }
            } else { //刚好命中奇数个的元素
                return nums[mid];
            }
        }
        return nums[lo];
    }
};