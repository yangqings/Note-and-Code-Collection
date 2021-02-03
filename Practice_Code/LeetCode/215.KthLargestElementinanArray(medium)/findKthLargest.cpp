/**
 * @brief 无序数组找到第k大的元素，
 *        思路：利用快速排序
 *        快排（升序）的轴点pivot定义，pivot前的数都不大于pivot，pivot后的数都不小于pivot
 *        当pivotSelection得到的pivot位置是nums.size() - k 时，nums[pivot]就是第k大元素
 *        时间复杂度O(n，空间复杂度O(logn)
 */
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int l = 0, r = nums.size() - 1, target = nums.size() - k;
        while(l < r){
            int pivot = quickSelection(nums, l, r);
            if(pivot == target){
                return nums[pivot];  //hit
            }
            if(pivot < target){
                l = pivot + 1;
            }else{
                r = pivot - 1;
            }
        }
        return nums[l];
    }

    int quickSelection(vector<int>& nums, int lo, int hi){

        swap(nums[lo], nums[lo + rand()%(hi - lo + 1)]);//随机置乱首次pivot选择
        int pivot = nums[lo];

        while(lo < hi){
            while((lo < hi) && nums[hi] >= pivot){
                --hi;
            }
            nums[lo] = nums[hi];
            while((lo < hi) && nums[lo] <= pivot){
                ++lo;
            }
            nums[hi] = nums[lo];
        }
        nums[lo] = pivot;
        return lo;
    }
};

/**
 * @brief 无序数组找到第k大的元素，
 *        思路：利用大顶堆或者小顶堆
 *        大顶堆，做k-1次删除操作后堆顶元素就是第k大元素
 *        时间复杂度：O(nlogn) 空间复杂度O(logn)
 */

class Solution {
public:
    void maxHeapify(vector<int>& a, int i, int heapSize) {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) {
            largest = l;
        } 
        if (r < heapSize && a[r] > a[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& a, int heapSize) {
        for (int i = heapSize / 2; i >= 0; --i) {
            maxHeapify(a, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};
