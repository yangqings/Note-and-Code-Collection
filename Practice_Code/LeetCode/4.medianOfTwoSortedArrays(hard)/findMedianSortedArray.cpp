//思路，不用遍历全部数组
//当m+n为奇数，找两个数组的第(m+n)/2个元素
//当m+n为偶数，找两个数组的第(m+n)/2和第(m+n)/2+1个元素的平均值
//转化为找第k大元素
//利用类似二分查找的思想
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLen = nums1.size() + nums2.size();
        if(totalLen % 2 == 1){
            //m + n 奇数 
            return getKthNum(nums1, nums2, (totalLen + 1) / 2);
        }else{
            //m + n 为偶数
            return (getKthNum(nums1, nums2, totalLen / 2) + getKthNum(nums1, nums2, totalLen / 2 + 1))/2.0;
        }

    }
private:
    int getKthNum(vector<int>& nums1, vector<int>& nums2, int k){//使用二分查找降低时间复杂度
        int m = nums1.size(), n = nums2.size();
        int index1 = 0, index2 = 0;
        
        while(true){
            if(index1 == m) return nums2[index2 + k - 1];
            if(index2 == n) return nums1[index1 + k - 1];
            if(k == 1) return min(nums1[index1], nums2[index2]);

            int newIndex1 = min(index1 + k/2 - 1, m - 1);
            int newIndex2 = min(index2 + k/2 - 1, n - 1);
            int pivot1 = nums1[ newIndex1 ];
            int pivot2 = nums2[ newIndex2 ];
            if(pivot1 <= pivot2){ //pivot最多大于前 k - 2
                k -= newIndex1 - index1 + 1;//排除前面的数
                index1 = newIndex1  + 1;
            }else{
                k -= newIndex2 - index2 + 1;//排除前面的数
                index2 = newIndex2 + 1;
            }
        } 
    }
};