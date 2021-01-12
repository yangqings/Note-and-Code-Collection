//类似于C++标准函数库里的lower_bound和upper_bound函数
//二分方法的细节值得推敲，边界条件对结果的影响
class Solution {

public:

    vector<int> searchRange(vector<int> &nums, int target) {
        if (nums.empty())return vector < int > {-1, -1};
        int lower = lower_bound(nums, target);
        int upper = upper_bound(nums, target) - 1;
        if (lower == nums.size() || nums[lower] != target) {
            return vector < int > {-1, -1};
        }
        return vector < int > {lower, upper};
    }

private:

    int lower_bound(vector<int> &nums, int target) {
        int l = 0, r = nums.size(), mid;
        while (l < r) {
            mid = (l + r) / 2;
            if (nums[mid] >= target) r = mid;   //这里的等号导致，命中元素时，继续往左边界查找
            else l = mid + 1;
        }
        return l;
    }

    int upper_bound(vector<int> &nums, int target) {
        int l = 0, r = nums.size(), mid;
        while (l < r) {
            mid = (l + r) / 2;
            if (nums[mid] > target) r = mid;
            else l = mid + 1;                 //由于if case没有等号，命中元素时，继续往右边界查找
        }
        return l;
    }
};