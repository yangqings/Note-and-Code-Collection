/**
 * @brief 归并两个有序数组
 *        不允许使用额外空间，nums1保存
 *        思路：双指针，从后开始遍历，比较两个数组最后元素大小，将大的元素放入
 */

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos = m-- + n-- - 1;   //m-- 返回的是m
        while(m >= 0 && n >= 0){
            nums1[pos--] = nums1[m] > nums2[n] ? nums1[m--]:nums2[n--];
        }
        while(n >= 0){
            nums1[pos--] = nums2[n--];
        }
    }
};